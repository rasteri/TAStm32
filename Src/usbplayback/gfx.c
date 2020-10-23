#include <stdint.h>

const uint8_t GFX_DIAMOND[] = {
	0x00,0x80,0x01,0x00,
	0x00,0xc0,0x03,0x00,
	0x00,0xe0,0x07,0x00,
	0x00,0xf0,0x0f,0x00,
	0x00,0xf8,0x1f,0x00,
	0x00,0xfc,0x3f,0x00,
	0x00,0xfe,0x7f,0x00,
	0x00,0xff,0xff,0x00,
	0x80,0xff,0xff,0x01,
	0xc0,0xff,0xff,0x03,
	0xe0,0xff,0xff,0x07,
	0xf0,0xff,0xff,0x0f,
	0xf8,0xff,0xff,0x1f,
	0xfc,0xff,0xff,0x3f,
	0xfe,0xff,0xff,0x7f,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xfe,0xff,0xff,0x7f,
	0xfc,0xff,0xff,0x3f,
	0xf8,0xff,0xff,0x1f,
	0xf0,0xff,0xff,0x0f,
	0xe0,0xff,0xff,0x07,
	0xc0,0xff,0xff,0x03,
	0x80,0xff,0xff,0x01,
	0x00,0xff,0xff,0x00,
	0x00,0xfe,0x7f,0x00,
	0x00,0xfc,0x3f,0x00,
	0x00,0xf8,0x1f,0x00,
	0x00,0xf0,0x0f,0x00,
	0x00,0xe0,0x07,0x00,
	0x00,0xc0,0x03,0x00,
	0x00,0x80,0x01,0x00
};

const uint8_t GFX_DIAMOND_BG[] = {
	0x00,0x80,0x01,0x00,
	0x00,0xc0,0x03,0x00,
	0x00,0x60,0x06,0x00,
	0x00,0x30,0x0c,0x00,
	0x00,0x18,0x18,0x00,
	0x00,0x0c,0x30,0x00,
	0x00,0x06,0x60,0x00,
	0x00,0x03,0xc0,0x00,
	0x80,0x01,0x80,0x01,
	0xc0,0x00,0x00,0x03,
	0x60,0x00,0x00,0x06,
	0x30,0x00,0x00,0x0c,
	0x18,0x00,0x00,0x18,
	0x0c,0x00,0x00,0x30,
	0x06,0x00,0x00,0x60,
	0x03,0x00,0x00,0xc0,
	0x03,0x00,0x00,0xc0,
	0x06,0x00,0x00,0x60,
	0x0c,0x00,0x00,0x30,
	0x18,0x00,0x00,0x18,
	0x30,0x00,0x00,0x0c,
	0x60,0x00,0x00,0x06,
	0xc0,0x00,0x00,0x03,
	0x80,0x01,0x80,0x01,
	0x00,0x03,0xc0,0x00,
	0x00,0x06,0x60,0x00,
	0x00,0x0c,0x30,0x00,
	0x00,0x18,0x18,0x00,
	0x00,0x30,0x0c,0x00,
	0x00,0x60,0x06,0x00,
	0x00,0xc0,0x03,0x00,
	0x00,0x80,0x01,0x00
};

const uint8_t GFX_BUTTON[] =  {
	0x00,0xf0,0x0f,0x00,
	0x00,0xfe,0x7f,0x00,
	0x80,0xff,0xff,0x01,
	0xc0,0xff,0xff,0x03,
	0xe0,0xff,0xff,0x07,
	0xf0,0xff,0xff,0x0f,
	0xf8,0xff,0xff,0x1f,
	0xfc,0xff,0xff,0x3f,
	0xfc,0xff,0xff,0x3f,
	0xfe,0xff,0xff,0x7f,
	0xfe,0xff,0xff,0x7f,
	0xfe,0xff,0xff,0x7f,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xfe,0xff,0xff,0x7f,
	0xfe,0xff,0xff,0x7f,
	0xfe,0xff,0xff,0x7f,
	0xfc,0xff,0xff,0x3f,
	0xfc,0xff,0xff,0x3f,
	0xf8,0xff,0xff,0x1f,
	0xf0,0xff,0xff,0x0f,
	0xe0,0xff,0xff,0x07,
	0xc0,0xff,0xff,0x03,
	0x80,0xff,0xff,0x01,
	0x00,0xfe,0x7f,0x00,
	0x00,0xf0,0x0f,0x00
};


