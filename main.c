/** Motorola 6816 Emulator **/

#ifndef DEBUG
#define DEBUG(...) printf()
#endif

#include "CPU-Registers.h"

void printError(int errorCode) {
  switch (errorCode)
  {
  case CPU_OPCODE_ERROR:
    printf(CPU_OPCODE_MSG);
    break;
  
  default: printf("Unknown Error Occurred");
    break;
  }
}

int main(int argc, char *argv[]) {
  registers pReg;
  
  
  
  return 0;
}