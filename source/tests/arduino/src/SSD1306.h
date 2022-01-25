#ifndef __SSD1306_H
#define __SSD1306_H

#include <inttypes.h>

/* using i2c interface of ssd1306 as default */
#ifndef SSD1306_BS_MODE
#define SSD1306_BS_MODE_I2C 1
#endif

/* oled param */
#define OLED_HOR_RES_MAX 128
#define OLED_VER_RES_MAX 64
#define OLED_COLOR_DEPTH 1

/* useful defines like buffer operation */
#define OFFSET(p, c) ((p)*128 + (c)-1)
#define GET_PAGE_FROM_BUFFER(i) (i / 128)
#define GET_COL_FROM_BUFFER(i) (i % 128)

#define GET_PAGE(pc) (pc >> 16)
#define GET_COL(pc) (pc & 0xFFFF)
#define PAGE_COL(page, col) ((page << 16) | col)
#define PAGE_COL_GET_X(pc) (GET_COL(pc))
#define PAGE_COL_GET_Y(pc) (GET_PAGE(pc) * 8)

/* the transmited value type */
#define COMMAND 0x00
#define DATA 0x40

/* for small oled, a uint8_t is enough to save a point data */
#if ((OLED_HOR_RES_MAX <= 255) && (OLED_VER_RES_MAX <= 255))
typedef uint8_t oled_coord_t;
typedef uint8_t oled_size_t;
#else
typedef uint16_t oled_coord_t;
typedef uint16_t oled_size_t;
#endif

/* obviously its used to save a point data */
typedef struct
{
    oled_coord_t x;
    oled_coord_t y;
} oled_point_t;

/* make a rectangle area */
typedef struct
{
    oled_coord_t x1;
    oled_coord_t y1;
    oled_coord_t x2;
    oled_coord_t y2;
} oled_area_t;

/* the color of oled, based on oled color depth */
typedef union
{
    struct
    {
        uint8_t blue : 2;
        uint8_t green : 3;
        uint8_t red : 3;
    } chnnel;
    uint8_t full;
} oled_color8_t;

#if (OLED_COLOR_DEPTH == 1)
typedef uint8_t oled_color_t;
#else
typedef oled_color8_t oled_color_t;
#endif

/* oled data or command. */
typedef uint8_t oled_dc_t;

/* oled buffer typedef */
typedef uint8_t oled_buffer_t;

/* oled pin typedef */
typedef uint8_t oled_pin_t;

typedef enum
{
    OLED_INTERFACE_I2C = 0x00,
    OLED_INTERFACE_SPI = 0x01,
} oled_interface_t;

typedef enum
{
    OLED_COLOR_DEPTH_1 = 0x00,
    OLED_COLOR_DEPTH_8 = 0x01,
    OLED_COLOR_DEPTH_16 = 0x02,
    OLED_COLOR_DEPTH_24 = 0x03,
    OLED_COLOR_DEPTH_32 = 0x04,
}oled_color_depth_t;

/* a handle struct for ssd1306 */
typedef struct
{
    oled_interface_t interface;
    
    oled_size_t width;
    oled_size_t height;
    oled_color_depth_t depth;

    oled_dc_t *msg_buf;

    uint8_t lock;
} oled_handle_t;

class SSD1306
{
public:
    SSD1306(oled_pin_t scl, oled_pin_t sda);
    SSD1306(oled_pin_t sclk, oled_pin_t mosi,
            oled_pin_t miso, oled_pin_t nss);

    void init(oled_handle_t handle,
              oled_interface_t interface,
              oled_size_t width, oled_size_t height,
              oled_pin_t scl, oled_pin_t sda,
              oled_pin_t sclk, oled_pin_t mosi,
              oled_pin_t miso, oled_pin_t nss);

    void clear();

    /* old api */
    void set_pos(uint8_t page, uint8_t col);
    void put_char(uint8_t page, uint8_t col, uint8_t c);
    void put_string(uint8_t page, uint8_t col, uint8_t *str);

    /* new api */
    void set_pixel(oled_coord_t x, oled_coord_t y, oled_color_t color);
    void put_ascii(oled_coord_t x, oled_coord_t y, uint16_t c);
    void put_asciistring(oled_coord_t x, oled_coord_t y, uint16_t *str);

    void flush();

private:
    void write_cmd(oled_dc_t val);
    void write_dat(oled_dc_t val);

    oled_pin_t _scl_pin;
    oled_pin_t _sda_pin;

    oled_pin_t _sclk_pin;
    oled_pin_t _mosi_pin;
    oled_pin_t _miso_pin;
    oled_pin_t _nss_pin;

    static oled_buffer_t m_oled_buffer[1024]; /* oled display buffer */
};

#endif