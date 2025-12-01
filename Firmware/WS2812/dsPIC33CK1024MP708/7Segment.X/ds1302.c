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
 * This file was ported from https://github.com/julgonmej/ds1302 and ported
 * to dsPIC from STM32
 * 
 */

#include "mcc_generated_files/timer/delay.h"
#include "mcc_generated_files/system/pins.h"

#include <stdint.h>
#include <stdbool.h>

#include "ds1302.h"

// Write Register Address
#define DS1302_SEC			0x80
#define DS1302_MIN			0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_DAY			0x8a
#define DS1302_YEAR			0x8c
#define DS1302_CONTROL		0x8e
#define DS1302_CHARGER		0x90 					 
#define DS1302_CLKBURST		0xbe
#define DS1302_RAMBURST 	0xfe

#define RAMSIZE 			0x31	// Ram Size in bytes
#define DS1302_RAMSTART		0xc0 	// First Address

#define HEX2BCD(v)	((v) % 10 + (v) / 10 * 16)
#define BCD2HEX(v)	((v) % 16 + (v) / 16 * 10)

// SDA Write(output) Mode
static void setIODirectionWrite(void) {
	
    RTTC_IO_SetDigitalOutput();
}

// SDA Read(input) Mode
static void setIODirectionRead(void) {

    RTTC_IO_SetDigitalInput();
}

/* Sends an address or command */
static void sendCmd(uint8_t cmd) {

	for (uint8_t i = 0; i < 8; i ++) {	

        if (cmd & 1) {
           RTTC_IO_SetHigh(); 
        } else {
           RTTC_IO_SetLow();             
        }
        
        RTTC_SCLK_SetHigh();
        DELAY_microseconds(1);
        
        RTTC_SCLK_SetLow();
        DELAY_microseconds(1);
        
		cmd >>= 1;
	}
}

/* Writes a byte to 'addr' */
static void writeByte(uint8_t addr, uint8_t d) {

    RTTC_CE_SetHigh();
        
	sendCmd(addr);	// Sends address
	
	for (uint8_t i = 0; i < 8; i ++) {

        if (d & 0x01) {
           RTTC_IO_SetHigh(); 
        } else {
           RTTC_IO_SetLow();             
        }
        
        RTTC_SCLK_SetHigh();
        DELAY_microseconds(1);
        
        RTTC_SCLK_SetLow();
        DELAY_microseconds(1);

		d >>= 1;
	}
	
    RTTC_CE_SetLow();
 
    RTTC_IO_SetLow();             
}

/* Reads a byte from addr */
static uint8_t readByte(uint8_t addr) {

	uint8_t value = 0;

    RTTC_CE_SetHigh();

	addr = addr | 0x01; // Generate Read Address

	sendCmd(addr);	// Sends address
	
	setIODirectionRead();
    
	for (uint8_t i = 0; i < 8; i ++) 
	{
		value >>= 1;
        
        if (RTTC_IO_GetValue()) {
            value |= 0x80;
        }
        
        RTTC_SCLK_SetHigh();
        DELAY_microseconds(1);
        
        RTTC_SCLK_SetLow();
        DELAY_microseconds(1);        
	}

	setIODirectionWrite();

    RTTC_CE_SetLow();
 
    RTTC_IO_SetLow();             

	return value;
}

/* Writes time byte by byte from 'buf' */
void ds1302WriteTime(struct dateTime_s *dt) 
{	
	writeByte(DS1302_CONTROL,0x00);			// Disable write protection

    DELAY_microseconds(1);

	writeByte(DS1302_SEC,0x80);
	writeByte(DS1302_YEAR,HEX2BCD(dt->year));
	writeByte(DS1302_MONTH,HEX2BCD(dt->month));
	writeByte(DS1302_DATE,HEX2BCD(dt->day));
	writeByte(DS1302_HOUR,HEX2BCD(dt->hour));
	writeByte(DS1302_MIN,HEX2BCD(dt->minute));
	writeByte(DS1302_SEC,HEX2BCD(dt->second));
	writeByte(DS1302_DAY,HEX2BCD(dt->day));
	writeByte(DS1302_CONTROL,0x80);			// Enable write protection

    DELAY_microseconds(1);
}

/* Reads time byte by byte to 'buf' */
void ds1302ReadTime(struct dateTime_s *dt)  
{ 
	dt->year = BCD2HEX(readByte(DS1302_YEAR));		 
	dt->month = BCD2HEX(readByte(DS1302_MONTH));	 
	dt->day = BCD2HEX(readByte(DS1302_DATE));
	dt->hour = BCD2HEX(readByte(DS1302_HOUR));
	dt->minute = BCD2HEX(readByte(DS1302_MIN)); 
	dt->second = BCD2HEX(readByte((DS1302_SEC))&0x7F);
	dt->day = BCD2HEX(readByte(DS1302_DAY));
}

/* Initialization */
void ds1302Initialize(void)
{
    RTTC_CE_SetDigitalOutput();
    RTTC_CE_SetLow();

    RTTC_IO_SetDigitalOutput();
    RTTC_IO_SetLow();

    RTTC_SCLK_SetDigitalOutput();
    RTTC_SCLK_SetLow();
}

/* Writes 'val' to ram address 'addr' */
/* Ram addresses range from 0 to 30 */
void ds1302WriteRam(uint8_t addr, uint8_t val) {

	if (addr >= RAMSIZE) {
		return;
	}
	
	writeByte(DS1302_CONTROL,0x00);			// Disable write protection
    DELAY_microseconds(1);

	writeByte(DS1302_RAMSTART + (2 * addr), val);	
	
	writeByte(DS1302_CONTROL,0x80);			// Enable write protection
    DELAY_microseconds(1);
}

/* Reads ram address 'addr' */
uint8_t ds1302ReadRam(uint8_t addr) {

	if (addr >= RAMSIZE) {
		return 0;
	}
	
	return readByte(DS1302_RAMSTART + (2 * addr));	
}

/* Clears the entire ram writing 0 */
void ds1302ClearRam(void) {

	uint8_t i;
	for(i=0; i< RAMSIZE; i++){
		ds1302WriteRam(i,0x00);
	}
}
