//
//  main.cpp
//  MKPi
//
//  Created by Maurus Kühne on 03.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "main.h"
#include <cstdint>
#include <stdlib.h>
#include "ArrayList.h"
#include "System.h"
#include <string.h>
#include "HIL.h"

using namespace HIL;
using namespace HIL::Memory;


extern "C" void (*__init_array_start)();
extern "C" void (*__init_array_end)();



extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

extern uint32_t __data_rom_start__;
extern uint32_t __data_start__;
extern uint32_t __data_end__;

extern uint8_t* __stack;
extern uint8_t* __heap_start;
extern uint8_t* __kernel_start;
extern uint8_t* __kernel_end;
volatile bool interruptExecuted = false;

void print_init() {
  printf("\nSystem Parameters: \n");
  printf(" - git revision: \t %s\n", VERSION);
  printf(" - kernel start addr: \t 0x%08x\n", &__kernel_start);
  printf(" - kernel end addr: \t 0x%08x\n", &__kernel_end);
  printf(" - kernel size: \t %i KB\n", ((&__kernel_end - &__kernel_start) * 4) / 1024); // *4 -> we are counting 32Bit addresses, /1024 for kilobytes
  printf(" - Stack origin: \t 0x%08x\n", &__stack);
  printf(" - heap origin: \t 0x%08x\n", &__heap_start);
  printf(" - init array start: \t 0x%08x\n", &__init_array_start);
  printf(" - init array end: \t 0x%08x\n", &__init_array_end);
  printf(" - nr of init funcs: \t %i\n", (&__init_array_end - &__init_array_start) );

}

int main() {
  
  //call initializer methods for static variables
  for (uint32_t* address =((uint32_t*)&__init_array_start); address < (uint32_t*)&__init_array_end; address++) {
    uint32_t addrToCall = *address;
    void (*funcPtr)();
    funcPtr = (void(*)())addrToCall;
    (*funcPtr)();
  }
  
  UART* uart = UART::instance();
  ActLed* led = ActLed::instance();
  
  printf("\n\nMKPi (rev %s)\n", VERSION);
  
  print_init();
  
  led->blink();
  led->blink();
  
  int byteCounter = 0;
  while (true) {
    char buffer[1024];
    printf("\n> ");
    scanf("%s", &buffer);
    
    if(strcasecmp("KILLPI", buffer) == 0) {
      printf("self destruct\n");
      led->blink();
      rebootSystem();
    } else if (strcasecmp("TESTPI", buffer) == 0) {
      printf("hello world");
    } else if(strcasecmp("FAILPI", buffer) == 0) {
      char txt[80];
      sprintf(txt, "could not convert from bus address to physical address -> %#010x", 0x400);
      fatalError(txt);
    } else {
      printf("didn't recognize command");
    }
  }
  
  return 0;
}

extern "C" void svc_handler( uint32_t value ) {
  
  ActLed* led = ActLed::instance();
  unsigned int ra;
  for(int i = 0; i < value; i++)
  {
    led->blink();
  }
  interruptExecuted = true;
}

extern "C" void irq_handler( void ) {
  
  ActLed* led = ActLed::instance();
  unsigned int ra;
  for(int i = 0; i < 10; i++)
  {
    led->blink();
  }
  interruptExecuted = true;
}