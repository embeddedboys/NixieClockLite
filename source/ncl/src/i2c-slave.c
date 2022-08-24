/**
 * @file i2c-slave.c
 * @author Zheng Hua (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-20
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

#include "i2c-slave.h"

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#define LOOP_SIZE(index, buf)(index%(ARRAY_SIZE(buf)))

static unsigned char buf_i2c_slave_index = 0;
static unsigned char buf_i2c_slave_index_last = 0;
static unsigned char __xdata buf_i2c_slave[256];

static char read_pos = 0;

static char skip_addr = 1;
static char skip_mem = 1;


void i2c_slave_init()
{
	I2CCFG = 0x81;		/* Enable I2C Controller slave mode */
	I2CSLADR = 0x92;	/* Set I2C slave addr, PS: the addr is I2CSLADR[7:1] >> 1 */

	I2CSLST = 0x00;		/* Clear i2c slave status reg */
	I2CSLCR = 0x78;		/* Enable interrupt of i2c slave */
}


char *i2c_slave_get_buf()
{
	return buf_i2c_slave;
}

void i2c_slave_isr() __interrupt (24)
{
	int tmp;

	// _push_(P_SW2);
	P_SW2 |= 0x80;
	if(I2CSLST & 0x40) {	/* received a START signal */
		I2CSLST &= ~0x40;	/* START signal handled */
	}
	else if(I2CSLST & 0x20) {	/* received a BYTE data*/
		I2CSLST &= ~0x20;	/* BYTE data handled */
		if(skip_addr) {
			skip_addr = 0;
		}
		/*
		else if(skip_mem) {
			skip_mem = 0;
		}
		*/
		else {
			buf_i2c_slave[LOOP_SIZE(buf_i2c_slave_index++, buf_i2c_slave)] = I2CRXD;
		}
		
		I2CTXD = buf_i2c_slave[buf_i2c_slave_index-2];
	}
	else if(I2CSLST & 0x10) {
		I2CSLST &= ~0x10;
		I2CTXD = buf_i2c_slave[(buf_i2c_slave_index--)-3];
	}
	else if(I2CSLST & 0x08) {	/* received a STOP signal */
		I2CSLST &= ~0x08;	/* STOP signal handled */

		buf_i2c_slave_index = 0;
		skip_addr = 1;
		//skip_mem = 1;
	}
	// _pop_(P_SW2);
}

