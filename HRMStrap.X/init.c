/* 
 * Author: ckungler
 *
 * Created on July 22, 2016, 2:20 PM
 */

#include "init.h"
#include "max30100efd.h"

void initClock();
void initPeripherals();

void init(void) {
    initClock();
    initPeripherals();
}

void initClock() {

}

void initPeripherals() {
    Max30100efdInit();
    
}
