/*******************************************************************************
* File Name: Clock_7.c
* Version 1.70
*
*  Description:
*   This file provides the source code to the API for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include <cydevice_trm.h>
#include "Clock_7.h"

/* Clock Distribution registers. */
#define CLK_DIST_LD              (* (reg8 *) CYREG_CLKDIST_LD)
#define CLK_DIST_BCFG2           (* (reg8 *) CYREG_CLKDIST_BCFG2)
#define BCFG2_MASK               (0x80u)
#define CLK_DIST_DMASK           (* (reg8 *) CYREG_CLKDIST_DMASK)
#define CLK_DIST_AMASK           (* (reg8 *) CYREG_CLKDIST_AMASK)

#define HAS_CLKDIST_LD_DISABLE   (CY_PSOC3 || CY_PSOC5LP)


/*******************************************************************************
* Function Name: Clock_7_Start
********************************************************************************
* Summary:
*  Starts the clock. Note that on startup, clocks may be already running if the
*  "Start on Reset" option is enabled in the DWR.
*
* Parameters:
*  void
*
* Returns:
*  void
*
*******************************************************************************/
void Clock_7_Start(void) 
{
    /* Set the bit to enable the clock. */
    Clock_7_CLKEN |= Clock_7_CLKEN_MASK;
}


/*******************************************************************************
* Function Name: Clock_7_Stop
********************************************************************************
* Summary:
*  Stops the clock and returns immediately. This API does not require the
*  source clock to be running but may return before the hardware is actually
*  disabled. If the settings of the clock are changed after calling this
*  function, the clock may glitch when it is started. To avoid the clock
*  glitch, use the StopBlock function.
*
* Parameters:
*  void
*
* Returns:
*  void
*
*******************************************************************************/
void Clock_7_Stop(void) 
{
    /* Clear the bit to disable the clock. */
    Clock_7_CLKEN &= ~Clock_7_CLKEN_MASK;
}


#if(CY_PSOC3 || CY_PSOC5LP)
/*******************************************************************************
* Function Name: Clock_7_StopBlock
********************************************************************************
* Summary:
*  Stops the clock and waits for the hardware to actually be disabled before
*  returning. This ensures that the clock is never truncated (high part of the
*  cycle will terminate before the clock is disabled and the API returns).
*  Note that the source clock must be running or this API will never return as
*  a stopped clock cannot be disabled.
*
* Parameters:
*  void
*
* Returns:
*  void
*
*******************************************************************************/
void Clock_7_StopBlock(void) 
{
    if (Clock_7_CLKEN & Clock_7_CLKEN_MASK)
    {
#if HAS_CLKDIST_LD_DISABLE
        uint16 oldDivider;

        CLK_DIST_LD = 0;

        /* Clear all the mask bits except ours. */
#if defined(Clock_7__CFG3)
        CLK_DIST_AMASK = Clock_7_CLKEN_MASK;
        CLK_DIST_DMASK = 0x00u;
#else
        CLK_DIST_DMASK = Clock_7_CLKEN_MASK;
        CLK_DIST_AMASK = 0x00u;
#endif

        /* Clear mask of bus clock. */
        CLK_DIST_BCFG2 &= ~BCFG2_MASK;

        oldDivider = CY_GET_REG16(Clock_7_DIV_PTR);
        CY_SET_REG16(CYREG_CLKDIST_WRK0, oldDivider);
        CLK_DIST_LD = CYCLK_LD_DISABLE | CYCLK_LD_SYNC_EN | CYCLK_LD_LOAD;

        /* Wait for clock to be disabled */
        while (CLK_DIST_LD & CYCLK_LD_LOAD) { }
#endif

        /* Clear the bit to disable the clock. */
        Clock_7_CLKEN &= ~Clock_7_CLKEN_MASK;

#if HAS_CLKDIST_LD_DISABLE
        /* Clear the disable bit */
        CLK_DIST_LD = 0x00u;
        CY_SET_REG16(Clock_7_DIV_PTR, oldDivider);
#endif
    }
}
#endif

