/**
 * Copyright (C) 2021 jensenhua(writeforever@foxmail.com)
 *
 * This file is part of sdol.
 *
 * sdol is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * sdol is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with sdol.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stcmcu.h"
#include "system.h" /* opreations of system */
#include "ds1302.h"
#include "tm1650.h"

static struct system_operations my_sys_opr;
static struct ds1302_operations my_ds1302_opr;
static struct tm1650_operations my_tm1650_opr;
const unsigned char tm1650_segment_value[10] = {
    0x3f, /* `0` */
    0x06, /* `1` */
    0x5b, /* `2` */
    0x4f, /* `3` */
    0x66, /* `4` */
    0x6d, /* `5` */
    0x7d, /* `6` */
    0x07, /* `7` */
    0x7f, /* `8` */
    0x6f, /* `9` */
};

/**
 * @biref all initialization operations for mcu and device.
 */
void SystemInit()
{
    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
    /* register driver of system*/
    // register_system_operations(&my_sys_opr);
    // my_sys_opr.iomux(P32P33_I2C);

    /* register driver of ds1302 */
    register_ds1302_operations( &my_ds1302_opr );
    my_ds1302_opr.init();
    register_tm1650_operations( &my_tm1650_opr );
    my_tm1650_opr.init();
}

void Delay1000ms()      //@11.0592MHz
{
    unsigned char i, j, k;
    i = 57;
    j = 27;
    k = 112;

    do {
        do {
            while( --k );
        }
        while( --j );
    }
    while( --i );
}

/**
*@description main thread of this project
*@param
*@return
*/
int main( void )
{
    uint8_t ten, biz, res;
    SystemInit();
    my_tm1650_opr.set_brightness( TM1650_BRIGHTNESS_LEVEL_8 );
    my_tm1650_opr.show_bit( TM1650_BIT_1, tm1650_segment_value[1] );
    my_tm1650_opr.show_bit( TM1650_BIT_2, TM1650_SEGMENT_VALUE_2 );
    my_tm1650_opr.show_bit( TM1650_BIT_3, TM1650_SEGMENT_VALUE_3 );
    my_tm1650_opr.show_bit( TM1650_BIT_4, TM1650_SEGMENT_VALUE_4 );
    // my_ds1302_opr.write_register( 0x80, 0x00 );
    // Delay1000ms();
    // my_ds1302_opr.write_register( 0x82, 0x00 );
    // Delay1000ms();
    // my_ds1302_opr.write_register( 0x84, 0x00 );

    // while( 1 ) {
    //     res = my_ds1302_opr.read_register(0x85);
    //     ten = (res & 0x10) >> 4;
    //     biz = (res & 0x0f);
    //     my_tm1650_opr.show_bit(TM1650_BIT_1, tm1650_segment_value[ten]);
    //     my_tm1650_opr.show_bit(TM1650_BIT_2, tm1650_segment_value[biz]);


    //     res = my_ds1302_opr.read_register(0x83);
    //     ten = (res & 0xf0) >> 4;
    //     biz = (res & 0x0f);
    //     my_tm1650_opr.show_bit(TM1650_BIT_3, tm1650_segment_value[ten]);
    //     my_tm1650_opr.show_bit(TM1650_BIT_4, tm1650_segment_value[biz]);
    //     Delay1000ms();
    //     Delay1000ms();
    // }

    return 0;
}
