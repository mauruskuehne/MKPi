//
//  Memory.h
//  MKPi
//
//  Created by Maurus Kühne on 06.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#ifndef __MKPi__Memory__
#define __MKPi__Memory__

#include <stdint.h>

namespace HIL {
  namespace Memory {
    
    struct PhysicalAddress;
    
    struct BusAddress {
      uint32_t address;
      explicit operator PhysicalAddress();
    };
    
    struct PhysicalAddress {
      uint32_t address;
      explicit operator BusAddress();
    };
    
    struct VirtualAddress {
      uint32_t address;
      
    };
    
    volatile void MemoryBarrier();
    
    extern "C" volatile void PUT32 ( uint32_t, uint32_t );
    extern "C" volatile unsigned int GET32 ( uint32_t );
  };
}

#endif /* defined(__MKPi__Memory__) */
