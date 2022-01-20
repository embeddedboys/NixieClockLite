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

#include "i2c.h"

/**
 * @brief 初始化I2C控制器
 *
 * 允许I2C功能
 * 设置为主机模式
 * 总线速度设置为400K（FOSC=24MHz）
 *
 */
void i2c_init()
{
    I2CCFG = 0xD3; /* FOSC 24MHz  I2C 400KHz */
    
    I2CMSAUX &= ~(1 << 0); /* 禁用自动发送功能 */

    I2CMSST = 0x00; /* 清空主机状态寄存器 */
}

/**
 * @brief I2C控制器等待查询方式
 *
 * 当处于主机模式的I2C控制器执行完成寄存器I2CMSCR中MSCMD命令后产生中断信号，
 * 硬件自动将I2CMSST的MSIF位置1，向CPU发送中断请求，响应中断后MSIF必须用软件清零。
 * 
 */
void __i2c_wait()
{
    while( !( I2CMSST & 0x40 ) );

    I2CMSST &= ~0x40;
}

/**
 * @brief I2C总线起始命令
 *
 * MSCMD=0001
 * 发送START信号。如果当前I2C控制器处于空闲状态，
 * 即 MSBUSY (I2CMSST7）为0时，写此命令会使控制器进入忙状态，
 * 硬件自动将MSBUSY状态位置1，并开始发送START信号;
 * 若当前IC控制器处于忙状态，写此命令可触发发送START信号。
 *
 */
void i2c_start()
{
    I2CMSCR = 0x01;
    __i2c_wait();
}

/**
 * @brief I2C总线发送数据命令
 * 
 * 写此命令后，I2C总线控制器会在SCL管脚上产生8个时钟，
 * 并将I2CTXD寄存器里面数据按位送到SDA管脚上（先发送高位数据)。
 *
 * @param byte 要发送的数据
 */
void i2c_sendbyte( uint8_t byte )
{
    I2CTXD = byte;
    I2CMSCR = 0x02;
    __i2c_wait();
}

/**
 * @brief I2C总线接收ACK命令
 * 
 * 写此命令后，I2C总线控制器会在SCL管脚上产生1个时钟，
 * 并将从SDA端口上读取的数据保存到MSACKI (I12CMSST.1)。
 * 
 */
void i2c_revack()
{
    I2CMSCR = 0x03;
    __i2c_wait();
}

/**
 * @brief I2C总线接受数据命令
 * 
 * 写此命令后，I2C总线控制器会在SCL管脚上产生8个时钟，
 * 并将从SDA端口上读取的数据依次左移到I2CRXD寄存器（先接收高位数据)。接
 * 
 * @return uint8_t 返回I2CRXD寄存器中的内容
 */
uint8_t i2c_readbyte()
{
    I2CMSCR = 0x04;
    __i2c_wait();
    return I2CRXD;
}

/**
 * @brief I2C总线发送ACK命令
 * 
 * 写此命令后，I2C总线控制器会在SCL管脚上产生1个时钟，
 * 并将MSACKO (I2CMSST.0)中的数据发送到SDA端口。
 * 
 */
void i2c_sndack()
{
    I2CMSST = 0x00;
    I2CMSCR = 0x05;
    __i2c_wait();
}

/**
 * @brief I2C总线发送NACK命令
 * 
 * 写此命令后，I2C总线控制器会在SCL管脚上产生1个时钟，
 * 并将MSACKO (I2CMSST.0)中的数据发送到SDA端口。
 * 
 */
void i2c_sndnack()
{
    I2CMSST = 0x01;
    I2CMSCR = 0x05;
    __i2c_wait();
}

/**
 * @brief I2C总线停止命令
 * 
 * 发送STOP信号。写此命令后，TPC总线控制器开始发送STOP信号。
 * 信号发送完成后，硬件自动将MSBUSY状态位清零。
 * 
 */
void i2c_stop()
{
    I2CMSCR = 0x06;
    __i2c_wait();
}

/*------------- complex operations -------------*/
/**
 * @brief I2C组合命令，起始、发送数据、接收ACK。
 * 
 * 此命令为命令0001、命令0010、命令0011三个命令的组合，
 * 下此命令后控制器会依次执行这三个命令。
 * 
 * @param byte 要发送的数据
 */
void i2c_start_sendbyte_revack(uint8_t byte)
{
    I2CTXD = byte;
    I2CMSCR = 0x09;
    __i2c_wait();
}

/**
 * @brief I2C组合命令，发送数据、接收ACK。
 * 
 * 此命令为命令0010、命令0011两个命令的组合，
 * 下此命令后控制器会依次执行这两个命令。
 * 
 * @param byte 要发送的数据
 */
void i2c_sendbyte_revack(uint8_t byte)
{
    I2CTXD = byte;
    I2CMSCR = 0x0A;
}

/**
 * @brief I2C组合命令，接收数据，发送ACK命令。
 * 
 * 此命令为命令0100、命令0101两个命令的组合，下此命令后控制器会依次执行这两个命令。
 * 注意:此命令所返回的应答信号固定为ACK(0)，不受MSACKO位的影响。
 * 
 * @return uint8_t 返回I2CRXD中的内容
 */
uint8_t i2c_readbyte_sendack()
{
    I2CMSCR = 0x0B;
    __i2c_wait();
    return I2CRXD;
}

/**
 * @brief I2C组合命令，接收数据，发送NACK命令。
 * 
 * 此命令为命令0100、命令0101两个命令的组合，下此命令后控制器会依次执行这两个命令。
 * 注意:此命令所返回的应答信号固定为NAK (1)，不受MSACKO位的影响。
 * 
 * @return uint8_t 
 */
uint8_t i2c_readbyte_sendnack()
{
    I2CMSCR = 0x0C;
    __i2c_wait();
    return I2CRXD;
}
