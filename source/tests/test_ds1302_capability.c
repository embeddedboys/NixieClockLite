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

#include "ds1302.h"
#include "tm1650.h"

static struct ds1302_operations nMyDs1302Opr;
static struct tm1650_operations nMyTm1650Opr;
static uint16_t nCount = 0;
static uint16_t nInterruptCount = 0;

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

void main( void )
{
    uint8_t loop = 1;

    SystemInit();
    
}