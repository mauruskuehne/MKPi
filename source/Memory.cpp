//
//  Memory.cpp
//  MKPi
//
//  Created by Maurus Kühne on 06.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "Memory.h"

const uint32_t ARM_BUS_LOCATION = 0x40000000;

namespace HIL {
  
  
  namespace Memory {
    
    volatile void MemoryBarrier() {
      asm volatile( "mcr p15, 0, ip, c7, c5, 0" );
      asm volatile( "mcr p15, 0, ip, c7, c5, 6" );
      asm volatile( "mcr p15, 0, ip, c7, c10, 4" );
      asm volatile( "mcr p15, 0, ip, c7, c5, 4" );
    }
    
    volatile uint32_t PhysicalToVirtualAddress( uint32_t physicalAddress) {
      return physicalAddress + 0x80000000;
    }
    
    volatile uint32_t PhysicalToBusAddress( uint32_t p ) {
      return (uint32_t)(p + ARM_BUS_LOCATION );
    }
    
    volatile uint32_t BusToPhysicalAddress( uint32_t p ) {
      if ( p > ARM_BUS_LOCATION )
        return (uint32_t)(p - ARM_BUS_LOCATION );
      return (uint32_t)p;
    }
    
  }
}
