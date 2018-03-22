/* 
 * Author: ckungler
 *
 * Created on July 22, 2016, 2:27 PM
 */

#include <xc.h>
#include "i2c.h"
#include "hardware.h"

//FIXME add timouts

I2CObject I2C;

I2CResult i2cRead(uint8_t id, uint8_t address, uint8_t* data, size_t len);
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

    int gieBack = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;

    SSP1DATPPSbits.SSP1DATPPS = SDA_PIN;
    SSP1CLKPPSbits.SSP1CLKPPS = SCL_PIN;
    
    SDA_PPS = 0b11000; //Rxy source is SCK/SCL
    SCL_PPS = 0b11001; //Rxy source is SDO/SDA

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS

    GIE = gieBack;

    SSP1STAT = 0;
    SSP1CON1 = 0;
    SSP1CON2 = 0;
    SSP1CON3 = 0;

    PIR1bits.SSP1IF = 0;

    SSP1CON1bits.SSPM = 0b1000; // Master mode
    SSP1ADD = 3; //SCL = Fsoc/(4*(ADD+1)) 0 1 2 not supported need <400kHz for max
    SSP1CON1bits.SSPEN = 1;
}

I2CResult i2cRead(uint8_t id, uint8_t address, uint8_t* data, size_t len) {
    i2cStart();
    i2cWriteByte((uint8_t) (id | 0b1));
    i2cWriteByte(address);
    i2cRestart();
    i2cWriteByte((uint8_t) (id | 0b1));
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
    int i = 0;
    SSP1CON2bits.SEN = 1;
    // Wait for end of start condition, can use int?
    while (SSP1CON2bits.SEN) {
        if (i++ > 100) {
            return I2C_ERROR;
        }
    }
    return I2C_OK;
}

I2CResult i2cStop(void) {
    int i = 0;
    SSP1CON2bits.PEN = 1;
    // Wait for end of stop condition, can use int?
    while (SSP1CON2bits.PEN) {
        if (i++ > 100) {
            return I2C_ERROR;
        }
    }
    return I2C_OK;
}

I2CResult i2cRestart(void) {
    int i = 0;
    SSP1CON2bits.RSEN = 1;
    while (SSP1CON2bits.RSEN) {
        if (i++ > 100) {
            return I2C_ERROR;
        }
    }
    return I2C_OK;
}

I2CResult i2cAck(void) {
    int i = 0;
    SSP1CON2bits.ACKDT = 0;
    SSP1CON2bits.ACKEN = 1;
    while (SSP1CON2bits.ACKEN) {
        if (i++ > 100) {
            return I2C_ERROR;
        }
    }
    return I2C_OK;
}

I2CResult i2cNAck(void) {
    int i = 0;
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
    while (SSP1CON2bits.ACKEN) {
        if (i++ > 100) {
            return I2C_ERROR;
        }
    }
    return I2C_OK;
}

I2CResult i2cReadByte(uint8_t * byte) {
    int i = 0;
    SSP1CON2bits.RCEN = 1;
    while (!SSP1STATbits.BF) {
        if (i++ > 100) {
            return I2C_ERROR;
        }
    }
    *byte = SSP1BUF;
    return I2C_OK;
}

I2CResult i2cWriteByte(uint8_t byte) {
    int i = 0;
    SSP1BUF = byte;
    while (SSP1STATbits.BF) {
        if (i++ > 100) {
            return I2C_ERROR;
        }
    }
    i = 0;
    while (SSP1CON2bits.ACKSTAT) {
        if (i++ > 100) {
            return I2C_ERROR;
        }
    }
    return I2C_OK;
}
