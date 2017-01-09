/* 
 * Author: ckungler
 *
 * Created on July 22, 2016, 2:27 PM
 */

#include <xc.h>
#include "i2c.h"

//FIXME add timouts

I2CObject I2C;

I2CResult i2cRead(uint8_t id, uint8_t address, uint8_t* data, size_t* len);
I2CResult i2cWrite(uint8_t id, uint8_t address, uint8_t* data, size_t len);
I2CResult i2cWriteByte(uint8_t byte);
I2CResult i2cReadByte(uint8_t* byte);
I2CResult i2cNAck(void);
I2CResult i2cAck(void);
I2CResult i2cRestart(void);
I2CResult i2cStop(void);
I2CResult i2cStart(void);

void I2CInit(void) {
    I2C.read = i2cRead;
    I2C.write = i2cWrite;

    // TODO Configure pins TRIS?

    SSP1CON1bits.SSPM = 0b1000; // Master mode
    SSP1ADD = 3; //SCL = Fsoc/(4*(ADD+1)) 0 1 2 not supported need <400kHz for max
    SSP1CON1bits.SSPEN = 1;
}

I2CResult i2cRead(uint8_t id, uint8_t address, uint8_t* data, size_t len) {
    i2cStart();
    i2cWriteByte(id | 0b1);
    i2cWriteByte(address);
    i2cRestart();
    i2cWriteByte(id | 0b1);
    i2cReadByte(data++);
    while (--len) {
        i2cAck();
        i2cReadByte(data++);
    }
    i2cNAck();
    i2cStop();
    return I2C_OK;
}

I2CResult i2cWrite(uint8_t id, uint8_t address, uint8_t* data, size_t len) {
    i2cStart();
    i2cWriteByte(id);
    i2cWriteByte(address);
    while (len--) {
        i2cWriteByte(*(data++));
    }
    i2cStop();
    return I2C_OK;
}

I2CResult i2cStart(void) {
    SSP1CON2bits.SEN = 1;
    // Wait for end of start condition, can use int?
    while (SSP1CON2bits.SEN);
    return I2C_OK;
}

I2CResult i2cStop(void) {
    SSP1CON2bits.PEN = 1;
    // Wait for end of stop condition, can use int?
    while (SSP1CON2bits.PEN);
    return I2C_OK;
}

I2CResult i2cRestart(void) {
    SSP1CON2bits.RSEN = 1;
    while (SSP1CON2bits.RSEN);
    return I2C_OK;
}

I2CResult i2cAck(void) {
    SSP1CON2bits.ACKDT = 0;
    SSP1CON2bits.ACKEN = 1;
    while (SSP1CON2bits.ACKEN);
    return I2C_OK;
}

I2CResult i2cNAck(void) {
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
    while (SSP1CON2bits.ACKEN);
    return I2C_OK;
}

I2CResult i2cReadByte(uint8_t * byte) {
    SSP1CON2bits.RCEN = 1;
    while (!SSP1STATbits.BF);
    *byte = SSP1BUF;
    return I2C_OK;
}

I2CResult i2cWriteByte(uint8_t byte) {
    SSP1BUF = byte;
    while (SSP1STATbits.BF);
    while (SSP1CON2bits.ACKSTAT);
    return I2C_OK;
}
