/*******************************************************************************
* File Name: Pixy_UART.h
* Version 2.20
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include "cytypes.h"
#include "cyfitter.h"

#if !defined(CY_UART_Pixy_UART_H)
#define CY_UART_Pixy_UART_H


/***************************************
* Conditional Compilation Parameters
***************************************/

#define Pixy_UART_RX_ENABLED                     (1u)
#define Pixy_UART_TX_ENABLED                     (0u)
#define Pixy_UART_HD_ENABLED                     (0u)
#define Pixy_UART_RX_INTERRUPT_ENABLED           (0u)
#define Pixy_UART_TX_INTERRUPT_ENABLED           (0u)
#define Pixy_UART_INTERNAL_CLOCK_USED            (1u)
#define Pixy_UART_RXHW_ADDRESS_ENABLED           (0u)
#define Pixy_UART_OVER_SAMPLE_COUNT              (8u)
#define Pixy_UART_PARITY_TYPE                    (0u)
#define Pixy_UART_PARITY_TYPE_SW                 (0u)
#define Pixy_UART_BREAK_DETECT                   (0u)
#define Pixy_UART_BREAK_BITS_TX                  (13u)
#define Pixy_UART_BREAK_BITS_RX                  (13u)
#define Pixy_UART_TXCLKGEN_DP                    (1u)
#define Pixy_UART_USE23POLLING                   (1u)
#define Pixy_UART_FLOW_CONTROL                   (0u)
#define Pixy_UART_CLK_FREQ                       (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#ifdef Pixy_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Pixy_UART_CONTROL_REG_REMOVED            (0u)
#else
    #define Pixy_UART_CONTROL_REG_REMOVED            (1u)
#endif /* End Pixy_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct _Pixy_UART_backupStruct
{
    uint8 enableState;

    #if(Pixy_UART_CONTROL_REG_REMOVED == 0u)
        uint8 cr;            
    #endif /* End Pixy_UART_CONTROL_REG_REMOVED */    
    #if( (Pixy_UART_RX_ENABLED) || (Pixy_UART_HD_ENABLED) )
        uint8 rx_period;
        #if (CY_UDB_V0) 
            uint8 rx_mask;
            #if (Pixy_UART_RXHW_ADDRESS_ENABLED)
                uint8 rx_addr1;
                uint8 rx_addr2;
            #endif /* End Pixy_UART_RXHW_ADDRESS_ENABLED */
        #endif /* End CY_UDB_V0 */
    #endif  /* End (Pixy_UART_RX_ENABLED) || (Pixy_UART_HD_ENABLED)*/

    #if(Pixy_UART_TX_ENABLED)
        #if(Pixy_UART_TXCLKGEN_DP)
            uint8 tx_clk_ctr;
            #if (CY_UDB_V0) 
                uint8 tx_clk_compl;
            #endif  /* End CY_UDB_V0 */
        #else
            uint8 tx_period;
        #endif /*End Pixy_UART_TXCLKGEN_DP */
        #if (CY_UDB_V0) 
            uint8 tx_mask;
        #endif  /* End CY_UDB_V0 */
    #endif /*End Pixy_UART_TX_ENABLED */
} Pixy_UART_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void Pixy_UART_Start(void) ;
void Pixy_UART_Stop(void) ;
uint8 Pixy_UART_ReadControlRegister(void) ;
void Pixy_UART_WriteControlRegister(uint8 control) ;

void Pixy_UART_Init(void) ;
void Pixy_UART_Enable(void) ;
void Pixy_UART_SaveConfig(void) ;
void Pixy_UART_RestoreConfig(void) ;
void Pixy_UART_Sleep(void) ;
void Pixy_UART_Wakeup(void) ;

