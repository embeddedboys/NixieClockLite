#include "SSD1306.h"

void SSD1306::init(oled_handle_t handle,
                   oled_interface_t interface,
                   oled_size_t width, oled_size_t height,
                   oled_pin_t scl, oled_pin_t sda,
                   oled_pin_t sclk, oled_pin_t mosi,
                   oled_pin_t miso, oled_pin_t nss)
{
    /* pin association */
    _scl_pin = scl;
    _sda_pin = sda;

    _sclk_pin = sclk;
    _mosi_pin = mosi;
    _miso_pin = miso;
    _nss_pin  = nss;

    /*  */
}

void SSD1306::write_cmd(oled_dc_t val)
{
#if SSD1306_BS_MODE_I2C
    /* I2C logic here*/

#else
    /* SPI logic here*/

#endif
}

void SSD1306::write_dat(oled_dc_t val)
{
#if SSD1306_BS_MODE_I2C
    /* I2C logic here*/
#else
    /* SPI logic here*/
#endif
}