/*******************************************************************************
* Function Name: Clock_7_StandbyPower
********************************************************************************
* Summary:
*  Sets whether the clock is active in standby mode.
*
* Parameters:
*  state:  0 to disable clock during standby, nonzero to enable.
*
* Returns:
*  void
*
*******************************************************************************/
void Clock_7_StandbyPower(uint8 state) 
{
    if(state == 0)
    {
        Clock_7_CLKSTBY &= ~Clock_7_CLKSTBY_MASK;
    }
    else
    {
        Clock_7_CLKSTBY |= Clock_7_CLKSTBY_MASK;
    }
}


/*******************************************************************************
* Function Name: Clock_7_SetDividerRegister
********************************************************************************
* Summary:
*  Modifies the clock divider and, thus, the frequency. When the clock divider
*  register is set to zero or changed from zero, the clock will be temporarily
*  disabled in order to change the SSS mode bit. If the clock is enabled when
*  SetDividerRegister is called, then the source clock must be running.
*
* Parameters:
*  clkDivider:  Divider register value (0-65,535). This value is NOT the
*    divider; the clock hardware divides by clkDivider plus one. For example,
*    to divide the clock by 2, this parameter should be set to 1.
*  restart:  If nonzero, restarts the clock divider: the current clock cycle
*   will be truncated and the new divide value will take effect immediately. If
*   zero, the new divide value will take effect at the end of the current clock
*   cycle.
*
* Returns:
*  void
*
*******************************************************************************/
void Clock_7_SetDividerRegister(uint16 clkDivider, uint8 restart) 
{
    uint8 enabled;

    uint8 currSrc = Clock_7_GetSourceRegister();
    uint16 oldDivider = Clock_7_GetDividerRegister();

    if (clkDivider != oldDivider)
    {
        enabled = Clock_7_CLKEN & Clock_7_CLKEN_MASK;

        if (currSrc == CYCLK_SRC_SEL_CLK_SYNC_D && (oldDivider == 0 || clkDivider == 0))
        {
            /* Moving to/from SSS requires correct ordering to prevent halting the clock    */
            if (oldDivider == 0 && clkDivider != 0)
            {
                /* Moving away from SSS, set the divider first so when SSS is cleared we    */
                /* don't halt the clock.  Using the shadow load isn't required as the       */
                /* divider is ignored while SSS is set.                                     */
                CY_SET_REG16(Clock_7_DIV_PTR, clkDivider);
                Clock_7_MOD_SRC &= ~CYCLK_SSS;
            }
            else
            {
                /* Moving to SSS, set SSS which then ignores the divider and we can set     */
                /* it without bothering with the shadow load.                               */
                Clock_7_MOD_SRC |= CYCLK_SSS;
                CY_SET_REG16(Clock_7_DIV_PTR, clkDivider);
            }
        }
        else
        {
            if (enabled)
            {
                CLK_DIST_LD = 0x00u;

                /* Clear all the mask bits except ours. */
#if defined(Clock_7__CFG3)
                CLK_DIST_AMASK = Clock_7_CLKEN_MASK;
                CLK_DIST_DMASK = 0x00u;
#else
                CLK_DIST_DMASK = Clock_7_CLKEN_MASK;
                CLK_DIST_AMASK = 0x00u;
#endif
                /* Clear mask of bus clock. */
                CLK_DIST_BCFG2 &= ~BCFG2_MASK;

#if HAS_CLKDIST_LD_DISABLE
                CY_SET_REG16(CYREG_CLKDIST_WRK0, oldDivider);
                CLK_DIST_LD = CYCLK_LD_DISABLE|CYCLK_LD_SYNC_EN|CYCLK_LD_LOAD;

                /* Wait for clock to be disabled */
                while (CLK_DIST_LD & CYCLK_LD_LOAD) { }
#endif

                Clock_7_CLKEN &= ~Clock_7_CLKEN_MASK;

#if HAS_CLKDIST_LD_DISABLE
                /* Clear the disable bit */
                CLK_DIST_LD = 0x00u;
#endif
            }

            /* Load divide value. */
            if (Clock_7_CLKEN & Clock_7_CLKEN_MASK)
            {
                /* If the clock is still enabled, use the shadow registers */
                CY_SET_REG16(CYREG_CLKDIST_WRK0, clkDivider);

                CLK_DIST_LD = (CYCLK_LD_LOAD | (restart ? CYCLK_LD_SYNC_EN : 0x00u));
                while (CLK_DIST_LD & CYCLK_LD_LOAD) { }
            }
            else
            {
                /* If the clock is disabled, set the divider directly */
                CY_SET_REG16(Clock_7_DIV_PTR, clkDivider);
            }

            Clock_7_CLKEN |= enabled;
        }
    }
}


