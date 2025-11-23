#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pack.h"

#define MAXDATA PACKEDBITSIZE(MAXBITPATTERNS)

static uint8_t packData[MAXDATA];
static size_t packBytePos;
static uint8_t packBitPos;        // 0 to 7, where we are in current byte
static uint32_t packAccumulator;  // holds up to 24 bits safely

void packDataStart(void) {

    for (size_t i = 0; i < MAXDATA; i++) {
        packData[i] = 0;
    }

    packBytePos     = 0;  // position of the next byte
    packBitPos      = 0;  // 0 to 7, where we are in current byte
    packAccumulator = 0;  // holds up to 24 bits safely
}

void packDataBits(uint32_t bitPattern) {

    packAccumulator |= bitPattern >> packBitPos;
    packBitPos += BITPATTERNLEN;

    // If we have at least 8 bits, write a byte
    if (packBitPos >= 8) {
        packData[packBytePos] = (uint8_t)(packAccumulator >> 8);
        ++packBytePos;
        packAccumulator <<= 8;
        packBitPos -= 8;
    }
}

void packDataEnd(void) {

    // Write remaining bits if any
    if (packBitPos > 0) {
        packData[packBytePos] = (uint8_t)(packAccumulator >> 8);
        ++packBytePos;
    }
}

size_t packDataLen(void) {

    return packBytePos;
}

uint8_t *packDataBuffer(void) {
    return &packData[0];
}

