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

#include "tm1650.h"

static tm1650_config_t __mTM1650_config = {0};

/**
 * @brief TM1650写寄存器函数
 *
 * TM1650使用非标准I2C协议，需要直接发送命令+数据，
 * 没有设备地址概念，使用gpio管脚模拟时序。
 *
 * @param command 需要发送的命令
 * @param dat     需要发送的数据
 */
static void tm1650_write_register( uint8_t command, uint8_t dat )
{
    gpio_i2c_start();
    gpio_i2c_sendbyte( command ); //slave address
    gpio_i2c_revack();
    gpio_i2c_sendbyte( dat );
    gpio_i2c_revack();
    gpio_i2c_stop();
}

static uint8_t tm1650_read_key()
{
    uint8_t byte;
    
    Fgpio_i2c_start();
    gpio_i2c_sendbyte( TM1650_COMMAND_READ_KEY );
    gpio_i2c_revack();
    byte = gpio_i2c_readbyte();
    gpio_i2c_revack();
    gpio_i2c_stop();
    
    return byte;    
}

/**
 * @brief TM1650数码管辉度等级设置
 *
 * 设置数码管的亮度级别，可设置从1到8的级别。
 *
 * @param level 辉度等级
 */
static void tm1650_set_brightness( tm1650_brightness_level_t level )
{
    __mTM1650_config.display_register.brightness = level;
    tm1650_write_register( TM1650_DISPLAY_REG, __mTM1650_config.full );
}

/**
 * @brief TM650数码管显示控制函数
 *
 * 设置数码管显示开关，可设置开启 / 关闭。
 *
 * @param state 开关
 */
static void tm1650_set_display( tm1650_display_power_t state )
{
    __mTM1650_config.display_register.power = state;
    tm1650_write_register( TM1650_DISPLAY_REG, __mTM1650_config.full );
}

/**
 * @brief TM1650数码管段数设置函数
 *
 * 设置数码管的格式，可选择数码管为7段还是8段。
 *
 * @param format 段格式
 */
static void tm1650_set_segment_format( tm1650_segment_format_t format )
{
    __mTM1650_config.display_register.segment_format = format;
    tm1650_write_register( TM1650_DISPLAY_REG, __mTM1650_config.full );
}

/**
 * @brief TM1650位显示函数
 *
 * 将给定的段码值显示到对应的位
 *
 * @param which 位号
 * @param value 段码值
 */
static void tm1650_show_bit( tm1650_bit_selection_t which,
                             tm1650_segment_value_t value )
{
    tm1650_write_register( which, value );
}

/**
 * @brief TM1650初始化函数
 *
 * 进行的初始化操作
 * 1. 设置显示打开
 * 2. 设置辉度等级为1
 * 3. 设置数码管段格式为8段
 *
 */
static void tm1650_init()
{
    /* enable pin internal pull up res */
    // P3PU &= ~(0x03 << 2);
    // P3PU |= (0x03 << 2);
    /**
     * default mode:
     * power: ON
     * brightness: level 1
     * segment format: 8 bit
     */
    __mTM1650_config.display_register.power = TM1650_DISPLAY_POWER_ON;
    __mTM1650_config.display_register.brightness = TM1650_BRIGHTNESS_LEVEL_1;
    __mTM1650_config.display_register.segment_format = TM1650_SEGMENT_FORMAT_8;
    tm1650_write_register( 0x48, __mTM1650_config.full );
}

static void tm1650_deinit()
{
}

/**
 * @brief TM1650操作注册函数。
 *
 * 将TM1650的操作函数注册进结构体函数指针。
 *
 * @param opr 操作函数结构体
 */
void register_tm1650_operations( struct tm1650_operations *opr )
{
    opr->init = tm1650_init;
    opr->write_register = tm1650_write_register;
    opr->read_key = tm1650_read_key;
    opr->set_brightness = tm1650_set_brightness;
    opr->set_display = tm1650_set_display;
    opr->set_segment_format = tm1650_set_segment_format;
    opr->show_bit = tm1650_show_bit;
}
