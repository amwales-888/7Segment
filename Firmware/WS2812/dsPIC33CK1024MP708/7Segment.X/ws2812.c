/*
 *  Copyright (c) 2025 Angelo Masci
 *
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 *  
 */

#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/timer/delay.h"

#include "pack.h"
#include "DMA2SPI.h"

#include <stdint.h>
#include <stdbool.h>


#define BITPATTERN(x) ((x) == 0 ? 0x00000004UL : 0x00000006UL)

void ws2812RGBOut(uint8_t R, uint8_t G, uint8_t B) {
        
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

bool ws2812Busy(void) {
        
    return DMA2SPIBusy();
}

void ws2812Update(void) {

    DMA2SPIStart(packDataGetBuffer(), packDataGetLen());    
}

void ws2812Initialize(void) {
    
    DMA2SPIInitialize();

}
    
void ws2812Start(uint8_t *dataBuf, size_t dataSize) {  

    packDataStart(dataBuf, dataSize);    
}  

void ws2812End(void) {

    packDataEnd();
}  
