/*** CPU-Opcodes for the motorola 6816.
 * Filename: CPU-Opcodes.c
 * Created: 11/6/2024
 * Last Modified: 11/6/2024
***/

#include "CPU-Registers.h"
 
/*** Flag Modifiers 
** 11 10  9  8    7 6  5 4  3 2 1 0
**    INT    SM   S MV H EV N Z V C ***/
#define FLAG_CLEAR_ALL     0x00
#define FLAG_C 0x0001   // Carry flag
#define FLAG_V 0x0002   // Overflow Flag
#define FLAG_Z 0x0004   // Zero flag
#define FLAG_N 0x0008   // Negative flag
#define FLAG_EV 0x0010  // Extension bit overflow flag
#define FLAG_H 0x0020   // Half carry flag
#define FLAG_MV 0x0040  // Accumulator M overflow flag
#define FLAG_S 0x0080   // Stop enable
#define FLAG_SM 0x0100  // Saturate mode bit
#define FLAG_INT_0 0x0000 // Interupt priority mask 0
#define FLAG_INT_1 0x0200 // Mask 1
#define FLAG_INT_2 0x0400 // Mask 2
#define FLAG_INT_3 0x0600 // Mask 3
#define FLAG_INT_4 0x0800 // Mask 4
#define FLAG_INT_5 0x0A00 // Mask 5
#define FLAG_INT_6 0x0C00 // Mask 6
#define FLAG_INT_7 0x0E00 // Mask 7

void SetFlag(registers *pReg, uint32_t flag) {
  pReg->flags = pReg->flags | flag;
}

void ClearFlag(registers *pReg, uint32_t flag) {
  pReg->flags = ~(~pReg->flags | flag);
}

void CheckOverflow() {
  
}

void CheckNegative(uint32_t result, uint32_t shift) {
  
}

bool CheckHalfCarry(uint8_t parm1, uint8_t parm2) {
  uint8_t buf = 0;
  parm1 = parm1 | 0xF8;
  parm1 = parm1 ^ 0xF8;
  parm2 = parm2 | 0xF8;
  parm2 = parm2 ^ 0xF8;
  buf = parm1 + parm2;
  if (buf > 0x07) {
    return true;
  }
  return false;
}

/*** ABA: 370B - Add B to A and store in A ***/
void aba(registers *pReg) {
  uint16_t buf = 0;
  uint8_t xa = 0, xb = 0;
  buf = pReg->a + pReg->b;
  // Check carry flag
  if (buf > 0xFF) { // Set flag
    SetFlag(pReg, FLAG_C);
  } else { // Clear flag
    ClearFlag(pReg, FLAG_C);
  }
  // Check Overflow Flag (signed arithmatic only)
  // but no way to know if it signed or not, so
  // check anyway.
  if (buf > 0xFF){
    xa = buf ^ pReg->a;
    xb = buf ^ pReg->b;
    xa >> 0x07;
    xb >> 0x07;
    if (xa == xb) { 
      SetFlag(pReg, FLAG_V);
    } else {
      ClearFlag(pReg, FLAG_V);
    }
  }
  // check zero flag
  if (buf == 0x0000) {
    SetFlag(pReg, FLAG_Z);
  } else {
    ClearFlag(pReg, FLAG_Z);
  }
  // check negative flag (MSB = 1)
  if (buf > 0x007F && buf < 0x0100) {
    SetFlag(pReg, FLAG_N);
  } else {
    ClearFlag(pReg, FLAG_N);
  }
  // check half carry flag
  if (CheckHalfCarry(pReg->a, pReg->b)) {
    SetFlag(pReg, FLAG_H);
  } else {
    ClearFlag(pReg, FLAG_H);
  }
  pReg->a = buf;
  return;
}

/*** ABX: 374F - add B to X  
*** No flags changed            ***/
void abx(registers *pReg) {
  pReg->ix = pReg->ix + pReg->b;
  return;
}

/*** ABY: 375F - add B to Y ***/
void aby(registers *pReg) {
  pReg->iy = pReg->iy + pReg->b;
  return;
}

/*** ABZ: 376F - add B to Z ***/
void abz(registers *pReg) {
  pReg->iz = pReg->iz + pReg->b;
  return;
}

/*** ACE: 3722 - add E to AM(31:15) ***/
void ace(registers *pReg) {
  
}
/*** AIX: Add Immediate data to IX ***/
int aix(registers *pReg, uint16_t opcode) {
  uint16_t buf = 0;
  uint16_t mem = 0;
  pReg->pc++; // incrament pc to point to first data byte
  switch (opcode)
  {
  case 0x003C: // 1 byte of data
    mem = pReg->ram[pReg->pc]; // get data from ram
    buf = pReg->ix + mem; // add data to ix register
    break;
  case 0x373C: // 2 bytes of data
    mem = pReg->ram[pReg->pc]; // get first ram byte
    mem = mem << 8; // shift bits right 1 byte
    pReg->pc++; // incrament to next data byte
    mem = mem + pReg->ram[pReg->pc]; // get second ram byte
    buf = pReg->ix + mem;
    break;
  default: return -1;
    break;
  }
  pReg->pc++; // Inc. pc to Point to next instruction
  return 0;
}

/*** CPX: compare IX to memory - (IX - (M:M+1)) ***/
void cpx(registers *pReg, uint16_t opcode) {
  switch(opcode) {
    case 0x004C: break;
    case 0x005C: break;
    case 0x006C: break;
    case 0x174C: break;
    case 0x175C: break;
    case 0x176C: break;
    case 0x177C: break;
    case 0x377C: break;
    default: break;
  }
  return;
}