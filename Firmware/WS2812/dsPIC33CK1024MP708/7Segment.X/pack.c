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

#include <stdint.h>
#include <stdlib.h>

#include "pack.h"

static uint8_t *data;         // user data buffer
static size_t bytePos;        // where the next byte will be put
static uint8_t bitPos;        // 0 to 7, where we are in current byte
static uint32_t accumulator;  // used to hold bits that are being processed


void packDataStart(uint8_t *dataBuf, size_t dataSize) {
    
    data        = dataBuf;    // User data buffer
    accumulator = 0;          // holds partial data
    bytePos     = 0;          // Index of next byte to be written
    bitPos      = 0;          // bits used in current byte (0-7)
        
    for (size_t i = 0; i < dataSize; i++) {
        data[i] = 0;
    }
}

void packDataBits(uint32_t bitPattern) {

    // Shift the new bits into the accumulator at the correct position

    accumulator |=  (uint32_t)bitPattern << ((32-BITPATTERNLEN)-bitPos);
    bitPos += BITPATTERNLEN;

    // While we have complete bytes, extract them

    while (bitPos >= 8) {
        
        data[bytePos] = (uint8_t)(accumulator >> 24);
        ++bytePos;
        
        accumulator <<= 8;
        bitPos -= 8;
    }
}

 




void packDataEnd(void) {
    
    // Flush any remaining bits 

    if (bitPos > 0) {
        
        data[bytePos] = (uint8_t)(accumulator >> 24);
        ++bytePos;
    }
}

size_t packDataGetLen(void) {

    return bytePos;
}

uint8_t *packDataGetBuffer(void) {

    return &data[0];
}

