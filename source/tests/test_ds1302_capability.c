/**
 * @file test_ds1302_capability.c
 * @author Zheng Hua (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-01-22
 *
 * MIT License
 *
 * Copyright 2022 Zheng Hua(writeforever@foxmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "ds1302.h"
#include "tm1650.h"

static struct ds1302_operations nMyDs1302Opr;
static struct tm1650_operations nMyTm1650Opr;
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

void Timer2Init( void )     //10毫秒@23.894MMHz
{
    AUXR &= 0xFB;       //定时器时钟12T模式
    T2L = 0x38;     //设置定时初始值
    T2H = 0xB2;     //设置定时初始值
    AUXR |= 0x10;       //定时器2开始计时
    IE2 = 0x04;
    EA = 1;
}

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
    
    register_ds1302_operations( &nMyDs1302Opr );
    nMyDs1302Opr.init();
    
    register_tm1650_operations( &nMyTm1650Opr );
    nMyTm1650Opr.init();
}

void Timer2_Isr() interrupt 12
{
    if( nInterruptCount++ == 100 ) {
        nCount++;
        nInterruptCount = 0;
    }
}

void Delay1000ms()      //@24.000MHz
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
            while( --k );
        }
        while( --j );
    }
    while( --i );
}

void main( void )
{
    uint8_t loop = 1;
    uint8_t disp = 1;
    uint8_t byte_read = 0x00;
    
    SystemInit();
    
    // nMyDs1302Opr.write_register( 0x80, 0x05 );

    while( loop ) {
        // __ds1302_set_rst(1);
        // __ds1302_writebyte(0x82);
        // __ds1302_writebyte(0x11);
        // __ds1302_set_rst(0);
        byte_read = nMyDs1302Opr.read_register( 0xBF );
        nMyTm1650Opr.show_bit( TM1650_BIT_4,
                               tm1650_segment_value[( byte_read & 0x0f )] );
        nMyTm1650Opr.show_bit( TM1650_BIT_3,
                               tm1650_segment_value[( byte_read & 0x70 ) >> 4] );
                               
        disp = !disp;
        nMyTm1650Opr.show_bit( TM1650_BIT_1,
                               tm1650_segment_value[( disp ) ? 1 : 0] );
        Delay1000ms();
    }
}