/*******************************************************************************
* Function Name: Clock_7_GetDividerRegister
********************************************************************************
* Summary:
*  Gets the clock divider register value.
*
* Parameters:
*  void
*
* Returns:
*  Divide value of the clock minus 1. For example, if the clock is set to
*  divide by 2, the return value will be 1.
*
*******************************************************************************/
uint16 Clock_7_GetDividerRegister(void) 
{
    return CY_GET_REG16(Clock_7_DIV_PTR);
}


/*******************************************************************************
* Function Name: Clock_7_SetModeRegister
********************************************************************************
* Summary:
*  Sets flags that control the operating mode of the clock. This function only
*  changes flags from 0 to 1; flags that are already 1 will remain unchanged.
*  To clear flags, use the ClearModeRegister function. The clock must be
*  disabled before changing the mode.
*
* Parameters:
*  clkMode: Bit mask containing the bits to set. For PSoC 3 and PSoC 5,
*   clkMode should be a set of the following optional bits or'ed together.
*   - CYCLK_EARLY Enable early phase mode. Rising edge of output clock will
*                 occur when the divider count reaches half of the divide
*                 value.
*   - CYCLK_DUTY  Enable 50% duty cycle output. When enabled, the output clock
*                 is asserted for approximately half of its period. When
*                 disabled, the output clock is asserted for one period of the
*                 source clock.
*   - CYCLK_SYNC  Enable output synchronization to master clock. This should
*                 be enabled for all synchronous clocks.
*   See the Technical Reference Manual for details about setting the mode of
*   the clock. Specifically, see the CLKDIST.DCFG.CFG2 register.
*
* Returns:
*  void
*
*******************************************************************************/
void Clock_7_SetModeRegister(uint8 clkMode) 
{
    Clock_7_MOD_SRC |= clkMode & Clock_7_MODE_MASK;
}


/*******************************************************************************
* Function Name: Clock_7_ClearModeRegister
********************************************************************************
* Summary:
*  Clears flags that control the operating mode of the clock. This function
*  only changes flags from 1 to 0; flags that are already 0 will remain
*  unchanged. To set flags, use the SetModeRegister function. The clock must be
*  disabled before changing the mode.
*
* Parameters:
*  clkMode: Bit mask containing the bits to clear. For PSoC 3 and PSoC 5,
*   clkMode should be a set of the following optional bits or'ed together.
*   - CYCLK_EARLY Enable early phase mode. Rising edge of output clock will
*                 occur when the divider count reaches half of the divide
*                 value.
*   - CYCLK_DUTY  Enable 50% duty cycle output. When enabled, the output clock
*                 is asserted for approximately half of its period. When
*                 disabled, the output clock is asserted for one period of the
*                 source clock.
*   - CYCLK_SYNC  Enable output synchronization to master clock. This should
*                 be enabled for all synchronous clocks.
*   See the Technical Reference Manual for details about setting the mode of
*   the clock. Specifically, see the CLKDIST.DCFG.CFG2 register.
*
* Returns:
*  void
*
*******************************************************************************/
void Clock_7_ClearModeRegister(uint8 clkMode) 
{
    Clock_7_MOD_SRC &= ~clkMode | ~Clock_7_MODE_MASK;
}


/*******************************************************************************
* Function Name: Clock_7_GetModeRegister
********************************************************************************
* Summary:
*  Gets the clock mode register value.
*
* Parameters:
*  void
*
* Returns:
*  Bit mask representing the enabled mode bits. See the SetModeRegister and
*  ClearModeRegister descriptions for details about the mode bits.
*
*******************************************************************************/
uint8 Clock_7_GetModeRegister(void) 
{
    return Clock_7_MOD_SRC & Clock_7_MODE_MASK;
}


