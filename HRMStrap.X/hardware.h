#ifndef HARDWARE_H
#define	HARDWARE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // PIN Definitions
    
#define HRM_INT PORTCbits.RC5
#define HRM_INT_TRIS TRISCbits.TRISC5
#define HRM_EN LATCbits.LATC4
#define HRM_EN_TRIS TRISCbits.TRISC4
    
#define DATA_RX_TRIS TRISAbits.TRISA2
#define DATA_RX 
#define DATA_TX_TRIS TRISCbits.TRISC0
#define DATA_TX 
    
#define SCL_TRIS TRISAbits.TRISA5
#define SDA_TRIS TRISAbits.TRISA4

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* HARDWARE_H */

