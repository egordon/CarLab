/*******************************************************************************
* FILENAME: cyfitter_cfg.c
* PSoC Creator 2.1 Component Pack 4
*
* Description:
* This file is automatically generated by PSoC Creator with device 
* initialization code.  Except for the user defined sections in
* CyClockStartupError(), this file should not be modified.
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include <string.h>
#include <cytypes.h>
#include <cydevice_trm.h>
#include <cyfitter.h>
#include <CyLib.h>
#include <cyfitter_cfg.h>

/* Clock startup error codes                                                   */
#define CYCLOCKSTART_NO_ERROR    0
#define CYCLOCKSTART_XTAL_ERROR  1
#define CYCLOCKSTART_32KHZ_ERROR 2
#define CYCLOCKSTART_PLL_ERROR   3

/*******************************************************************************
* Function Name: CyClockStartupError
********************************************************************************
* Summary:
*  If an error is encountered during clock configuration (crystal startup error,
*  PLL lock error, etc) the system will end up here.  Unless reimplemented by 
*  the customer, an infinite loop will be encountered.
*
* Parameters:  
*   void
*
* Return:
*   void
*
*******************************************************************************/
#if defined(__GNUC__) || defined(__ARMCC_VERSION)
__attribute__ ((unused))
#endif
static void CyClockStartupError(uint8 errorCode)
{
    /* To remove the compiler warning if errorCode not used.                */
    errorCode = errorCode;

    /* `#START CyClockStartupError` */

    /* If we have a clock startup error (bad MHz crystal, PLL lock, etc)    */
    /* we will end up here to allow the customer to implement something to  */
    /* deal with the clock condition.                                       */

    /* `#END` */

    /* If nothing else, stop here since the clocks have not started         */
    /* correctly.                                                           */
    while(1) {}
}


#undef CYCODE
#undef CYDATA
#undef CYXDATA
#undef CYFAR
#if defined(__C51__) || defined(__CX51__)
	#define CYCODE code
	#define CYDATA data
	#define CYXDATA xdata
	#define CYFAR far

	#define CYPACKED
	#define CYALIGNED
    
	#define CY_CFG_MEMORY_BARRIER()

	#ifndef CYCONFIGCPY_DECLARED
		extern void cymemzero(void CYFAR *addr, uint16 size);
		extern void cyconfigcpy(uint16 size, const void CYFAR *src, void CYFAR *dest) small;
		extern void cyconfigcpycode(uint16 size, const void CYCODE *src, void CYFAR *dest);
	#endif


	#define CYMEMZERO(a,c) cymemzero((a),(c))
	#define CYCONFIGCPY(d,s,c) cyconfigcpy((c),(s),(d))
	#define CYCONFIGCPYCODE(d,s,c) cyconfigcpycode((c),(s),(d))
#else
	#error Unsupported toolchain
#endif

/* Defines the layout and meaning of each entry in the cfg_memset_list used for clearing registers */
typedef struct {
	void CYFAR *address;
	uint16 size;
} CYPACKED cfg_memset_t;

/* Defines the layout and meaning of each entry in the cfg_memcpy_list used for initializing registers */
typedef struct {
	void CYFAR *dest;
	const void CYFAR *src;
	uint16 size;
} CYPACKED cfg_memcpy_t;

/* Contains the regions of memory that must be set to 0 during configuration */
#define CFG_MEMSET_COUNT (sizeof(cfg_memset_list)/sizeof(*cfg_memset_list))
static const cfg_memset_t CYCODE cfg_memset_list [] = {
	/* address, size */
	{(void CYFAR *)(CYREG_TMR0_CFG0), 48},
	{(void CYFAR *)(CYREG_PRT4_DR), 16},
	{(void CYFAR *)(CYREG_PRT6_DR), 16},
	{(void CYFAR *)(CYREG_PRT12_DR), 16},
	{(void CYFAR *)(CYREG_PRT15_DR), 16},
	{(void CYFAR *)(CYDEV_UCFG_B0_P0_U0_BASE), 4096},
	{(void CYFAR *)(CYDEV_UCFG_B1_P2_U0_BASE), 2048},
	{(void CYFAR *)(CYDEV_UCFG_DSI0_BASE), 2560},
	{(void CYFAR *)(CYDEV_UCFG_DSI12_BASE), 512},
	{(void CYFAR *)(CYREG_BCTL0_MDCLK_EN), 32},
};

