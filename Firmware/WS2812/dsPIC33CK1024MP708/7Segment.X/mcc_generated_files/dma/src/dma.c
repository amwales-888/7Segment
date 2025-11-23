/**
 * DMA Generated Driver Source File
 * 
 * @file      dma.c
 * 
 * @ingroup   dmadriver
 * 
 * @brief     This is the generated driver source file for DMA driver
 *
 * @skipline @version   Driver Version 1.1.1
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

// Section: Included Files
#include <xc.h>
#include "../dma.h"

// Section: Driver Interface Function Definitions

void DMA_Initialize (void)
{ 
    // DMAEN disabled; PRSSEL Fixed priority; 
    DMACON = (uint16_t)(((uint16_t)0x0 | (uint16_t)0x01U) & (uint16_t)0x7FFFU); //The module is disabled, till other settings are configured.
    // LADDR 0; 
    DMAL= 0x0U;
    // HADDR 0; 
    DMAH= 0x0U;

    // CHEN0 disabled; DAMODE0 Unchanged; TRMODE0 One-Shot; CHREQ0 disabled; RELOAD0 disabled; SIZE0 16 bit; NULLW0 disabled; SAMODE0 Unchanged; 
    DMACH0 = (uint16_t)((uint16_t)0x0 & (uint16_t)0xFFFEU); //The channel is disabled, till other settings are configured.
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; CHSEL0 ; HIGHIF disabled; 
    DMAINT0= 0x0U;
    // SADDR0 0; 
    DMASRC0= 0x0U;
    // DADDR0 0; 
    DMADST0= 0x0U;
    // CNT0 0; 
    DMACNT0= 0x0U;
    // Clearing Channel 0 Interrupt Flag;
    IFS0bits.DMA0IF = 0U;

    // CHEN1 disabled; SAMODE1 Unchanged; SIZE1 16 bit; DAMODE1 Unchanged; CHREQ1 disabled; RELOAD1 disabled; TRMODE1 One-Shot; NULLW1 disabled; 
    DMACH1 = (uint16_t)((uint16_t)0x0 & (uint16_t)0xFFFEU); //The channel is disabled, till other settings are configured.
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; CHSEL1 ; 
    DMAINT1= 0x0U;
    // SADDR1 0; 
    DMASRC1= 0x0U;
    // DADDR1 0; 
    DMADST1= 0x0U;
    // CNT1 0; 
    DMACNT1= 0x0U;
    // Clearing Channel 1 Interrupt Flag;
    IFS0bits.DMA1IF = 0U;

    // SAMODE2 Unchanged; CHEN2 disabled; SIZE2 16 bit; DAMODE2 Unchanged; CHREQ2 disabled; RELOAD2 disabled; NULLW2 disabled; TRMODE2 One-Shot; 
    DMACH2 = (uint16_t)((uint16_t)0x0 & (uint16_t)0xFFFEU); //The channel is disabled, till other settings are configured.
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; CHSEL2 ; 
    DMAINT2= 0x0U;
    // SADDR2 0; 
    DMASRC2= 0x0U;
    // DADDR2 0; 
    DMADST2= 0x0U;
    // CNT2 0; 
    DMACNT2= 0x0U;
    // Clearing Channel 2 Interrupt Flag;
    IFS1bits.DMA2IF = 0U;

    // SAMODE3 Unchanged; CHEN3 disabled; SIZE3 16 bit; DAMODE3 Unchanged; TRMODE3 One-Shot; NULLW3 disabled; CHREQ3 disabled; RELOAD3 disabled; 
    DMACH3 = (uint16_t)((uint16_t)0x0 & (uint16_t)0xFFFEU); //The channel is disabled, till other settings are configured.
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; CHSEL3 ; HIGHIF disabled; 
    DMAINT3= 0x0U;
    // SADDR3 0; 
    DMASRC3= 0x0U;
    // DADDR3 0; 
    DMADST3= 0x0U;
    // CNT3 0; 
    DMACNT3= 0x0U;
    // Clearing Channel 3 Interrupt Flag;
    IFS1bits.DMA3IF = 0U;

    // CHEN4 disabled; DAMODE4 Unchanged; TRMODE4 One-Shot; CHREQ4 disabled; RELOAD4 disabled; SIZE4 16 bit; NULLW4 disabled; SAMODE4 Unchanged; 
    DMACH4 = (uint16_t)((uint16_t)0x0 & (uint16_t)0xFFFEU); //The channel is disabled, till other settings are configured.
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; CHSEL4 ; 
    DMAINT4= 0x0U;
    // SADDR4 0; 
    DMASRC4= 0x0U;
    // DADDR4 0; 
    DMADST4= 0x0U;
    // CNT4 0; 
    DMACNT4= 0x0U;
    // Clearing Channel 4 Interrupt Flag;
    IFS1bits.DMA4IF = 0U;

    // SIZE5 16 bit; DAMODE5 Unchanged; CHEN5 disabled; SAMODE5 Unchanged; CHREQ5 disabled; RELOAD5 disabled; TRMODE5 One-Shot; NULLW5 disabled; 
    DMACH5 = (uint16_t)((uint16_t)0x0 & (uint16_t)0xFFFEU); //The channel is disabled, till other settings are configured.
    // CHSEL5 ; HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; 
    DMAINT5= 0x0U;
    // SADDR5 0; 
    DMASRC5= 0x0U;
    // DADDR5 0; 
    DMADST5= 0x0U;
    // CNT5 0; 
    DMACNT5= 0x0U;
    // Clearing Channel 5 Interrupt Flag;
    IFS2bits.DMA5IF = 0U;

    // CHEN6 disabled; DAMODE6 Unchanged; TRMODE6 One-Shot; CHREQ6 disabled; RELOAD6 disabled; SIZE6 16 bit; NULLW6 disabled; SAMODE6 Unchanged; 
    DMACH6 = (uint16_t)((uint16_t)0x0 & (uint16_t)0xFFFEU); //The channel is disabled, till other settings are configured.
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; CHSEL6 ; HIGHIF disabled; 
    DMAINT6= 0x0U;
    // SADDR6 0; 
    DMASRC6= 0x0U;
    // DADDR6 0; 
    DMADST6= 0x0U;
    // CNT6 0; 
    DMACNT6= 0x0U;
    // Clearing Channel 6 Interrupt Flag;
    IFS9bits.DMA6IF = 0U;

    // CHEN7 disabled; DAMODE7 Unchanged; TRMODE7 One-Shot; CHREQ7 disabled; RELOAD7 disabled; SIZE7 16 bit; NULLW7 disabled; SAMODE7 Unchanged; 
    DMACH7 = (uint16_t)((uint16_t)0x0 & (uint16_t)0xFFFEU); //The channel is disabled, till other settings are configured.
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; CHSEL7 ; HIGHIF disabled; 
    DMAINT7= 0x0U;
    // SADDR7 0; 
    DMASRC7= 0x0U;
    // DADDR7 0; 
    DMADST7= 0x0U;
    // CNT7 0; 
    DMACNT7= 0x0U;
    // Clearing Channel 7 Interrupt Flag;
    IFS9bits.DMA7IF = 0U;
    
    //Enable DMA
    DMACONbits.DMAEN = 1U; 
    
}


