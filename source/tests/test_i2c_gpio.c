/**
 * Copyright (C) 2022 Zheng Hua(writeforever@foxmail.com)
 *
 * SDOL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SDOL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with SDOL. If not, see <http://www.gnu.org/licenses/>.
 */

#include "gpio_i2c.h"

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

    gpio_i2c_init();
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

void main( void )
{
    SystemInit();

    while( 1 ) {
        
        gpio_i2c_start();
        gpio_i2c_sendbyte( 0x48 ); 
        gpio_i2c_revack();
        gpio_i2c_sendbyte( 0x71 ); 
        gpio_i2c_revack();
        gpio_i2c_stop();

        Delay1000ms();
    }
}