#define cfg_byte_table ((const void CYFAR *)0x080000)
/* IOPINS0_0 Address: CYREG_PRT0_DM0 Size (bytes): 8 */
#define BS_IOPINS0_0_VAL ((const uint8 CYFAR *)0x00080624)

/* IOPINS0_1 Address: CYREG_PRT1_DM0 Size (bytes): 8 */
#define BS_IOPINS0_1_VAL ((const uint8 CYFAR *)0x0008062C)

/* IOPINS0_2 Address: CYREG_PRT2_DM0 Size (bytes): 8 */
#define BS_IOPINS0_2_VAL ((const uint8 CYFAR *)0x00080634)

/* IOPINS0_3 Address: CYREG_PRT3_DM0 Size (bytes): 8 */
#define BS_IOPINS0_3_VAL ((const uint8 CYFAR *)0x0008063C)

/* IOPINS0_5 Address: CYREG_PRT5_DM0 Size (bytes): 8 */
#define BS_IOPINS0_5_VAL ((const uint8 CYFAR *)0x00080644)

/* CYDEV_CLKDIST_ACFG0_CFG0 Address: CYREG_CLKDIST_ACFG0_CFG0 Size (bytes): 4 */
#define BS_CYDEV_CLKDIST_ACFG0_CFG0_VAL ((const uint8 CYFAR *)0x0008064C)


extern void cfg_write_bytes_code(void CYCODE *table);
extern void cfg_write_bytes(void CYFAR *table);

/*******************************************************************************
* Function Name: ClockSetup
********************************************************************************
*
* Summary:
*  Performs the initialization of all of the clocks in the device based on the
*  settings in the Clock tab of the DWR.  This includes enabling the requested
*  clocks and setting the necessary dividers to produce the desired frequency. 
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
static void ClockSetup(void)
{
	reg32  timeout;
	reg32* timeout_p = &timeout;
	reg8   pllLock;


	/* Configure Digital Clocks based on settings from Clock DWR */
	CY_SET_XTND_REG24((void CYFAR *)(CYREG_CLKDIST_DCFG0_CFG0), 0x180002);
	CY_SET_XTND_REG24((void CYFAR *)(CYREG_CLKDIST_DCFG1_CFG0), 0x180017);
	CY_SET_XTND_REG24((void CYFAR *)(CYREG_CLKDIST_DCFG2_CFG0), 0x180017);
	CY_SET_XTND_REG24((void CYFAR *)(CYREG_CLKDIST_DCFG3_CFG0), 0x180017);
	CY_SET_XTND_REG24((void CYFAR *)(CYREG_CLKDIST_DCFG4_CFG0), 0x180017);
	CY_SET_XTND_REG24((void CYFAR *)(CYREG_CLKDIST_DCFG5_CFG0), 0x180017);
	CY_SET_XTND_REG24((void CYFAR *)(CYREG_CLKDIST_DCFG6_CFG0), 0x190BB7);

	/* Configure Analog Clocks based on settings from Clock DWR */
	CYCONFIGCPY((void CYFAR *)(CYREG_CLKDIST_ACFG0_CFG0), (void CYFAR *)(BS_CYDEV_CLKDIST_ACFG0_CFG0_VAL), 4);

	/* Configure ILO based on settings from Clock DWR */
	CY_SET_REG8((void CYXDATA *)(CYREG_SLOWCLK_ILO_CR0), 0x02);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_CR), 0x08);

	/* Configure IMO based on settings from Clock DWR */
	CY_SET_REG8((void CYXDATA *)(CYREG_FASTCLK_IMO_CR), 0x03);
	CY_SET_REG8((void CYXDATA *)(CYREG_IMO_TR1), (CY_GET_XTND_REG8(CYREG_FLSHID_CUST_TABLES_IMO_3MHZ)));

	/* Configure PLL based on settings from Clock DWR */
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_FASTCLK_PLL_P), 0x0008);
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_FASTCLK_PLL_CFG0), 0x1051);
	/* Wait up to 250us for the PLL to lock */
	pllLock = 0;
	for (timeout = 250 / 10; *timeout_p && (pllLock != 0x03u); timeout--) { 
		pllLock = 0x03u & ((pllLock << 1) | ((CY_GET_REG8(CYREG_FASTCLK_PLL_SR) & 0x01u) >> 0));
		CyDelayCycles(10 * 48); /* Delay 10us based on 48MHz clock */
	}

	/* Configure Bus/Master Clock based on settings from Clock DWR */
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_MSTR0), 0x0100);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_MSTR0), 0x07);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_BCFG0), 0x00);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_BCFG2), 0x48);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_MSTR0), 0x00);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_LD), 0x02);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_DLY1), 0x04);

	CY_SET_REG8((void CYXDATA *)(CYREG_PM_ACT_CFG2), ((CY_GET_REG8(CYREG_PM_ACT_CFG2) | 0x7F)));
	CY_SET_REG8((void CYXDATA *)(CYREG_PM_ACT_CFG1), ((CY_GET_REG8(CYREG_PM_ACT_CFG1) | 0x01)));
	CY_SET_REG8((void CYXDATA *)(CYREG_PM_ACT_CFG0), ((CY_GET_REG8(CYREG_PM_ACT_CFG0) | 0x80)));
}


