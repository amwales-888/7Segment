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

/* The DMA->SPI was inspired by the work done by Broadwell Consulting and 
 * the youtube video found at https://www.youtube.com/watch?v=_HJepzYc6_0
 * the w2812 code was released under an MIT licensed and inititally used as
 * a reference to debug the DMA->SPI code in this file.
 * 
 * The dsPIC33CK1024MP708 used here requires that a second DMA channel used
 * to read from the SPI, failing to do this causes the SPI to stall.
 * I am using a 300ns SPI period and 3 bits for each of bit on the WS2812.
 * 
 * The peripheral clock is running at 100Mhz and a BRG value of 16 is used to 
 * achive this.
 * 
 *  |SPI  |SPI  |SPI  |
 *  |Bit  |Bit  |Bit  |
 *  |300ns|300ns|300ns|
 * 
 *  +-----+
 *  |     |              WS2812 0 Bit
 *  |     +-----+-----+
 * 
 *  +-----+-----+
 *  |           |        WS2812 1 Bit
 *  |           +-----+
 *  
 * These value fall within the specifications of the WS2812 datasheet I am using 
 * found at https://github.com/amwales-888/7Segment/blob/main/Hardware/KiCad/Docs/ws2812B-C22461793.pdf
 * 
 *            Time in ns
 *            Min Typ Max
 *  0 High    200 300 400
 *  1 High    550 600 1200
 *  0 Low     550 600 1200
 *  1 Low     200 300 400
 * 
 *  Cycle     900 -   -
 * 
 * Our cycle time is 3x300 ns
 * and the other transitions we use are the typical spec value of 300 and 600
 * 
 * The bits are packed into a byte buffer, 5 WS2812 bits require 15 SPI Bits
 * and 2 packed Bytes in the DMA buffer.
 * 
 * As of Nov 2025 I believe that the Serial Wombat code could make significant 
 * RAM savings by changing it to use a 375ns period and using 3bit packing
 */

#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/timer/delay.h"

#include <stdint.h>
#include <stdbool.h>


#include "pack.h"
#include "ws2812.h"
#include "segment.h"
#include "ds1302.h"

/*
    Main application
*/



static uint8_t segmentValues[] = { 0, 0, 0, 0 };

int main(void)
{
    SYSTEM_Initialize();
    
    LED0_SetHigh();
       
    ws2812Initialize();
    
    
    struct dateTime_s dt[5];
    
    dt[0].day = 1;
    dt[0].hour = 13;
    dt[0].minute = 56;
    dt[0].month = 1;
    dt[0].second = 0;
    dt[0].year = 25;
    
    
    //DS1302_WriteTime(&dt[0]);

        DELAY_milliseconds(1000);
    
    
    
    while(1)
    {
        uint8_t hh, hl, mh, ml;
        
        ds1302ReadTime(&dt[1]);
        
        hh = dt[1].hour / 10;
        hl = dt[1].hour % 10;
        
        mh = dt[1].minute / 10;
        ml = dt[1].minute % 10;
            
        /* Populate ALL 4 7Segment displays 
         */            
        segmentValues[0] = hh;
        segmentValues[1] = hl;
        segmentValues[2] = mh;
        segmentValues[3] = ml;

        segmentsOut(segmentValues, 4, 0xff, 0, 0 );

        DELAY_milliseconds(1000);
    }
}