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
#include "ws2812.h"
#include "segment.h"

#include <stdint.h>
#include <stdbool.h>

#define LEDSPERSEGMENT 7
#define NUMSEGMENTS    4
#define NUMLEDS        ((LEDSPERSEGMENT)*(NUMSEGMENTS))
#define BITSPERLED     24
#define BYTESREQUIRED  PACKEDBITSIZE((NUMLEDS)*(BITSPERLED))

uint8_t dataBuf[BYTESREQUIRED];
size_t dataSize = BYTESREQUIRED;

void segmentsOut(uint8_t *value, uint16_t count, 
        uint8_t R, uint8_t G, uint8_t B) {

    ws2812Start(dataBuf, dataSize);    
        
    for (uint16_t i=0; i<count; i++) {
        
        switch (value[i]) {
            case 0:
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(0x00, 0x00, 0x00);
                break;
            case 1:
                ws2812RGBOut(0x00, 0x00, 0x00);
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(0x00, 0x00, 0x00);
                ws2812RGBOut(0x00, 0x00, 0x00);
                ws2812RGBOut(0x00, 0x00, 0x00);
                ws2812RGBOut(0x00, 0x00, 0x00);
                break;
            case 2:
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(0x00, 0x00, 0x00);
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(0x00, 0x00, 0x00);
                ws2812RGBOut(R, G, B);   
                break;
            case 3:
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(0x00, 0x00, 0x00);
                ws2812RGBOut(0x00, 0x00, 0x00);
                ws2812RGBOut(R, G, B);   
                break;
            case 4:
                ws2812RGBOut(0x00, 0x00, 0x00);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(0x00, 0x00, 0x00);   
                ws2812RGBOut(0x00, 0x00, 0x00);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                break;
            case 5:
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(0x00, 0x00, 0x00);
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(0x00, 0x00, 0x00);
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                break;
            case 6:
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(0x00, 0x00, 0x00);
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                break;
            case 7:
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(0x00, 0x00, 0x00);
                ws2812RGBOut(0x00, 0x00, 0x00);
                ws2812RGBOut(0x00, 0x00, 0x00);
                ws2812RGBOut(0x00, 0x00, 0x00);
                break;
            case 8:            
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                break;
            case 9:            
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(0x00, 0x00, 0x00);   
                ws2812RGBOut(R, G, B);   
                ws2812RGBOut(R, G, B);   
                break;
            case SEGMENTVALUEOFF:            
                ws2812RGBOut(0x00, 0x00, 0x00);   
                ws2812RGBOut(0x00, 0x00, 0x00);   
                ws2812RGBOut(0x00, 0x00, 0x00);   
                ws2812RGBOut(0x00, 0x00, 0x00);   
                ws2812RGBOut(0x00, 0x00, 0x00);   
                ws2812RGBOut(0x00, 0x00, 0x00);   
                ws2812RGBOut(0x00, 0x00, 0x00);   
                break;
        }
    }

    ws2812End();
        
    ws2812Update();
}