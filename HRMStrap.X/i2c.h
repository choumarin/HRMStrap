/* 
 * Author: ckungler
 *
 * Created on July 22, 2016, 2:27 PM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

    typedef enum {
        I2C_OK,
        I2C_ERROR
    } I2CResult;

    typedef struct {
        I2CResult(*read)(uint8_t id, uint8_t address, uint8_t* data, size_t len);
        I2CResult(*write)(uint8_t id, uint8_t address, uint8_t* data, size_t len);
    } I2CObject;

    extern I2CObject I2C;

    void I2CInit(void);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