/* Only if RX is enabled */
#if( (Pixy_UART_RX_ENABLED) || (Pixy_UART_HD_ENABLED) )

    #if(Pixy_UART_RX_INTERRUPT_ENABLED)
        void  Pixy_UART_EnableRxInt(void) ;
        void  Pixy_UART_DisableRxInt(void) ;
        CY_ISR_PROTO(Pixy_UART_RXISR);
    #endif /* Pixy_UART_RX_INTERRUPT_ENABLED */

    void Pixy_UART_SetRxAddressMode(uint8 addressMode) 
                                                           ;
    void Pixy_UART_SetRxAddress1(uint8 address) ;
    void Pixy_UART_SetRxAddress2(uint8 address) ;

    void  Pixy_UART_SetRxInterruptMode(uint8 intSrc) ;
    uint8 Pixy_UART_ReadRxData(void) ;
    uint8 Pixy_UART_ReadRxStatus(void) ;
    uint8 Pixy_UART_GetChar(void) ;
    uint16 Pixy_UART_GetByte(void) ;
    uint8 Pixy_UART_GetRxBufferSize(void)  
                                                            ;
    void Pixy_UART_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define Pixy_UART_GetRxInterruptSource   Pixy_UART_ReadRxStatus

#endif /* End (Pixy_UART_RX_ENABLED) || (Pixy_UART_HD_ENABLED) */

/* Only if TX is enabled */
#if(Pixy_UART_TX_ENABLED || Pixy_UART_HD_ENABLED)

    #if(Pixy_UART_TX_INTERRUPT_ENABLED)
        void Pixy_UART_EnableTxInt(void) ;
        void Pixy_UART_DisableTxInt(void) ;
        CY_ISR_PROTO(Pixy_UART_TXISR);
    #endif /* Pixy_UART_TX_INTERRUPT_ENABLED */

    void Pixy_UART_SetTxInterruptMode(uint8 intSrc) ;
    void Pixy_UART_WriteTxData(uint8 txDataByte) ;
    uint8 Pixy_UART_ReadTxStatus(void) ;
    void Pixy_UART_PutChar(uint8 txDataByte) ;
    void Pixy_UART_PutString(char* string) ;
    void Pixy_UART_PutArray(uint8* string, uint8 byteCount)
                                                            ;
    void Pixy_UART_PutCRLF(uint8 txDataByte) ;
    void Pixy_UART_ClearTxBuffer(void) ;
    void Pixy_UART_SetTxAddressMode(uint8 addressMode) ;
    void Pixy_UART_SendBreak(uint8 retMode) ;
    uint8 Pixy_UART_GetTxBufferSize(void) 
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define Pixy_UART_PutStringConst         Pixy_UART_PutString
    #define Pixy_UART_PutArrayConst          Pixy_UART_PutArray
    #define Pixy_UART_GetTxInterruptSource   Pixy_UART_ReadTxStatus
    
#endif /* End Pixy_UART_TX_ENABLED || Pixy_UART_HD_ENABLED */

#if(Pixy_UART_HD_ENABLED)
    void Pixy_UART_LoadRxConfig(void) ;
    void Pixy_UART_LoadTxConfig(void) ;
#endif /* End Pixy_UART_HD_ENABLED */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define Pixy_UART_SET_SPACE                              (0x00u)
#define Pixy_UART_SET_MARK                               (0x01u)

/* Status Register definitions */
#if( (Pixy_UART_TX_ENABLED) || (Pixy_UART_HD_ENABLED) )
    #if(Pixy_UART_TX_INTERRUPT_ENABLED)
        #define Pixy_UART_TX_VECT_NUM                Pixy_UART_TXInternalInterrupt__INTC_NUMBER
        #define Pixy_UART_TX_PRIOR_NUM               Pixy_UART_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* Pixy_UART_TX_INTERRUPT_ENABLED */
    #if(Pixy_UART_TX_ENABLED) 
        #define Pixy_UART_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define Pixy_UART_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define Pixy_UART_TX_STS_FIFO_FULL_SHIFT         (0x02u)
        #define Pixy_UART_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* Pixy_UART_TX_ENABLED */
    #if(Pixy_UART_HD_ENABLED) 
        #define Pixy_UART_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define Pixy_UART_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define Pixy_UART_TX_STS_FIFO_FULL_SHIFT         (0x05u)  /*needs MD=0*/
        #define Pixy_UART_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* Pixy_UART_HD_ENABLED */
    #define Pixy_UART_TX_STS_COMPLETE                (0x01u << Pixy_UART_TX_STS_COMPLETE_SHIFT)
    #define Pixy_UART_TX_STS_FIFO_EMPTY              (0x01u << Pixy_UART_TX_STS_FIFO_EMPTY_SHIFT)
    #define Pixy_UART_TX_STS_FIFO_FULL               (0x01u << Pixy_UART_TX_STS_FIFO_FULL_SHIFT)
    #define Pixy_UART_TX_STS_FIFO_NOT_FULL           (0x01u << Pixy_UART_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (Pixy_UART_TX_ENABLED) || (Pixy_UART_HD_ENABLED)*/

