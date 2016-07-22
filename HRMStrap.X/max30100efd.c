/* 
 * Author: ckungler
 *
 * Created on July 22, 2016, 2:20 PM
 */

#include "max30100efd.h"
#include "i2c.h"

Max30100efdObject Max;

void maxISR(void);
void maxRequestHeartRate(void);

void Max30100efdInit(void) {
    Max.ISR = maxISR;
    Max.requestHeartRate = maxRequestHeartRate;
    
    I2CInit();
}

void maxISR(void) {

}

void maxRequestHeartRate(void) {

}