/*******************************************************************************
* Function Name: Clock_7_SetSourceRegister
********************************************************************************
* Summary:
*  Sets the input source of the clock. The clock must be disabled before
*  changing the source. The old and new clock sources must be running.
*
* Parameters:
*  clkSource:  For PSoC 3 and PSoC 5 devices, clkSource should be one of the
*   following input sources:
*   - CYCLK_SRC_SEL_SYNC_DIG
*   - CYCLK_SRC_SEL_IMO
*   - CYCLK_SRC_SEL_XTALM
*   - CYCLK_SRC_SEL_ILO
*   - CYCLK_SRC_SEL_PLL
*   - CYCLK_SRC_SEL_XTALK
*   - CYCLK_SRC_SEL_DSI_G
*   - CYCLK_SRC_SEL_DSI_D/CYCLK_SRC_SEL_DSI_A
*   See the Technical Reference Manual for details on clock sources.
*
* Returns:
*  void
*
*******************************************************************************/
void Clock_7_SetSourceRegister(uint8 clkSource) 
{
    uint16 currDiv = Clock_7_GetDividerRegister();
    uint8 oldSrc = Clock_7_GetSourceRegister();

    if (oldSrc != CYCLK_SRC_SEL_CLK_SYNC_D && clkSource == CYCLK_SRC_SEL_CLK_SYNC_D && currDiv == 0)
    {
        /* Switching to Master and divider is 1, set SSS, which will output master, */
        /* then set the source so we are consistent.                                */
        Clock_7_MOD_SRC |= CYCLK_SSS;
        Clock_7_MOD_SRC =
            (Clock_7_MOD_SRC & ~Clock_7_SRC_SEL_MSK) | clkSource;
    }
    else if (oldSrc == CYCLK_SRC_SEL_CLK_SYNC_D && clkSource != CYCLK_SRC_SEL_CLK_SYNC_D && currDiv == 0)
    {
        /* Switching from Master to not and divider is 1, set source, so we don't   */
        /* lock when we clear SSS.                                                  */
        Clock_7_MOD_SRC =
            (Clock_7_MOD_SRC & ~Clock_7_SRC_SEL_MSK) | clkSource;
        Clock_7_MOD_SRC &= ~CYCLK_SSS;
    }
    else
    {
        Clock_7_MOD_SRC =
            (Clock_7_MOD_SRC & ~Clock_7_SRC_SEL_MSK) | clkSource;
    }
}


/*******************************************************************************
* Function Name: Clock_7_GetSourceRegister
********************************************************************************
* Summary:
*  Gets the input source of the clock.
*
* Parameters:
*  void
*
* Returns:
*  The input source of the clock. See SetSourceRegister for details.
*
*******************************************************************************/
uint8 Clock_7_GetSourceRegister(void) 
{
    return Clock_7_MOD_SRC & Clock_7_SRC_SEL_MSK;
}


#if defined(Clock_7__CFG3)


/*******************************************************************************
* Function Name: Clock_7_SetPhaseRegister
********************************************************************************
* Summary:
*  Sets the phase delay of the analog clock. This function is only available
*  for analog clocks. The clock must be disabled before changing the phase
*  delay to avoid glitches.
*
*
* Parameters:
*  clkPhase: Amount to delay the phase of the clock, in 1.0ns increments.
*   clkPhase must be from 1 to 11 inclusive. Other values, including 0,
*   disable the clock. clkPhase = 1 produces a 0ns delay and clkPhase = 11 
*   produces a 10ns delay.
*
* Returns:
*  void
*
*******************************************************************************/
void Clock_7_SetPhaseRegister(uint8 clkPhase) 
{
    Clock_7_PHASE = clkPhase & Clock_7_PHASE_MASK;
}


/*******************************************************************************
* Function Name: Clock_7_GetPhase
********************************************************************************
* Summary:
*  Gets the phase delay of the analog clock. This function is only available
*  for analog clocks.
*
* Parameters:
*  void
*
* Returns:
*  Phase of the analog clock. See SetPhaseRegister for details.
*
*******************************************************************************/
uint8 Clock_7_GetPhaseRegister(void) 
{
    return Clock_7_PHASE & Clock_7_PHASE_MASK;
}

#endif


/* [] END OF FILE */
