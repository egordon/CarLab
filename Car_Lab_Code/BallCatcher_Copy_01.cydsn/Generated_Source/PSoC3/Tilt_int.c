/*******************************************************************************
* File Name: Tilt_int.c  
* Version 1.60
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include <CYDEVICE.H>
#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <Tilt_int.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START Tilt_int_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: Tilt_int_Start
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void Tilt_int_Start(void)
{
    /* For all we know the interrupt is active. */
    Tilt_int_Disable();

    /* Set the ISR to point to the Tilt_int Interrupt. */
    Tilt_int_SetVector(Tilt_int_Interrupt);

    /* Set the priority. */
    Tilt_int_SetPriority(Tilt_int_INTC_PRIOR_NUMBER);

    /* Enable it. */
    Tilt_int_Enable();
}

/*******************************************************************************
* Function Name: Tilt_int_StartEx
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*******************************************************************************/
void Tilt_int_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    Tilt_int_Disable();

    /* Set the ISR to point to the Tilt_int Interrupt. */
    Tilt_int_SetVector(address);

    /* Set the priority. */
    Tilt_int_SetPriority(Tilt_int_INTC_PRIOR_NUMBER);

    /* Enable it. */
    Tilt_int_Enable();
}

/*******************************************************************************
* Function Name: Tilt_int_Stop
********************************************************************************
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
void Tilt_int_Stop(void) 
{
    /* Disable this interrupt. */
    Tilt_int_Disable();
}

/*******************************************************************************
* Function Name: Tilt_int_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for Tilt_int.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
*
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
CY_ISR(Tilt_int_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START Tilt_int_Interrupt` */

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (Tilt_int__ES2_PATCH ))      
            Tilt_int_ISR_PATCH();
        #endif
    #endif
}

/*******************************************************************************
* Function Name: Tilt_int_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling Tilt_int_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use Tilt_int_StartEx instead.
*
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void Tilt_int_SetVector(cyisraddress address) 
{
    CY_SET_REG16(Tilt_int_INTC_VECTOR, (uint16) address);
}

/*******************************************************************************
* Function Name: Tilt_int_GetVector
********************************************************************************
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*
*******************************************************************************/
cyisraddress Tilt_int_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(Tilt_int_INTC_VECTOR);
}

/*******************************************************************************
* Function Name: Tilt_int_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling Tilt_int_Start
*   or Tilt_int_StartEx will override any effect this method would have had. 
*	This method should only be called after Tilt_int_Start or 
*	Tilt_int_StartEx has been called. To set the initial
*	priority for the component use the cydwr file in the tool.
*
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void Tilt_int_SetPriority(uint8 priority) 
{
    *Tilt_int_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: Tilt_int_GetPriority
********************************************************************************
* Summary:
*   Gets the Priority of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
*******************************************************************************/
uint8 Tilt_int_GetPriority(void) 
{
    uint8 priority;


    priority = *Tilt_int_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: Tilt_int_Enable
********************************************************************************
* Summary:
*   Enables the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void Tilt_int_Enable(void) 
{
    /* Enable the general interrupt. */
    *Tilt_int_INTC_SET_EN = Tilt_int__INTC_MASK;
}

/*******************************************************************************
* Function Name: Tilt_int_GetState
********************************************************************************
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   1 if enabled, 0 if disabled.
*
*
*******************************************************************************/
uint8 Tilt_int_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*Tilt_int_INTC_SET_EN & Tilt_int__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: Tilt_int_Disable
********************************************************************************
* Summary:
*   Disables the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void Tilt_int_Disable(void) 
{
    /* Disable the general interrupt. */
    *Tilt_int_INTC_CLR_EN = Tilt_int__INTC_MASK;
}

/*******************************************************************************
* Function Name: Tilt_int_SetPending
********************************************************************************
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void Tilt_int_SetPending(void) 
{
    *Tilt_int_INTC_SET_PD = Tilt_int__INTC_MASK;
}

/*******************************************************************************
* Function Name: Tilt_int_ClearPending
********************************************************************************
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void Tilt_int_ClearPending(void) 
{
    *Tilt_int_INTC_CLR_PD = Tilt_int__INTC_MASK;
}