#if( (Pixy_UART_RX_ENABLED) || (Pixy_UART_HD_ENABLED) )
    #if(Pixy_UART_RX_INTERRUPT_ENABLED)
        #define Pixy_UART_RX_VECT_NUM                Pixy_UART_RXInternalInterrupt__INTC_NUMBER
        #define Pixy_UART_RX_PRIOR_NUM               Pixy_UART_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* Pixy_UART_RX_INTERRUPT_ENABLED */
    #define Pixy_UART_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define Pixy_UART_RX_STS_BREAK_SHIFT             (0x01u)
    #define Pixy_UART_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define Pixy_UART_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define Pixy_UART_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define Pixy_UART_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define Pixy_UART_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define Pixy_UART_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define Pixy_UART_RX_STS_MRKSPC                  (0x01u << Pixy_UART_RX_STS_MRKSPC_SHIFT)
    #define Pixy_UART_RX_STS_BREAK                   (0x01u << Pixy_UART_RX_STS_BREAK_SHIFT)
    #define Pixy_UART_RX_STS_PAR_ERROR               (0x01u << Pixy_UART_RX_STS_PAR_ERROR_SHIFT)
    #define Pixy_UART_RX_STS_STOP_ERROR              (0x01u << Pixy_UART_RX_STS_STOP_ERROR_SHIFT)
    #define Pixy_UART_RX_STS_OVERRUN                 (0x01u << Pixy_UART_RX_STS_OVERRUN_SHIFT)
    #define Pixy_UART_RX_STS_FIFO_NOTEMPTY           (0x01u << Pixy_UART_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define Pixy_UART_RX_STS_ADDR_MATCH              (0x01u << Pixy_UART_RX_STS_ADDR_MATCH_SHIFT)
    #define Pixy_UART_RX_STS_SOFT_BUFF_OVER          (0x01u << Pixy_UART_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define Pixy_UART_RX_HW_MASK                     (0x7Fu)
#endif /* End (Pixy_UART_RX_ENABLED) || (Pixy_UART_HD_ENABLED) */

/* Control Register definitions */
#define Pixy_UART_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define Pixy_UART_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define Pixy_UART_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define Pixy_UART_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define Pixy_UART_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define Pixy_UART_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define Pixy_UART_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define Pixy_UART_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define Pixy_UART_CTRL_HD_SEND                       (0x01u << Pixy_UART_CTRL_HD_SEND_SHIFT)
#define Pixy_UART_CTRL_HD_SEND_BREAK                 (0x01u << Pixy_UART_CTRL_HD_SEND_BREAK_SHIFT)
#define Pixy_UART_CTRL_MARK                          (0x01u << Pixy_UART_CTRL_MARK_SHIFT)
#define Pixy_UART_CTRL_PARITY_TYPE_MASK              (0x03u << Pixy_UART_CTRL_PARITY_TYPE0_SHIFT)
#define Pixy_UART_CTRL_RXADDR_MODE_MASK              (0x07u << Pixy_UART_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define Pixy_UART_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define Pixy_UART_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define Pixy_UART_SEND_BREAK                         (0x00u)
#define Pixy_UART_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define Pixy_UART_REINIT                             (0x02u)
#define Pixy_UART_SEND_WAIT_REINIT                   (0x03u)

#define Pixy_UART_OVER_SAMPLE_8                      (8u)
#define Pixy_UART_OVER_SAMPLE_16                     (16u)

#define Pixy_UART_BIT_CENTER                         (Pixy_UART_OVER_SAMPLE_COUNT - 1u)

#define Pixy_UART_FIFO_LENGTH                        (4u)
#define Pixy_UART_NUMBER_OF_START_BIT                (1u)

/* 8X always for count7 implementation*/
#define Pixy_UART_TXBITCTR_BREAKBITS8X   (Pixy_UART_BREAK_BITS_TX * Pixy_UART_OVER_SAMPLE_8 - 1u)
/* 8X or 16X for DP implementation*/
#define Pixy_UART_TXBITCTR_BREAKBITS   (Pixy_UART_BREAK_BITS_TX * Pixy_UART_OVER_SAMPLE_COUNT - 1u)