const uint8_t GFX_BUTTONS_BG[] = {
	0x00,0x00,0x00,0xe0,0x1f,0x00,0x00,0x00,
	0x00,0x00,0x00,0x3c,0xf0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x07,0x80,0x03,0x00,0x00,
	0x00,0x00,0x80,0x01,0x00,0x06,0x00,0x00,
	0x00,0x00,0xc0,0x00,0x00,0x0c,0x00,0x00,
	0x00,0x00,0x60,0x00,0x00,0x18,0x00,0x00,
	0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,
	0x00,0x00,0x18,0x00,0x00,0x60,0x00,0x00,
	0x00,0x00,0x08,0x00,0x00,0x40,0x00,0x00,
	0x00,0x00,0x0c,0x00,0x00,0xc0,0x00,0x00,
	0x00,0x00,0x04,0x00,0x00,0x80,0x00,0x00,
	0x00,0x00,0x04,0x00,0x00,0x80,0x00,0x00,
	0x00,0x00,0x06,0x00,0x00,0x80,0x01,0x00,
	0x00,0x00,0x02,0x00,0x00,0x00,0x01,0x00,
	0x00,0x00,0x02,0x00,0x00,0x00,0x01,0x00,
	0x00,0x00,0x02,0x00,0x00,0x00,0x01,0x00,
	0x00,0xf0,0x03,0x00,0x00,0x80,0x0f,0x00,
	0x00,0x1e,0x06,0x00,0x00,0xc0,0x78,0x00,
	0x80,0x03,0x0c,0x00,0x00,0x60,0xc0,0x01,
	0xc0,0x00,0x18,0x00,0x00,0x30,0x00,0x03,
	0x60,0x00,0x30,0x00,0x00,0x18,0x00,0x06,
	0x30,0x00,0x60,0x00,0x00,0x0c,0x00,0x0c,
	0x18,0x00,0xc0,0x00,0x00,0x06,0x00,0x18,
	0x0c,0x00,0x80,0x01,0x00,0x03,0x00,0x30,
	0x04,0x00,0x00,0x03,0x80,0x01,0x00,0x20,
	0x06,0x00,0x00,0x06,0xc0,0x00,0x00,0x60,
	0x02,0x00,0x00,0x0c,0x60,0x00,0x00,0x40,
	0x02,0x00,0x00,0x18,0x30,0x00,0x00,0x40,
	0x03,0x00,0x00,0x30,0x18,0x00,0x00,0xc0,
	0x01,0x00,0x00,0x60,0x0c,0x00,0x00,0x80,
	0x01,0x00,0x00,0xc0,0x06,0x00,0x00,0x80,
	0x01,0x00,0x00,0x80,0x03,0x00,0x00,0x80,
	0x01,0x00,0x00,0x80,0x03,0x00,0x00,0x80,
	0x01,0x00,0x00,0xc0,0x06,0x00,0x00,0x80,
	0x01,0x00,0x00,0x60,0x0c,0x00,0x00,0x80,
	0x03,0x00,0x00,0x30,0x18,0x00,0x00,0xc0,
	0x02,0x00,0x00,0x18,0x30,0x00,0x00,0x40,
	0x02,0x00,0x00,0x0c,0x60,0x00,0x00,0x40,
	0x06,0x00,0x00,0x06,0xc0,0x00,0x00,0x60,
	0x04,0x00,0x00,0x03,0x80,0x01,0x00,0x20,
	0x0c,0x00,0x80,0x01,0x00,0x03,0x00,0x30,
	0x18,0x00,0xc0,0x00,0x00,0x06,0x00,0x18,
	0x30,0x00,0x60,0x00,0x00,0x0c,0x00,0x0c,
	0x60,0x00,0x30,0x00,0x00,0x18,0x00,0x06,
	0xc0,0x00,0x18,0x00,0x00,0x30,0x00,0x03,
	0x80,0x03,0x0c,0x00,0x00,0x60,0xc0,0x01,
	0x00,0x1e,0x06,0x00,0x00,0xc0,0x78,0x00,
	0x00,0xf0,0x03,0x00,0x00,0x80,0x0f,0x00,
	0x00,0x00,0x02,0x00,0x00,0x00,0x01,0x00,
	0x00,0x00,0x02,0x00,0x00,0x00,0x01,0x00,
	0x00,0x00,0x02,0x00,0x00,0x00,0x01,0x00,
	0x00,0x00,0x06,0x00,0x00,0x80,0x01,0x00,
	0x00,0x00,0x04,0x00,0x00,0x80,0x00,0x00,
	0x00,0x00,0x04,0x00,0x00,0x80,0x00,0x00,
	0x00,0x00,0x0c,0x00,0x00,0xc0,0x00,0x00,
	0x00,0x00,0x08,0x00,0x00,0x40,0x00,0x00,
	0x00,0x00,0x18,0x00,0x00,0x60,0x00,0x00,
	0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,
	0x00,0x00,0x60,0x00,0x00,0x18,0x00,0x00,
	0x00,0x00,0xc0,0x00,0x00,0x0c,0x00,0x00,
	0x00,0x00,0x80,0x01,0x00,0x06,0x00,0x00,
	0x00,0x00,0x00,0x07,0x80,0x03,0x00,0x00,
	0x00,0x00,0x00,0x3c,0xf0,0x00,0x00,0x00,
	0x00,0x00,0x00,0xe0,0x1f,0x00,0x00,0x00
};

