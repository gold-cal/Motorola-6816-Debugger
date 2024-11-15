#ifndef CPU_REG
#define CPU_REG

/*** Include Files ***/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/*** Defines ***/
#define CPU_OPCODE_ERROR -1
#define CPU_OPCODE_MSG "Invalid Opcode"

/*** 6816 CPU registers ***/
typedef struct CPU_registers{
  uint8_t a;
  uint8_t b;
  uint32_t ix;
  uint32_t iy;
  uint32_t iz;
  uint32_t sp;
  uint32_t pc;
  uint16_t h;
  uint16_t i;
  uint16_t ccr;
  uint64_t am;
  uint8_t xmsk;
  uint8_t ymsk;
  uint16_t flags;
  uint8_t ram[0xFFFFF];
}registers;

#endif //CPU_REG