#if (Pixy_UART_OVER_SAMPLE_COUNT == Pixy_UART_OVER_SAMPLE_8)
    #define Pixy_UART_HD_TXBITCTR_INIT   ((Pixy_UART_BREAK_BITS_TX + \
        Pixy_UART_NUMBER_OF_START_BIT) * Pixy_UART_OVER_SAMPLE_COUNT - 1u)
    /* This parameter is increased on the 1 in 2 out of 3 mode to sample voting in the middle */
    #define Pixy_UART_HD_RXBITCTR_INIT   ((Pixy_UART_BREAK_BITS_RX + \
    Pixy_UART_NUMBER_OF_START_BIT) * Pixy_UART_OVER_SAMPLE_COUNT - 1u + \
    (Pixy_UART_OVER_SAMPLE_COUNT / 2u) + (Pixy_UART_USE23POLLING * 2u) - 1u)
#else /* Pixy_UART_OVER_SAMPLE_COUNT == Pixy_UART_OVER_SAMPLE_16 */
    #define Pixy_UART_HD_TXBITCTR_INIT   (8u * Pixy_UART_OVER_SAMPLE_COUNT - 1u)
    #define Pixy_UART_HD_RXBITCTR_INIT   (7u * Pixy_UART_OVER_SAMPLE_COUNT - 1u  +  \
       (Pixy_UART_OVER_SAMPLE_COUNT / 2u) + (Pixy_UART_USE23POLLING * 2u) - 1u)
#endif /* End Pixy_UART_OVER_SAMPLE_COUNT */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define Pixy_UART__B_UART__AM_SW_BYTE_BYTE 1
#define Pixy_UART__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define Pixy_UART__B_UART__AM_HW_BYTE_BY_BYTE 3
#define Pixy_UART__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define Pixy_UART__B_UART__AM_NONE 0

#define Pixy_UART__B_UART__NONE_REVB 0
#define Pixy_UART__B_UART__EVEN_REVB 1
#define Pixy_UART__B_UART__ODD_REVB 2
#define Pixy_UART__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

#define Pixy_UART_TXBUFFERSIZE           (4u)
#define Pixy_UART_RXBUFFERSIZE           (4u)
/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define Pixy_UART_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define Pixy_UART_NUMBER_OF_STOP_BITS    (1u)

#if (Pixy_UART_RXHW_ADDRESS_ENABLED)
    #define Pixy_UART_RXADDRESSMODE      (0u)
    #define Pixy_UART_RXHWADDRESS1       (0u)
    #define Pixy_UART_RXHWADDRESS2       (0u)
    /* Backward compatible define */
    #define Pixy_UART_RXAddressMode      Pixy_UART_RXADDRESSMODE
#endif /* End EnableHWAddress */

#define Pixy_UART_INIT_RX_INTERRUPTS_MASK \
                                          (1 << Pixy_UART_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << Pixy_UART_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << Pixy_UART_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << Pixy_UART_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << Pixy_UART_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << Pixy_UART_RX_STS_BREAK_SHIFT) \
                                        | (0 << Pixy_UART_RX_STS_OVERRUN_SHIFT)

#define Pixy_UART_INIT_TX_INTERRUPTS_MASK \
                                          (0 << Pixy_UART_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << Pixy_UART_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << Pixy_UART_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << Pixy_UART_TX_STS_FIFO_NOT_FULL_SHIFT)


/***************************************
*              Registers
***************************************/

