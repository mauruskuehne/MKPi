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
    volatile void MemoryBarrier();
    volatile uint32_t PhysicalToVirtualAddress( uint32_t physicalAddress);
    volatile uint32_t PhysicalToBusAddress( uint32_t physicalAddress );
    volatile uint32_t BusToPhysicalAddress( uint32_t busAddress );
    
    extern "C" volatile void PUT32 ( uint32_t, uint32_t );
    extern "C" volatile unsigned int GET32 ( uint32_t );
  };
}

#endif /* defined(__MKPi__Memory__) */
