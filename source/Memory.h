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
#include "AddressTypes.h"

namespace HIL {
  namespace Memory {
    
    volatile void MemoryBarrier();
    
    void write(BusAddress address, uint32_t value);
    uint32_t read(BusAddress address);
    
    void write(PhysicalAddress address, uint32_t value);
    uint32_t read(PhysicalAddress address);
    
    void write(PhysicalAddress address, uint32_t value);
    uint32_t read(PhysicalAddress address);
    
    uint32_t raw_read(uint32_t addr);
    void raw_write(uint32_t addr, uint32_t val);
    
    namespace Locations {
      namespace UART {
        extern const struct BusAddress BASE;
        extern const struct BusAddress DR;
        extern const struct BusAddress RSRECR;
        extern const struct BusAddress FR;
        extern const struct BusAddress ILPR;
        extern const struct BusAddress IBRD;
        extern const struct BusAddress FBRD;
        extern const struct BusAddress LCRH;
        extern const struct BusAddress CR;
        extern const struct BusAddress IFLS;
        extern const struct BusAddress IMSC;
        extern const struct BusAddress RIS;
        extern const struct BusAddress MIS;
        extern const struct BusAddress ICR;
        extern const struct BusAddress DMACR;
        extern const struct BusAddress ITCR;
        extern const struct BusAddress ITIP;
        extern const struct BusAddress ITOP;
        extern const struct BusAddress TDR;
      };
    };
  };
}

#endif /* defined(__MKPi__Memory__) */
