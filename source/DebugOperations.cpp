//
//  DebugOperations.cpp
//  MKPi
//
//  Created by Maurus Kühne on 19/05/15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "DebugOperations.h"
#include "UART.h"


extern uint32_t __ram_end;

using namespace HIL;

namespace System {
  namespace Diagnostics {
    
    
    void DebugOperations::dump_memory(uint32_t startAddress, uint32_t endAddress) {
      UART* uart = UART::instance();
      
      printf("*** begin memory dump ***");
      
      size_t size = endAddress - startAddress;
      
      printf("dump size: %i bytes", size);
      
      uart->sendBytes((uint8_t*)startAddress, size);
    }
    
    void DebugOperations::dump_memory() {
      dump_memory(0x0, __ram_end);
    }
    
    
  }
}