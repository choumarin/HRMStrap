/* 
 * Author: ckungler
 *
 * Created on July 22, 2016, 2:27 PM
 */

#include "i2c.h"

I2CObject I2C;

I2CResult i2cRead(uint8_t address);
I2CResult i2cWrite(uint8_t address, uint8_t* data, size_t len);

void I2CInit(void) {
    I2C.read = i2cRead;
    I2C.write = i2cWrite;
    
    

}

I2CResult i2cRead(uint8_t address) {
    return I2C_ERROR;
}

I2CResult i2cWrite(uint8_t address, uint8_t* data, size_t len) {
    return I2C_ERROR;
}
