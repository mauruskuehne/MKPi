//
//  CommandInterpreter.cpp
//  MKPi
//
//  Created by Maurus Kühne on 16.05.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "CommandInterpreter.h"
#include "System.h"
#include <stdlib.h>


extern "C" int get_stack_pointer();
extern uint8_t* __stack;
extern uint8_t* __heap_start;
extern uint8_t* __kernel_start;
extern uint8_t* __kernel_end;
extern uint32_t _current_heap_end;


char* ptrs[1000];

namespace System {
  void CommandInterpreter::interpretCommand(const char *input) {
    
    if(strcasecmp("KILLPI", input) == 0) {
      printf("self destruct\n");
      //led->blink();
      rebootSystem();
    } else if (strcasecmp("ALOCPI", input) == 0) {
      printf("allocating memory...\n");
      
      for (int i = 0; i < 1000; i++) {
        char* longText = new char[1024];
        
        
        
        ptrs[i] = longText;
      }
      
      printf("finished\n");
      
    } else if(strcasecmp("FREEMPI", input) == 0) {
      printf("freeing memory\n");
      for (int i = 0; i < 1000; i++) {
        delete ptrs[i];
      }
      printf("finished\n");
    } else if(strcasecmp("FAILPI", input) == 0) {
      char txt[80];
      sprintf(txt, "could not convert from bus address to physical address -> %#010x", 0x400);
      fatalError(txt);
    } else if(strcasecmp("HEAPPI", input) == 0) {
      
      printf(" - kernel start addr: \t 0x%08lx\n", (uint32_t)&__kernel_start);
      printf(" - kernel end addr: \t 0x%08lx\n", (uint32_t)&__kernel_end);
      printf(" - kernel size: \t %i KB\n", ((&__kernel_end - &__kernel_start) * 4) / 1024); // *4 -> we are counting 32Bit addresses, /1024 for kilobytes
      printf(" - stack origin: \t 0x%08lx\n", (uint32_t)&__stack);
      printf(" - current stack end: \t 0x%08lx\n", (uint32_t)get_stack_pointer());
      printf(" - heap origin: \t 0x%08lx\n", (uint32_t)&__heap_start);
      printf(" - current break: \t 0x%08lx\n", (uint32_t)_current_heap_end);
      
    } else {
      printf("didn't recognize command");
    }
  }
}