/* 
 * Author: ckungler
 *
 * Created on July 22, 2016, 2:20 PM
 */

#ifndef HARDWARE_H
#define	HARDWARE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#define _XTAL_FREQ 8000000UL // 8MHz
    
    // PIN Definitions
    
#define HRM_INT PORTCbits.RC5
#define HRM_INT_TRIS TRISCbits.TRISC5
#define HRM_EN LATCbits.LATC4
#define HRM_EN_TRIS TRISCbits.TRISC4
    
#define DATA_RX_TRIS TRISAbits.TRISA2
#define DATA_RX 
#define DATA_TX_TRIS TRISCbits.TRISC0
#define DATA_TX 
    
#define SCL_PIN 0b00101 //RA5
#define SDA_PIN 0b00100 //RA4

#define SCL_PPS RA5PPSbits.RA5PPS
#define SDA_PPS RA4PPSbits.RA4PPS
    
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* HARDWARE_H */

