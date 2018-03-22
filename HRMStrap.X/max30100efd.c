/* 
 * Author: ckungler
 *
 * Created on July 22, 2016, 2:20 PM
 */

#include "max30100efd.h"
#include "i2c.h"
#include "hardware.h"

#define MAX_ID              0xAE
#define MAX_MODE            0x06
#define MAX_MODE_SHDN       0b10000000
#define MAX_MODE_RESET      0b01000000
#define MAX_MODE_TEMP_EN    0b00001000
#define MAX_MODE_HR_ONLY    0b00000010
#define MAX_MODE_SPO2       0b00000011

#define MAX_INT             0x00
#define MAX_INT_PWR_RDY     0b00000001
#define MAX_INT_SPO2_RDY    0b00010000
#define MAX_INT_HR_RDY      0b00100000
#define MAX_INT_TEMP_RDY    0b01000000
#define MAX_INT_A_FULL      0b10000000

#define MAX_FIFO_WR_PTR     0x02
#define MAX_FIFO_OVF_CNT    0x03
#define MAX_FIFO_RD_PRT     0x04
#define MAX_FIFO_DATA       0x05

Max30100efdObject Max;

void maxISR(void);
void maxRequestHeartRate(void);

void Max30100efdInit(void) {

    HRM_EN_TRIS = 0;
    HRM_EN = 1;

    Max.ISR = maxISR;
    Max.requestHeartRate = maxRequestHeartRate;
    I2CInit();
}

void maxISR(void) {
    uint8_t data[1];
    // read int
    I2C.read(MAX_ID, MAX_INT, data, 1);
    if (data[0] & MAX_INT_HR_RDY) {

    }
    // turn off
    data[0] = MAX_MODE_SHDN;
    I2C.write(MAX_ID, MAX_MODE, data, 1);
}

void maxRequestHeartRate(void) {
    uint8_t data[1];
    // turn HR on
    data[0] = MAX_MODE_HR_ONLY;
    I2C.write(MAX_ID, MAX_MODE, data, 1);
    // wait for interrupt
}
