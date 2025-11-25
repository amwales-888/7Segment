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

#ifndef PACK_H
#define PACK_H

#include <stdint.h>
#include <stdlib.h>

/* User configuration - Edit the following to suit your needs
 */
#define BITPATTERNLEN  3       // How many bits will pattern require

/* System configuration - Leave the remaining code unchanged.
 */

#if (BITPATTERNLEN > 24)
#error "The maximum length of a bitpattern used by the pack functions is 24"
#endif

/* How many bytes are required to store 'count' bit patterns 
 * Ie. 
 *
 *   When BITPATTERNLEN=3 and count=10
 *   We require 4 bytes to store 5 packed bit patterns.
 */
#define PACKEDBITSIZE(count) (((size_t)(count) * BITPATTERNLEN + 7) / 8)

#ifdef	__cplusplus
extern "C" {
#endif

    
/* Function packDataStart() 
 * Arguments dataBuf  - Pointer to buffer that will hold the packed data
 *           dataSize - Size of the user buffer, this should be calculated using 
 *                      the PACKEDBITSIZE() macro to ensure the buffer is large
 *                      enough to hold the packed bits
 *
 * Call to initialise the pack data buffer
 */        
void packDataStart(uint8_t *dataBuf, size_t dataSize);

/* Function packDataBits() 
 * Arguments bitPattern - The bitPattern must be placed LSB justified 
 *                        bits BITPATTERNLEN:0 
 * 
 * Example: 
 * 
 *   MSB uint32_t
 *   bit 32      bit 24      bit 16        bit 8
 *   byte 4      Byte 3      Byte 2        Byte 3
 *   -           -           -             Pattern  
 *   0x00         0x00       0x00          0x01         
 *   0x00         0x00       0x00          0x02         
 *   0x00         0x00       0x00          0x03         
 *   0x00         0x00       0x00          0x04         
 *   0x00         0x00       0x00          0x05         
 *   0x00         0x00       0x00          0x06         
 *   0x00         0x00       0x00          0x07         
 * 
 * 
 *   #define MAXLEDS    28
 *   #define BITSPERLED 24
 * 
 *   uint8_t dataBuf[PACKEDBITSIZE(MAXLEDS*BITSPERLED)];
 *   size_t dataSize = PACKEDBITSIZE(MAXLEDS*BITSPERLED);
 * 
 *   packDataStart(dataBuf, dataSize);
 *   packDataBits(0x06);
 *   packDataBits(0x06);
 *   ...
 *   packDataBits(0x06);
 *   packDataBits(0x04);
 *   packDataEnd();
 * 
 *   uint8_t *ptr = packDataGetBuffer();
 *   size_t byteToSend = packDataGetLen();
 *  
 */        
void packDataBits(uint32_t bitPattern);

/* Function packDataEnd() 
 * Call to write any remaining bits still in the accumulator to the data buffer.
 */        
void packDataEnd(void);

/* Function packDataLen() 
 * Returns the number of bytes used in the data buffer.
 */        
size_t packDataGetLen(void);

/* Function packDataLen() 
 * Returns a pointer to the start of the data buffer.
 */        
uint8_t *packDataGetBuffer(void);

#ifdef	__cplusplus
}
#endif

#endif /* PACK_H */