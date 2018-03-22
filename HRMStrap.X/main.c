/* 
 * Author: ckungler
 *
 * Created on July 22, 2016, 2:20 PM
 */

#include <xc.h>
#include "init.h"
#include "hardware.h"
#include "i2c.h"

uint8_t buffer[10];

void main(void) {
    init();
    while (1) {
        __delay_ms(10000);
        I2C.read(0xAE, 0x00, buffer, 1);
    }



}
