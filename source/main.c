/**
 * @file main.c
 * @author Zheng Hua (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-22
 * 
 * Copyright 2022 Zheng Hua(writeforever@foxmail.com)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 * 
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

void Delay1000ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 122;
	j = 193;
	k = 128;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
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
