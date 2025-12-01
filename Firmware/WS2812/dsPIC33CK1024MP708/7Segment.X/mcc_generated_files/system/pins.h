/**
 * PINS Generated Driver Header File 
 * 
 * @file      pins.h
 *            
 * @defgroup  pinsdriver Pins Driver
 *            
 * @brief     The Pin Driver directs the operation and function of 
 *            the selected device pins using dsPIC MCUs.
 *
 * @skipline @version   Firmware Driver Version 1.0.2
 *
 * @skipline @version   PLIB Version 1.4.1
 *
 * @skipline  Device : dsPIC33CK1024MP708
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H
// Section: Includes
#include <xc.h>

// Section: Device Pin Macros

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA0 GPIO Pin which has a custom name of LED0 to High
 * @pre      The RA0 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define LED0_SetHigh()          (_LATA0 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA0 GPIO Pin which has a custom name of LED0 to Low
 * @pre      The RA0 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define LED0_SetLow()           (_LATA0 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RA0 GPIO Pin which has a custom name of LED0
 * @pre      The RA0 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define LED0_Toggle()           (_LATA0 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RA0 GPIO Pin which has a custom name of LED0
 * @param    none
 * @return   none  
 */
#define LED0_GetValue()         _RA0

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA0 GPIO Pin which has a custom name of LED0 as Input
 * @param    none
 * @return   none  
 */
#define LED0_SetDigitalInput()  (_TRISA0 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA0 GPIO Pin which has a custom name of LED0 as Output
 * @param    none
 * @return   none  
 */
#define LED0_SetDigitalOutput() (_TRISA0 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA1 GPIO Pin which has a custom name of RTTC_CE to High
 * @pre      The RA1 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define RTTC_CE_SetHigh()          (_LATA1 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA1 GPIO Pin which has a custom name of RTTC_CE to Low
 * @pre      The RA1 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define RTTC_CE_SetLow()           (_LATA1 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RA1 GPIO Pin which has a custom name of RTTC_CE
 * @pre      The RA1 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define RTTC_CE_Toggle()           (_LATA1 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RA1 GPIO Pin which has a custom name of RTTC_CE
 * @param    none
 * @return   none  
 */
#define RTTC_CE_GetValue()         _RA1

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA1 GPIO Pin which has a custom name of RTTC_CE as Input
 * @param    none
 * @return   none  
 */
#define RTTC_CE_SetDigitalInput()  (_TRISA1 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA1 GPIO Pin which has a custom name of RTTC_CE as Output
 * @param    none
 * @return   none  
 */
#define RTTC_CE_SetDigitalOutput() (_TRISA1 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA2 GPIO Pin which has a custom name of RTTC_SCLK to High
 * @pre      The RA2 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define RTTC_SCLK_SetHigh()          (_LATA2 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA2 GPIO Pin which has a custom name of RTTC_SCLK to Low
 * @pre      The RA2 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define RTTC_SCLK_SetLow()           (_LATA2 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RA2 GPIO Pin which has a custom name of RTTC_SCLK
 * @pre      The RA2 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define RTTC_SCLK_Toggle()           (_LATA2 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RA2 GPIO Pin which has a custom name of RTTC_SCLK
 * @param    none
 * @return   none  
 */
#define RTTC_SCLK_GetValue()         _RA2

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA2 GPIO Pin which has a custom name of RTTC_SCLK as Input
 * @param    none
 * @return   none  
 */
#define RTTC_SCLK_SetDigitalInput()  (_TRISA2 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA2 GPIO Pin which has a custom name of RTTC_SCLK as Output
 * @param    none
 * @return   none  
 */
#define RTTC_SCLK_SetDigitalOutput() (_TRISA2 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA3 GPIO Pin which has a custom name of RTTC_IO to High
 * @pre      The RA3 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define RTTC_IO_SetHigh()          (_LATA3 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA3 GPIO Pin which has a custom name of RTTC_IO to Low
 * @pre      The RA3 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define RTTC_IO_SetLow()           (_LATA3 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RA3 GPIO Pin which has a custom name of RTTC_IO
 * @pre      The RA3 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define RTTC_IO_Toggle()           (_LATA3 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RA3 GPIO Pin which has a custom name of RTTC_IO
 * @param    none
 * @return   none  
 */
#define RTTC_IO_GetValue()         _RA3

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA3 GPIO Pin which has a custom name of RTTC_IO as Input
 * @param    none
 * @return   none  
 */
#define RTTC_IO_SetDigitalInput()  (_TRISA3 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA3 GPIO Pin which has a custom name of RTTC_IO as Output
 * @param    none
 * @return   none  
 */
#define RTTC_IO_SetDigitalOutput() (_TRISA3 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Initializes the PINS module
 * @param    none
 * @return   none  
 */
void PINS_Initialize(void);



#endif
