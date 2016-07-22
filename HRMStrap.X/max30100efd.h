/* 
 * Author: ckungler
 *
 * Created on July 22, 2016, 2:20 PM
 */

#ifndef MAX30100EFD_H
#define	MAX30100EFD_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct {
        void (*requestHeartRate)(void);
        void (*ISR)(void);
    } Max30100efdObject;

    extern Max30100efdObject Max;
    
    void Max30100efdInit(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MAX30100EFD_H */

