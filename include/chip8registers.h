#ifndef CHIP8REGISTERS_H
#define CHIP8REGISTERS_H

#include "config.h"
struct chip8_registers
{
    unsigned char V[CHIP8_TOTAL_DATA_REGISTERS];
    unsigned short I; //Index register, used to store memory addresses for some instructions
    unsigned char delay_timer;
    unsigned char sound_timer;
    unsigned short PC; //Program counter, used to store the currently executing instruction's address
    unsigned char SP; //Stack pointer, used to point to the top of the stack
};

#endif