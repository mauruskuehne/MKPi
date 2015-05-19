//
//  DebugOperations.h
//  MKPi
//
//  Created by Maurus Kühne on 19/05/15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#ifndef __MKPi__DebugOperations__
#define __MKPi__DebugOperations__

#include <stdio.h>
#include <stdint.h>

namespace System {
  namespace Diagnostics {
    struct UartMemDumpPacketInfo {
      uint32_t dumpSize;
      uint32_t blockCount;
    };
    
    struct UartMemDumpDataBlock {
      uint32_t size;
      uint8_t content[];
    };
    
    class DebugOperations {
      
    public:
      static void dump_memory();
      static void dump_memory(uint32_t startAddress, uint32_t endAddress);
    };
  }
}

#endif /* defined(__MKPi__DebugOperations__) */