const uint8_t GFX_R[] =  {
		0x00,0x00,0x00,0x00,
		0x01,0x00,0x00,0x00,
		0x03,0x00,0x00,0x00,
		0x07,0x00,0x00,0x00,
		0x0f,0x00,0x00,0x00,
		0x1f,0x00,0x00,0x00,
		0x3f,0x00,0x00,0x00,
		0x7f,0x00,0x00,0x00,
		0xff,0x00,0x00,0x00,
		0xff,0x01,0x00,0x00,
		0xff,0x03,0x00,0x00,
		0xff,0x07,0x00,0x00,
		0xff,0x0f,0x00,0x00,
		0xff,0x1f,0x00,0x00,
		0xff,0x3f,0x00,0x00,
		0xff,0x7f,0x00,0x00,
		0xff,0xff,0x00,0x00,
		0xff,0xff,0x01,0x00,
		0xff,0xff,0x03,0x00,
		0xff,0xff,0x07,0x00,
		0xff,0xff,0x0f,0x00,
		0xff,0xff,0x1f,0x00,
		0xff,0xff,0x3f,0x00,
		0xff,0xff,0x7f,0x00,
		0xff,0xff,0xff,0x00,
		0xff,0xff,0xff,0x01,
		0xff,0xff,0xff,0x03,
		0xff,0xff,0xff,0x07,
		0xff,0xff,0xff,0x0f,
		0xff,0xff,0xff,0x1f,
		0xff,0xff,0xff,0x3f,
		0xff,0xff,0xff,0x7f
};

const uint8_t GFX_L[] =  {
		0xff,0xff,0xff,0x7f,
		0xff,0xff,0xff,0x3f,
		0xff,0xff,0xff,0x1f,
		0xff,0xff,0xff,0x0f,
		0xff,0xff,0xff,0x07,
		0xff,0xff,0xff,0x03,
		0xff,0xff,0xff,0x01,
		0xff,0xff,0xff,0x00,
		0xff,0xff,0x7f,0x00,
		0xff,0xff,0x3f,0x00,
		0xff,0xff,0x1f,0x00,
		0xff,0xff,0x0f,0x00,
		0xff,0xff,0x07,0x00,
		0xff,0xff,0x03,0x00,
		0xff,0xff,0x01,0x00,
		0xff,0xff,0x00,0x00,
		0xff,0x7f,0x00,0x00,
		0xff,0x3f,0x00,0x00,
		0xff,0x1f,0x00,0x00,
		0xff,0x0f,0x00,0x00,
		0xff,0x07,0x00,0x00,
		0xff,0x03,0x00,0x00,
		0xff,0x01,0x00,0x00,
		0xff,0x00,0x00,0x00,
		0x7f,0x00,0x00,0x00,
		0x3f,0x00,0x00,0x00,
		0x1f,0x00,0x00,0x00,
		0x0f,0x00,0x00,0x00,
		0x07,0x00,0x00,0x00,
		0x03,0x00,0x00,0x00,
		0x01,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00
};


