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
#include "uart.h"
#include "i2c-slave.h"

static struct system_operations my_sys_opr;
static struct uart_operations my_uart_opr;

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

	register_uart_operations(&my_uart_opr);
	my_uart_opr.fast_init();

	// i2c_slave_init();

	ES=1;
    EA=1;
}

void Delay1000ms()		//@24.000MHz
{
	unsigned char i, j, k;

	NOP();
	NOP();
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
	static int count = 0;
	char *pbuf;

    SystemInit();

	while(1) {

		my_uart_opr.puts("Hello, World!");
		my_uart_opr.putchar('0'+count);
		my_uart_opr.puts("\r\n");


		// pbuf = i2c_slave_get_buf();

		/*
		my_uart_opr.putchar(pbuf[0]);
		my_uart_opr.putchar(pbuf[1]);
		my_uart_opr.putchar(pbuf[2]);
		my_uart_opr.putchar(pbuf[3]);
		*/

		// my_uart_opr.puts(pbuf);
		
		// count++;
		// if(count>9)
		// 	count=0;
		Delay1000ms();
	}

    return 0;
}
