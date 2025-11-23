#ifndef PACK_H
#define PACK_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/* User configuration - Edit the following to suit your needs
 */
#define BITPATTERNLEN  3       // How many bits will pattern require
#define MAXBITPATTERNS 24*7    // How many bit patterns do we want to store? 

/* System configuration - Leave the remaining code unchanged.
 */

#if (BITPATTERNLEN > 8)
#error "The maximum length of a bitpattern used by the pack functions is 8"
#endif

/* How many bytes are required to store 'count' bit patterns 
 * Ie. 
 *
 *   WHen BITPATTERNLEN=3
 *   We require 3 bytes to store 5 packed bit patterns.
 */
#define PACKEDBITSIZE(count) ((((count) * BITPATTERNLEN) + 7) / 8)

#ifdef	__cplusplus
extern "C" {
#endif

    
/* Function packDataStart() 
 * Call to initialise the pack data buffer
 */        
void packDataStart(void);

/* Function packDataBits() 
 * Arguments bitPattern - The bitPattern must be placed in 
 *                        bits 7:(8-BITPATTERNLEN) of Byte 2
 * 
 * Example: 
 * 
 *   MSB uint32_t
 *   byte 4      Byte 3      Byte 2        Byte 3
 *   -           -           PATTERN       - 
 *   0x00         0x00       0xC0          0x00         
 * 
 * 0x00008000UL : 0x0000C000UL
 * 
 * 
 * Will add binary pattern 110 to the end of the data buffer
 */        
void packDataBits(uint32_t bitPattern);

/* Function packDataEnd() 
 * Call to write a remaining bits still in the accumulator to the data buffer.
 */        
void packDataEnd(void);

/* Function packDataLen() 
 * Returns the number of bytes used in the data buffer.
 */        
size_t packDataLen(void);

/* Function packDataLen() 
 * Returns a pointer to the start of the data buffer.
 */        
uint8_t *packDataBuffer(void);

#ifdef	__cplusplus
}
#endif

#endif /* PACK_H */