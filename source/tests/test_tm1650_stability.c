// Copyright (C) 2022 16578
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

#include "stcmcu.h"
#include "tm1650.h"


static struct tm1650_operations my_tm1650_opr;
static uint16_t nCount = 0;
static uint16_t nInterruptCount = 0;

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
    register_tm1650_operations( &my_tm1650_opr );
    my_tm1650_opr.init();
}

void Delay1000ms()      //@24.000MHz
{
    unsigned char i, j, k;
    _nop_();
    _nop_();
    i = 122;
    j = 193;
    k = 128;

    do {
        do {
            while( --k );
        }
        while( --j );
    }
    while( --i );
}

void Timer2_Isr() interrupt 12
{
    if( nInterruptCount++ == 100 ) {
        nCount++;
        nInterruptCount = 0;
    }
}

void Timer2Init(void)		//10毫秒@23.894MMHz
{
	AUXR &= 0xFB;		//定时器时钟12T模式
	T2L = 0x38;		//设置定时初始值
	T2H = 0xB2;		//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时
    IE2 = 0x04;
    EA = 1;
}


/**
*@description main thread of this project
*@param
*@return
*/
int main( void )
{
    uint8_t loop = 1;
    SystemInit();
    // Timer2Init();
    my_tm1650_opr.set_brightness( TM1650_BRIGHTNESS_LEVEL_8 );
    my_tm1650_opr.show_bit( TM1650_BIT_1, TM1650_SEGMENT_VALUE_0 );
    my_tm1650_opr.show_bit( TM1650_BIT_2, TM1650_SEGMENT_VALUE_0 );
    my_tm1650_opr.show_bit( TM1650_BIT_3, TM1650_SEGMENT_VALUE_0 );
    my_tm1650_opr.show_bit( TM1650_BIT_4, TM1650_SEGMENT_VALUE_0 );

    while( loop ) {
        if( nCount / 1000 > 9 ) {
            nCount = 0;
        }
        else {
            my_tm1650_opr.show_bit( TM1650_BIT_1, tm1650_segment_value[nCount / 1000] );
        }

        my_tm1650_opr.show_bit( TM1650_BIT_2, tm1650_segment_value[nCount / 100 % 10] );
        my_tm1650_opr.show_bit( TM1650_BIT_3, tm1650_segment_value[nCount / 10 % 10] );
        my_tm1650_opr.show_bit( TM1650_BIT_4, tm1650_segment_value[nCount % 10] );

        
    }

    return 0;
}