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

#ifndef DS1302_H
#define	DS1302_H

struct dateTime_s {
        
    uint8_t year;   // Starting at 2000
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;    
};


#ifdef	__cplusplus
extern "C" {
#endif

void ds1302Initialize(void);
void ds1302WriteTime(struct dateTime_s *dt);
void ds1302ReadTime(struct dateTime_s *dt);
void ds1302WriteRam(uint8_t addr, uint8_t val);
uint8_t ds1302ReadRam(uint8_t addr);
void ds1302ClearRam(void);

#ifdef	__cplusplus
}
#endif

#endif	/* DS1302_H */