/* Analog API Functions */

/*******************************************************************************
* Function Name: AnalogSetDefault
********************************************************************************
*
* Summary:
*  Sets up the analog portions of the chip to default values based on chip
*  configuration options from the project.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AnalogSetDefault(void)
{
	uint8 bg_xover_inl_trim = CY_GET_XTND_REG8(CYREG_FLSHID_MFG_CFG_BG_XOVER_INL_TRIM + 1u);
	CY_SET_REG8(CYREG_BG_DFT0, bg_xover_inl_trim & 0x07u);
	CY_SET_REG8(CYREG_BG_DFT1, (bg_xover_inl_trim >> 4) & 0x0Fu);
	CY_SET_REG8(CYREG_PRT1_AG, 0x04);
	CY_SET_REG8(CYREG_PRT5_AG, 0x02);
	CY_SET_REG8(CYREG_DSM0_SW0, 0x06);
	CY_SET_REG8(CYREG_BUS_SW0, 0x06);
	CY_SET_REG8(CYREG_PUMP_CR0, 0x44);
}


/*******************************************************************************
* Function Name: SetAnalogRoutingPumps
********************************************************************************
*
* Summary:
* Enables or disables the analog pumps feeding analog routing switches.
* Intended to be called at startup, based on the Vdda system configuration;
* may be called during operation when the user informs us that the Vdda voltage crossed the pump threshold.
*
* Parameters:
*  enabled - 1 to enable the pumps, 0 to disable the pumps
*
* Return:
*  void
*
*******************************************************************************/
void SetAnalogRoutingPumps(uint8 enabled)
{
	uint8 regValue = CY_GET_REG8(CYREG_PUMP_CR0);
	if (enabled)
		regValue |= 0x02;
	else
		regValue &= ~0x02;
	CY_SET_REG8(CYREG_PUMP_CR0, regValue);
}

#define CY_AMUX_UNUSED CYREG_BOOST_SR
/* Table used to specify registers used to implement ADC_AMux */
uint8 CYXDATA * const CYCODE ADC_AMux__addrTable[] = {
	(uint8 CYXDATA *)CYREG_DSM0_SW3, 
	(uint8 CYXDATA *)CYREG_DSM0_SW3, 
};

/* Table used to define bit masks used to enable inputs for ADC_AMux */
const uint8 CYCODE ADC_AMux__maskTable[] = {
	0x40, 
	0x40, 
};

/*******************************************************************************
* Function Name: ADC_AMux_Set
********************************************************************************
* Summary:
*  This function is used to set a particular channel as active on the AMux.
*
* Parameters:  
*   channel - The mux channel input to set as active
*
* Return:
*   void
*
*******************************************************************************/
void ADC_AMux_Set(uint8 channel)
{
	if (channel >= 2)
		return;
	*ADC_AMux__addrTable[channel] |= ADC_AMux__maskTable[channel];
}

/*******************************************************************************
* Function Name: ADC_AMux_Unset
********************************************************************************
* Summary:
*  This function is used to clear a particular channel from being active on the
*  AMux.
*
* Parameters:  
*   channel - The mux channel input to mark inactive
*
* Return:
*   void
*
*******************************************************************************/
void ADC_AMux_Unset(uint8 channel)
{
	if (channel >= 2)
		return;
	*ADC_AMux__addrTable[channel] &= ~ADC_AMux__maskTable[channel];
}



