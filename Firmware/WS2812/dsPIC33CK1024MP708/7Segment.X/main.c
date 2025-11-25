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
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/system/pins.h"
#include "pack.h"
#include "mcc_generated_files/timer/delay.h"

#include <stdint.h>
#include <stdbool.h>

/*
    Main application
*/


void SPI1_Initialize (void)
{
    
    // Configure Peripheral Pin Select for SPI
        
    __builtin_write_RPCON(0x0000); // unlock PPS

    RPOR1bits.RP34R = 0x0005U;  //RB2->SPI1:SDO1;

     __builtin_write_RPCON(0x0800); // lock PPS    
    
    
    // Disable SPI1 so it can be configured
    SPI1CON1Lbits.SPIEN = 0x0U;    

    // SPIEN disabled; DISSDO disabled; MCLKEN FOSC/2; CKP Idle:Low, Active:High; SSEN disabled; MSTEN Host; MODE16 disabled; SMP Middle; DISSCK disabled; SPIFE Frame Sync pulse precedes; CKE Idle to Active; MODE32 disabled; SPISIDL disabled; ENHBUF enabled; DISSDI disabled; 
    SPI1CON1L = 0x21U;
    
    // AUDEN disabled; FRMEN disabled; AUDMOD I2S; FRMSYPW One clock wide; AUDMONO stereo; FRMCNT 0x0; MSSEN disabled; FRMPOL disabled; IGNROV disabled; SPISGNEXT not sign-extended; FRMSYNC disabled; URDTEN disabled; IGNTUR disabled; 
    SPI1CON1H = 0x0U;
    SPI1CON1Hbits.IGNROV = 0;

    // WLENGTH disabled; 
    SPI1CON2L = 0x0U;

    // SPIROV disabled; FRMERR disabled; 
    SPI1STATL = 0x0U;
    SPI1STATH = 0x0U;

    // Baud Rate Generator SPIBRGL divisor 1; 
    // Baud Rate = FP / ( 2 * (SPIxBRG + 1))
    SPI1BRGL = 0x10U; // 340ns period
            
    // FRMERREN disabled; BUSYEN disabled; SPITUREN disabled; SRMTEN disabled; SPIROVEN disabled; SPIRBEN disabled; SPITBEN enabled; SPITBFEN disabled; SPIRBFEN enabled
    // SPITBEN enables Interrupt Events via SPITBE bit, SPIx transmit buffer empty generates an interrupt event
    // SPIRBFEN enables Interrupt Events via SPIRBF bit, SPIx receive buffer full generates an interrupt event    
    SPI1IMSKL = 0x9U;

    // RXWIEN disabled; RXMSK disabled; TXWIEN disabled; TXMSK disabled
    SPI1IMSKH = 0x0U;
           
    // SPIURDTL 0; 
    SPI1URDTL = 0x0U;
    // SPIURDTH 0; 
    SPI1URDTH = 0x0U;

    // Enable SPI1 so changes take affect
    SPI1CON1Lbits.SPIEN = 1U;    
}

#define BITPATTERN(x) ((x) == 0 ? 0x00000004UL : 0x00000006UL)

void packRGB(uint8_t R, uint8_t G, uint8_t B) {
        
    packDataBits(BITPATTERN(G & 0x01));
    packDataBits(BITPATTERN(G & 0x02));
    packDataBits(BITPATTERN(G & 0x04));
    packDataBits(BITPATTERN(G & 0x08));
    packDataBits(BITPATTERN(G & 0x10));
    packDataBits(BITPATTERN(G & 0x20));
    packDataBits(BITPATTERN(G & 0x40));
    packDataBits(BITPATTERN(G & 0x80));

    packDataBits(BITPATTERN(R & 0x01));
    packDataBits(BITPATTERN(R & 0x02));
    packDataBits(BITPATTERN(R & 0x04));
    packDataBits(BITPATTERN(R & 0x08));
    packDataBits(BITPATTERN(R & 0x10));
    packDataBits(BITPATTERN(R & 0x20));
    packDataBits(BITPATTERN(R & 0x40));
    packDataBits(BITPATTERN(R & 0x80));

    packDataBits(BITPATTERN(B & 0x01));
    packDataBits(BITPATTERN(B & 0x02));
    packDataBits(BITPATTERN(B & 0x04));
    packDataBits(BITPATTERN(B & 0x08));
    packDataBits(BITPATTERN(B & 0x10));
    packDataBits(BITPATTERN(B & 0x20));
    packDataBits(BITPATTERN(B & 0x40));
    packDataBits(BITPATTERN(B & 0x80));    
}

bool queueBusy(void) {
        
    return (DMACH0bits.CHEN != 0);
}