#ifdef Pixy_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Pixy_UART_CONTROL_REG \
                            (* (reg8 *) Pixy_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define Pixy_UART_CONTROL_PTR \
                            (  (reg8 *) Pixy_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End Pixy_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(Pixy_UART_TX_ENABLED)
    #define Pixy_UART_TXDATA_REG          (* (reg8 *) Pixy_UART_BUART_sTX_TxShifter_u0__F0_REG)
    #define Pixy_UART_TXDATA_PTR          (  (reg8 *) Pixy_UART_BUART_sTX_TxShifter_u0__F0_REG)
    #define Pixy_UART_TXDATA_AUX_CTL_REG  (* (reg8 *) Pixy_UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define Pixy_UART_TXDATA_AUX_CTL_PTR  (  (reg8 *) Pixy_UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define Pixy_UART_TXSTATUS_REG        (* (reg8 *) Pixy_UART_BUART_sTX_TxSts__STATUS_REG)
    #define Pixy_UART_TXSTATUS_PTR        (  (reg8 *) Pixy_UART_BUART_sTX_TxSts__STATUS_REG)
    #define Pixy_UART_TXSTATUS_MASK_REG   (* (reg8 *) Pixy_UART_BUART_sTX_TxSts__MASK_REG)
    #define Pixy_UART_TXSTATUS_MASK_PTR   (  (reg8 *) Pixy_UART_BUART_sTX_TxSts__MASK_REG)
    #define Pixy_UART_TXSTATUS_ACTL_REG   (* (reg8 *) Pixy_UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define Pixy_UART_TXSTATUS_ACTL_PTR   (  (reg8 *) Pixy_UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(Pixy_UART_TXCLKGEN_DP)
        #define Pixy_UART_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) Pixy_UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define Pixy_UART_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) Pixy_UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define Pixy_UART_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) Pixy_UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define Pixy_UART_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) Pixy_UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define Pixy_UART_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) Pixy_UART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define Pixy_UART_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) Pixy_UART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define Pixy_UART_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) Pixy_UART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define Pixy_UART_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) Pixy_UART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define Pixy_UART_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) Pixy_UART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define Pixy_UART_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) Pixy_UART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* Pixy_UART_TXCLKGEN_DP */

#endif /* End Pixy_UART_TX_ENABLED */

#if(Pixy_UART_HD_ENABLED)

    #define Pixy_UART_TXDATA_REG             (* (reg8 *) Pixy_UART_BUART_sRX_RxShifter_u0__F1_REG )
    #define Pixy_UART_TXDATA_PTR             (  (reg8 *) Pixy_UART_BUART_sRX_RxShifter_u0__F1_REG )
    #define Pixy_UART_TXDATA_AUX_CTL_REG     (* (reg8 *) Pixy_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define Pixy_UART_TXDATA_AUX_CTL_PTR     (  (reg8 *) Pixy_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define Pixy_UART_TXSTATUS_REG           (* (reg8 *) Pixy_UART_BUART_sRX_RxSts__STATUS_REG )
    #define Pixy_UART_TXSTATUS_PTR           (  (reg8 *) Pixy_UART_BUART_sRX_RxSts__STATUS_REG )
    #define Pixy_UART_TXSTATUS_MASK_REG      (* (reg8 *) Pixy_UART_BUART_sRX_RxSts__MASK_REG )
    #define Pixy_UART_TXSTATUS_MASK_PTR      (  (reg8 *) Pixy_UART_BUART_sRX_RxSts__MASK_REG )
    #define Pixy_UART_TXSTATUS_ACTL_REG      (* (reg8 *) Pixy_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define Pixy_UART_TXSTATUS_ACTL_PTR      (  (reg8 *) Pixy_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End Pixy_UART_HD_ENABLED */

#if( (Pixy_UART_RX_ENABLED) || (Pixy_UART_HD_ENABLED) )
    #define Pixy_UART_RXDATA_REG             (* (reg8 *) Pixy_UART_BUART_sRX_RxShifter_u0__F0_REG )
    #define Pixy_UART_RXDATA_PTR             (  (reg8 *) Pixy_UART_BUART_sRX_RxShifter_u0__F0_REG )
    #define Pixy_UART_RXADDRESS1_REG         (* (reg8 *) Pixy_UART_BUART_sRX_RxShifter_u0__D0_REG )
    #define Pixy_UART_RXADDRESS1_PTR         (  (reg8 *) Pixy_UART_BUART_sRX_RxShifter_u0__D0_REG )
    #define Pixy_UART_RXADDRESS2_REG         (* (reg8 *) Pixy_UART_BUART_sRX_RxShifter_u0__D1_REG )
    #define Pixy_UART_RXADDRESS2_PTR         (  (reg8 *) Pixy_UART_BUART_sRX_RxShifter_u0__D1_REG )
    #define Pixy_UART_RXDATA_AUX_CTL_REG     (* (reg8 *) Pixy_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define Pixy_UART_RXBITCTR_PERIOD_REG    (* (reg8 *) Pixy_UART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define Pixy_UART_RXBITCTR_PERIOD_PTR    (  (reg8 *) Pixy_UART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define Pixy_UART_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) Pixy_UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define Pixy_UART_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) Pixy_UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define Pixy_UART_RXBITCTR_COUNTER_REG   (* (reg8 *) Pixy_UART_BUART_sRX_RxBitCounter__COUNT_REG )
    #define Pixy_UART_RXBITCTR_COUNTER_PTR   (  (reg8 *) Pixy_UART_BUART_sRX_RxBitCounter__COUNT_REG )

    #define Pixy_UART_RXSTATUS_REG           (* (reg8 *) Pixy_UART_BUART_sRX_RxSts__STATUS_REG )
    #define Pixy_UART_RXSTATUS_PTR           (  (reg8 *) Pixy_UART_BUART_sRX_RxSts__STATUS_REG )
    #define Pixy_UART_RXSTATUS_MASK_REG      (* (reg8 *) Pixy_UART_BUART_sRX_RxSts__MASK_REG )
    #define Pixy_UART_RXSTATUS_MASK_PTR      (  (reg8 *) Pixy_UART_BUART_sRX_RxSts__MASK_REG )
    #define Pixy_UART_RXSTATUS_ACTL_REG      (* (reg8 *) Pixy_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define Pixy_UART_RXSTATUS_ACTL_PTR      (  (reg8 *) Pixy_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (Pixy_UART_RX_ENABLED) || (Pixy_UART_HD_ENABLED) */

#if(Pixy_UART_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define Pixy_UART_INTCLOCK_CLKEN_REG     (* (reg8 *) Pixy_UART_IntClock__PM_ACT_CFG)
    #define Pixy_UART_INTCLOCK_CLKEN_PTR     (  (reg8 *) Pixy_UART_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define Pixy_UART_INTCLOCK_CLKEN_MASK    Pixy_UART_IntClock__PM_ACT_MSK
#endif /* End Pixy_UART_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants              
***************************************/

#if(Pixy_UART_TX_ENABLED)
    #define Pixy_UART_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End Pixy_UART_TX_ENABLED */

#if(Pixy_UART_HD_ENABLED)
    #define Pixy_UART_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End Pixy_UART_HD_ENABLED */

#if( (Pixy_UART_RX_ENABLED) || (Pixy_UART_HD_ENABLED) )
    #define Pixy_UART_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (Pixy_UART_RX_ENABLED) || (Pixy_UART_HD_ENABLED) */


/***************************************
* Renamed global variables or defines 
* for backward compatible
***************************************/

#define Pixy_UART_initvar                    Pixy_UART_initVar

#define Pixy_UART_RX_Enabled                 Pixy_UART_RX_ENABLED
#define Pixy_UART_TX_Enabled                 Pixy_UART_TX_ENABLED
#define Pixy_UART_HD_Enabled                 Pixy_UART_HD_ENABLED
#define Pixy_UART_RX_IntInterruptEnabled     Pixy_UART_RX_INTERRUPT_ENABLED
#define Pixy_UART_TX_IntInterruptEnabled     Pixy_UART_TX_INTERRUPT_ENABLED
#define Pixy_UART_InternalClockUsed          Pixy_UART_INTERNAL_CLOCK_USED
#define Pixy_UART_RXHW_Address_Enabled       Pixy_UART_RXHW_ADDRESS_ENABLED
#define Pixy_UART_OverSampleCount            Pixy_UART_OVER_SAMPLE_COUNT
#define Pixy_UART_ParityType                 Pixy_UART_PARITY_TYPE

#if( Pixy_UART_TX_ENABLED && (Pixy_UART_TXBUFFERSIZE > Pixy_UART_FIFO_LENGTH))
    #define Pixy_UART_TXBUFFER               Pixy_UART_txBuffer
    #define Pixy_UART_TXBUFFERREAD           Pixy_UART_txBufferRead 
    #define Pixy_UART_TXBUFFERWRITE          Pixy_UART_txBufferWrite 
#endif /* End Pixy_UART_TX_ENABLED */
#if( ( Pixy_UART_RX_ENABLED || Pixy_UART_HD_ENABLED ) && \
     (Pixy_UART_RXBUFFERSIZE > Pixy_UART_FIFO_LENGTH) )
    #define Pixy_UART_RXBUFFER               Pixy_UART_rxBuffer
    #define Pixy_UART_RXBUFFERREAD           Pixy_UART_rxBufferRead 
    #define Pixy_UART_RXBUFFERWRITE          Pixy_UART_rxBufferWrite 
    #define Pixy_UART_RXBUFFERLOOPDETECT     Pixy_UART_rxBufferLoopDetect
    #define Pixy_UART_RXBUFFER_OVERFLOW      Pixy_UART_rxBufferOverflow
#endif /* End Pixy_UART_RX_ENABLED */

#ifdef Pixy_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Pixy_UART_CONTROL                Pixy_UART_CONTROL_REG 
#endif /* End Pixy_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(Pixy_UART_TX_ENABLED)
    #define Pixy_UART_TXDATA                 Pixy_UART_TXDATA_REG
    #define Pixy_UART_TXSTATUS               Pixy_UART_TXSTATUS_REG
    #define Pixy_UART_TXSTATUS_MASK          Pixy_UART_TXSTATUS_MASK_REG   
    #define Pixy_UART_TXSTATUS_ACTL          Pixy_UART_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(Pixy_UART_TXCLKGEN_DP)
        #define Pixy_UART_TXBITCLKGEN_CTR        Pixy_UART_TXBITCLKGEN_CTR_REG
        #define Pixy_UART_TXBITCLKTX_COMPLETE    Pixy_UART_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define Pixy_UART_TXBITCTR_PERIOD        Pixy_UART_TXBITCTR_PERIOD_REG
        #define Pixy_UART_TXBITCTR_CONTROL       Pixy_UART_TXBITCTR_CONTROL_REG
        #define Pixy_UART_TXBITCTR_COUNTER       Pixy_UART_TXBITCTR_COUNTER_REG
    #endif /* Pixy_UART_TXCLKGEN_DP */
#endif /* End Pixy_UART_TX_ENABLED */

#if(Pixy_UART_HD_ENABLED)
    #define Pixy_UART_TXDATA                 Pixy_UART_TXDATA_REG
    #define Pixy_UART_TXSTATUS               Pixy_UART_TXSTATUS_REG
    #define Pixy_UART_TXSTATUS_MASK          Pixy_UART_TXSTATUS_MASK_REG   
    #define Pixy_UART_TXSTATUS_ACTL          Pixy_UART_TXSTATUS_ACTL_REG
#endif /* End Pixy_UART_HD_ENABLED */

#if( (Pixy_UART_RX_ENABLED) || (Pixy_UART_HD_ENABLED) )
    #define Pixy_UART_RXDATA                 Pixy_UART_RXDATA_REG             
    #define Pixy_UART_RXADDRESS1             Pixy_UART_RXADDRESS1_REG
    #define Pixy_UART_RXADDRESS2             Pixy_UART_RXADDRESS2_REG
    #define Pixy_UART_RXBITCTR_PERIOD        Pixy_UART_RXBITCTR_PERIOD_REG
    #define Pixy_UART_RXBITCTR_CONTROL       Pixy_UART_RXBITCTR_CONTROL_REG
    #define Pixy_UART_RXBITCTR_COUNTER       Pixy_UART_RXBITCTR_COUNTER_REG
    #define Pixy_UART_RXSTATUS               Pixy_UART_RXSTATUS_REG
    #define Pixy_UART_RXSTATUS_MASK          Pixy_UART_RXSTATUS_MASK_REG
    #define Pixy_UART_RXSTATUS_ACTL          Pixy_UART_RXSTATUS_ACTL_REG
#endif /* End  (Pixy_UART_RX_ENABLED) || (Pixy_UART_HD_ENABLED) */

#if(Pixy_UART_INTERNAL_CLOCK_USED)
    #define Pixy_UART_INTCLOCK_CLKEN         Pixy_UART_INTCLOCK_CLKEN_REG
#endif /* End Pixy_UART_INTERNAL_CLOCK_USED */

#define Pixy_UART_WAIT_FOR_COMLETE_REINIT    Pixy_UART_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_Pixy_UART_H */


/* [] END OF FILE */