/*******************************************************************************
* Function Name: cyfitter_cfg
********************************************************************************
* Summary:
*  This function is called by the start-up code for the selected device. It
*  performs all of the necessary device configuration based on the design
*  settings.  This includes settings from the Design Wide Resources (DWR) such
*  as Clocks and Pins as well as any component configuration that is necessary.
*
* Parameters:  
*   void
*
* Return:
*   void
*
*******************************************************************************/
void cyfitter_cfg(void)
{
	/* Enable/Disable Debug functionality based on settings from System DWR */
	CY_SET_XTND_REG8(CYREG_MLOGIC_DEBUG, (CY_GET_XTND_REG8(CYREG_MLOGIC_DEBUG) | 0x05));

	{
		uint8 CYDATA i;

		/* Zero out critical memory blocks before beginning configuration */
		for (i = 0; i < CFG_MEMSET_COUNT; i++)
		{
			const cfg_memset_t CYCODE * CYDATA ms = &cfg_memset_list[i];
			CYMEMZERO(ms->address, ms->size);
		}

		cfg_write_bytes(cfg_byte_table);

		/* Enable digital routing */
		CY_SET_XTND_REG8(CYREG_BCTL0_BANK_CTL, CY_GET_XTND_REG8(CYREG_BCTL0_BANK_CTL) | 0x02u);
		CY_SET_XTND_REG8(CYREG_BCTL1_BANK_CTL, CY_GET_XTND_REG8(CYREG_BCTL1_BANK_CTL) | 0x02u);

		/* Enable UDB array */
		CY_SET_REG8(CYREG_PM_ACT_CFG0, CY_GET_REG8(CYREG_PM_ACT_CFG0) | 0x40u);
		CY_SET_REG8(CYREG_PM_AVAIL_CR2, CY_GET_REG8(CYREG_PM_AVAIL_CR2) | 0x10u);
	}

	/* Perform second pass device configuration. These items must be configured in specific order after the regular configuration is done. */
	CYCONFIGCPY((void CYFAR *)(CYREG_PRT0_DM0), (void CYFAR *)(BS_IOPINS0_0_VAL), 8);
	CYCONFIGCPY((void CYFAR *)(CYREG_PRT1_DM0), (void CYFAR *)(BS_IOPINS0_1_VAL), 8);
	CYCONFIGCPY((void CYFAR *)(CYREG_PRT2_DM0), (void CYFAR *)(BS_IOPINS0_2_VAL), 8);
	CYCONFIGCPY((void CYFAR *)(CYREG_PRT3_DM0), (void CYFAR *)(BS_IOPINS0_3_VAL), 8);
	CYCONFIGCPY((void CYFAR *)(CYREG_PRT5_DM0), (void CYFAR *)(BS_IOPINS0_5_VAL), 8);
	CY_SET_REG8((void CYXDATA *)(CYREG_INTC_CSR_EN), 0x01);

	if (CYDEV_CHIP_REV_ACTUAL < 5)
	{
		CY_SET_REG8(CYDEV_MFGCFG_PWRSYS_WAKE_TR2, 0x3A);
	}


	/* Set Flash Cycles based on max possible frequency in case a glitch occurs during ClockSetup(). */
	CY_SET_REG8((void CYXDATA *)(CYREG_CACHE_CR), ((CYDEV_INSTRUCT_CACHE_ENABLED) ? 0xF1 : 0xC0));
	/* Setup clocks based on selections from Clock DWR */
	ClockSetup();
	/* Set Flash Cycles based on newly configured 24.00MHz Bus Clock. */
	CY_SET_REG8((void CYXDATA *)(CYREG_CACHE_CR), ((CYDEV_INSTRUCT_CACHE_ENABLED) ? 0xB1 : 0x80));

	/* Perform basic analog initialization to defaults */
	AnalogSetDefault();

	/* Configure alternate active mode */
	CYCONFIGCPY((void CYFAR *)CYDEV_PM_STBY_BASE, (void CYFAR *)CYDEV_PM_ACT_BASE, 14);
	CY_SET_REG8(CYREG_PM_STBY_CFG0, CY_GET_REG8(CYREG_PM_STBY_CFG0) & ~0x02u);	/* Disable CPU */
}
