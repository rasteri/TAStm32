#ifndef __N64__H
#define __N64__H

#include <stdint.h>

typedef struct __attribute__((packed))
{
	unsigned int right : 1; // low bit of 1st byte
	unsigned int left : 1;
	unsigned int down : 1;
	unsigned int up : 1;
	unsigned int start : 1;
	unsigned int z : 1;
	unsigned int b : 1;
	unsigned int a : 1; // high bit of 1st byte

	unsigned int c_right : 1;
	unsigned int c_left : 1;
	unsigned int c_down : 1;
	unsigned int c_up : 1;
	unsigned int r : 1;
    unsigned int l : 1;
    unsigned int dummy1 : 1;
    unsigned int dummy2 : 1;

    char x_axis;

    char y_axis;

} N64ControllerData;

typedef struct __attribute__((packed))
{
	unsigned int a : 1;
	unsigned int b : 1;
	unsigned int x : 1; // 1 bit wide
	unsigned int y : 1;
	unsigned int start : 1;
	unsigned int beginning_zeros : 3;

    unsigned int d_left : 1;
    unsigned int d_right : 1;
    unsigned int d_down : 1;
    unsigned int d_up : 1;
    unsigned int z : 1;
    unsigned int r : 1;
    unsigned int l : 1;
    unsigned int beginning_one : 1;

    uint8_t a_x_axis;
    uint8_t a_y_axis;
    uint8_t c_x_axis;
    uint8_t c_y_axis;
    uint8_t l_trigger;
    uint8_t r_trigger;

} GCControllerData; // all bits are in the correct order... except for the analog

uint32_t GCN64_ReadCommand(uint8_t player);
void N64_SendIdentity(uint8_t player);
void GC_SendIdentity(uint8_t player);
void GC_SendOrigin(uint8_t player);
void N64_SendRunData(uint8_t player, N64ControllerData data);
void N64_SendControllerData(uint8_t player, unsigned long data);
void GC_SendRunData(uint8_t player, GCControllerData gcdata);
void GC_SendControllerData(uint8_t player, uint64_t data);

#endif
