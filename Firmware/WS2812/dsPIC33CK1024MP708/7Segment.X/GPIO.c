/* 
 *  Copyright (c) 2023 Angelo Masci
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

#include <xc.h>
#include <stdint.h>

#include "mcc_generated_files/system/pins.h"
#include "GPIO.h"

void
GPIOEnablePullDown(uint16_t id) {

    switch (id) {
        case 0:
            CNPDB |= (1 << 5); // Enable Pull-down B5
            return;
        case 1:
            CNPDB |= (1 << 3); // Enable Pull-down B3
            return;
        case 2:
            CNPDB |= (1 << 4); // Enable Pull-down B4
            return;
    }
}

void
GPIOEnablePullUp(uint16_t id) {

    switch (id) {
        case 0:
            CNPUB |= (1 << 5); // Enable Pull-up B5
            return;
        case 1:
            CNPUB |= (1 << 3); // Enable Pull-up B3
            return;
        case 2:
            CNPUB |= (1 << 4); // Enable Pull-up B4
            return;
    }
}

void
GPIODisablePullDown(uint16_t id) {
    
    switch (id) {
        case 0:
            CNPDB &= ~(1 << 5); // Disable Pull-down B5
            return;
        case 1:
            CNPDB &= ~(1 << 3); // Disable Pull-down B3
            return;
        case 2:
            CNPDB &= ~(1 << 4); // Disable Pull-down B4
            return;
    }
}

void
GPIODisablePullUp(uint16_t id) {
    
    switch (id) {
        case 0:
            CNPUB &= ~(1 << 5); // Disable Pull-up B5
            return;
        case 1:
            CNPUB &= ~(1 << 3); // Disable Pull-up B3
            return;
        case 2:
            CNPUB &= ~(1 << 4); // Disable Pull-up B4
            return;
    }
}

uint8_t
GPIOGetValue(uint16_t id) {

    switch (id) {
        case 0:
            return GPIO0_GetValue();
        case 1:
            return GPIO1_GetValue();
        case 2:
            return GPIO2_GetValue();
    }

    return 0;
}

void
GPIOSetValue(uint16_t id, uint8_t value) {

    if (value) {
        switch (id) {
            case 0:
                GPIO0_SetHigh();
                return;
            case 1:
                GPIO1_SetHigh();
                return;
            case 2:
                GPIO2_SetHigh();
                return;
        } 
        
    } else {
        
        switch (id) {
            case 0:
                GPIO0_SetLow();
                return;
            case 1:
                GPIO1_SetLow();
                return;
            case 2:
                GPIO2_SetLow();
                return;
        }        
    }
}

void
GPIOToggleValue(uint16_t id) {

    switch (id) {
        case 0:
            GPIO0_Toggle();
            return;
        case 1:
            GPIO1_Toggle();
            return;
        case 2:
            GPIO2_Toggle();
            return;
    } 
        
}

void
GPIOSetDirection(uint16_t id, enum GPIODirection_e direction) {

    if (direction == GPIOOutput) {        
        
        switch (id) {
            case 0:
                GPIO0_SetDigitalOutput();
                return; 
            case 1:
                GPIO1_SetDigitalOutput();
                return; 
            case 2:
                GPIO2_SetDigitalOutput();
                return; 
        }
        
    } else {

        switch (id) {
            case 0:
                GPIO0_SetDigitalInput();
                return; 
            case 1:
                GPIO1_SetDigitalInput();
                return; 
            case 2:
                GPIO2_SetDigitalInput();
                return; 
        }        
    }
}

void
GPIOSetType(uint16_t id, enum GPIOType type) {
        
    switch (id) {
        case 0:
//            ANSELBbits.ANSELB5 = type;
            return;
        case 1:
            ANSELBbits.ANSELB3 = type;
            return;
        case 2:
            ANSELBbits.ANSELB4 = type;
            return;
    }            
}
