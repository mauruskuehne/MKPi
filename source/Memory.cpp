//
//  Memory.cpp
//  MKPi
//
//  Created by Maurus Kühne on 06.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "Memory.h"
#include "Errors.h"

const uint32_t ARM_BUS_LOCATION = 0x40000000;

const uint32_t SDRAM_SIZE = 1024* 1024 * 256;

namespace HIL {
  
  
  namespace Memory {    
    volatile void MemoryBarrier() {
      asm volatile( "mcr p15, 0, ip, c7, c5, 0" );
      asm volatile( "mcr p15, 0, ip, c7, c5, 6" );
      asm volatile( "mcr p15, 0, ip, c7, c10, 4" );
      asm volatile( "mcr p15, 0, ip, c7, c5, 4" );
    }
  }
}