bool queueSendBits(void) {

    static uint8_t dummy;         // Put the reasult of the SPI read here
    size_t count = packDataGetLen(); // Get number of bytes in the packed buffer
        
    // Start the DMA Transfer

    /* Channel 1 reads from the SPI when there is data available to be read 
     * NOTE - Failing to do so will cause DMA to stall waiting for SPI read 
     * buffer to be emptied.
     */
    
    DMACH1bits.CHEN = 0; // Disable the channel so we can configure it
            
    DMACH1bits.SIZE    = 1; // 8bit mode
    DMACH1bits.RELOAD  = 1; // Reload
    DMACH1bits.TRMODE  = 3; // Continuous
    DMACH1bits.SAMODE  = 0; // Peripheral    
    DMACH1bits.DAMODE  = 0; // Destination Address remains unchanged
    DMAINT1bits.CHSEL  = 2; // SPI1 RX
    DMAINT1bits.DONEIF = 0; // Clear the interrupt completion flag
            
    /* Setup source, destination and count 
     */    
    DMASRC1 = (uint16_t)&SPI1BUFL;
    DMADST1 = (uint16_t)&dummy;
    DMACNT1 = 1;
    
    DMACH1bits.CHEN  = 1; // Enable the channel
    DMACH1bits.CHREQ = 1; // Force start

    /* Channel 0 writes to the SPI when there is space available to write
     */
    
    DMACH0bits.CHEN = 0; // Disable the channel so we can configure it
            
    DMACH0bits.SIZE    = 1; // 8bit mode
    DMACH0bits.TRMODE  = 0; // One-shot
    DMACH0bits.RELOAD  = 0; // Do not reload
    DMACH0bits.SAMODE  = 1; // Destination Address Post-increment
    DMACH0bits.DAMODE  = 0; // Peripheral                
    DMAINT0bits.CHSEL  = 3; // SPI1 TX
    DMAINT0bits.DONEIF = 0; // Clear the interrupt completion flag
    
    /* Setup source, destination and count 
     */    
    DMASRC0 = (uint16_t)packDataGetBuffer();
    DMADST0 = (uint16_t)&SPI1BUFL;
    DMACNT0 = count;

    DMACH0bits.CHEN  = 1; // Enable the channel
    DMACH0bits.CHREQ = 1; // Force start

    return true;
}


void DMA_Initialize(void) {

    DMACONbits.DMAEN=1;  // Enable DMA
    DMACONbits.PRSSEL=1; // 1 => Round robin scheme
    DMAL=0x1000;         // Lower DMA Bounds
    DMAH=0xFFFF;         // Upper DMA Bounds
}


#define LEDSPERSEGMENT 7
#define NUMSEGMENTS    4
#define NUMLEDS        ((LEDSPERSEGMENT)*(NUMSEGMENTS))
#define BITSPERLED     24
#define BYTESREQUIRED  PACKEDBITSIZE((NUMLEDS)*(BITSPERLED))

uint8_t dataBuf[BYTESREQUIRED];
size_t dataSize = BYTESREQUIRED;


void SegmentsOut(uint8_t *value, uint16_t count, 
        uint8_t R, uint8_t G, uint8_t B) {

    packDataStart(&dataBuf[0], dataSize);    
        
    for (uint16_t i=0; i<count; i++) {
        
        switch (value[i]) {
            case 0:
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(0x00, 0x00, 0x00);
                break;
            case 1:
                packRGB(0x00, 0x00, 0x00);
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(0x00, 0x00, 0x00);
                packRGB(0x00, 0x00, 0x00);
                packRGB(0x00, 0x00, 0x00);
                packRGB(0x00, 0x00, 0x00);
                break;
            case 2:
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(0x00, 0x00, 0x00);
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(0x00, 0x00, 0x00);
                packRGB(R, G, B);   
                break;
            case 3:
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(0x00, 0x00, 0x00);
                packRGB(0x00, 0x00, 0x00);
                packRGB(R, G, B);   
                break;
            case 4:
                packRGB(0x00, 0x00, 0x00);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(0x00, 0x00, 0x00);   
                packRGB(0x00, 0x00, 0x00);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                break;
            case 5:
                packRGB(R, G, B);   
                packRGB(0x00, 0x00, 0x00);
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(0x00, 0x00, 0x00);
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                break;
            case 6:
                packRGB(R, G, B);   
                packRGB(0x00, 0x00, 0x00);
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                break;
            case 7:
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(0x00, 0x00, 0x00);
                packRGB(0x00, 0x00, 0x00);
                packRGB(0x00, 0x00, 0x00);
                packRGB(0x00, 0x00, 0x00);
                break;
            case 8:            
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                break;
            case 9:            
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                packRGB(0x00, 0x00, 0x00);   
                packRGB(R, G, B);   
                packRGB(R, G, B);   
                break;
        }
    }

    packDataEnd();
        
    queueSendBits();
}


static uint8_t segmentValues[] = { 0, 0, 0, 0 };

int main(void)
{
    SYSTEM_Initialize();
    
    LED0_SetHigh();
    
    SPI1_Initialize();    
    DMA_Initialize();

    
    while(1)
    {
        for (uint16_t i=0; i<10; i++) {
        
            /* Populate ALL 4 7Segment displays 
             */            
            segmentValues[0] = i;
            segmentValues[1] = i;
            segmentValues[2] = i;
            segmentValues[3] = i;

            SegmentsOut(segmentValues, 4, 0xff, 0, 0 );
            
            DELAY_milliseconds(1000);
        }        
    }
}