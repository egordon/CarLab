/*******************************************************************************
* File Name: FR_H_Cmp.c  
* Version 1.70
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "FR_H_Cmp.h"


/*******************************************************************************
* Function Name: FR_H_Cmp_Write
********************************************************************************
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  void 
*  
*******************************************************************************/
void FR_H_Cmp_Write(uint8 value) 
{
    uint8 staticBits = FR_H_Cmp_DR & ~FR_H_Cmp_MASK;
    FR_H_Cmp_DR = staticBits | ((value << FR_H_Cmp_SHIFT) & FR_H_Cmp_MASK);
}


/*******************************************************************************
* Function Name: FR_H_Cmp_SetDriveMode
********************************************************************************
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  void
*
*******************************************************************************/
void FR_H_Cmp_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(FR_H_Cmp_0, mode);
}


/*******************************************************************************
* Function Name: FR_H_Cmp_Read
********************************************************************************
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro FR_H_Cmp_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 FR_H_Cmp_Read(void) 
{
    return (FR_H_Cmp_PS & FR_H_Cmp_MASK) >> FR_H_Cmp_SHIFT;
}


/*******************************************************************************
* Function Name: FR_H_Cmp_ReadDataReg
********************************************************************************
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 FR_H_Cmp_ReadDataReg(void) 
{
    return (FR_H_Cmp_DR & FR_H_Cmp_MASK) >> FR_H_Cmp_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(FR_H_Cmp_INTSTAT) 

    /*******************************************************************************
    * Function Name: FR_H_Cmp_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  void 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 FR_H_Cmp_ClearInterrupt(void) 
    {
        return (FR_H_Cmp_INTSTAT & FR_H_Cmp_MASK) >> FR_H_Cmp_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 
