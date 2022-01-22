/**
 * @file i2c.h
 * @author Zheng hua (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-22
 * 
 * Copyright (c) 2022 Zheng Hua(writeforever@foxmail.com)
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 * 
 */

#ifndef __I2C_H
#define __I2C_H

/*********************
*      INCLUDES
*********************/
#ifndef STCMCU_H
    #include "stcmcu.h"
#endif

/*********************
 *      DEFINES
 *********************/
#define I2CCFG   (*(unsigned char volatile xdata *)0xfe80)
#define I2CMSCR  (*(unsigned char volatile xdata *)0xfe81)
#define I2CMSST  (*(unsigned char volatile xdata *)0xfe82)
#define I2CSLCR  (*(unsigned char volatile xdata *)0xfe83)
#define I2CSLST  (*(unsigned char volatile xdata *)0xfe84)
#define I2CSLADR (*(unsigned char volatile xdata *)0xfe85)
#define I2CTXD   (*(unsigned char volatile xdata *)0xfe86)
#define I2CRXD   (*(unsigned char volatile xdata *)0xfe87)
#define I2CMSAUX (*(unsigned char volatile xdata *)0xfe88)

/**********************
*      TYPEDEFS
**********************/
typedef struct
{
    uint8_t dat;
}i2c_handle_t;

typedef struct{
    uint8_t config;
}i2c_config_t;

/**********************
*      STRUCT
**********************/


/**********************
* GLOBAL PROTOTYPES
**********************/
void i2c_init();
void i2c_start();
void i2c_revack();
void i2c_sndack();
void i2c_sndnack();
void i2c_stop();
uint8_t i2c_readbyte();
void i2c_sendbyte( uint8_t byte );

/**********************
*      MACROS
**********************/

#endif /* I2C_H */
