/**
 * @file gpio_i2c.h
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

#ifndef __GPIO_I2C_H
#define __GPIO_I2C_H

/*********************
*      INCLUDES
*********************/
#ifndef STCMCU_H
    #include "stcmcu.h"
#endif

/*********************
 *      DEFINES
 *********************/
sbit GPIO_I2C_SCL = P3 ^ 2;
sbit GPIO_I2C_SDA = P3 ^ 3;

/* cost 416ns in STC8G 24MHz IRC */
#define delay() do { \
    _nop_();         \
    _nop_();         \
    _nop_();         \
    _nop_();         \
    _nop_();         \
    _nop_();         \
    _nop_();         \
    _nop_();         \
    _nop_();         \
    _nop_();         \
}while(0);
/**********************
*      TYPEDEFS
**********************/
typedef struct {
    uint8_t lock;
} gpio_i2c_handle_t;

typedef struct {
    uint32_t speed;
} gpio_i2c_config_t;

/**********************
*      STRUCT
**********************/

/**********************
* GLOBAL PROTOTYPES
**********************/
void gpio_i2c_init();
void gpio_i2c_start();
uint8_t gpio_i2c_revack();
void gpio_i2c_sndack();
void gpio_i2c_sndnack();
void gpio_i2c_stop();
uint8_t gpio_i2c_readbyte();
void gpio_i2c_sendbyte( uint8_t byte_in );

/**********************
*      MACROS
**********************/

#endif
