// Copyright (C) 2022 Zheng Hua(writeforever@foxmail.com)
// 
// SDOL is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// SDOL is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with SDOL. If not, see <http://www.gnu.org/licenses/>.



/**
 * @file i2c.h
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
