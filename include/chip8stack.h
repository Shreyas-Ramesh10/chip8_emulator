#ifndef CHIP8STACK_H
#define CHIP8STACK_H

#include "config.h"

struct chip8;
struct chip8_stack
{
    unsigned short stack[CHIP8_TOTAL_STACK_DEPTH];

};

//val is value for the return address pushed on to the stack, which is the address of the next instruction to execute after the current one finishes, so PC + 2
void chip8_stack_push(struct chip8* chip8, unsigned short val);

//will decrement the stack pointer and return whatever was on that value on the stack to us.
unsigned short chip8_stack_pop(struct chip8* chip8);


#endif