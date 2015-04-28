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
    
    
    extern "C" volatile void PUT32 ( uint32_t, uint32_t );
    extern "C" volatile unsigned int GET32 ( uint32_t );
    
    
    void write(BusAddress address, uint32_t value) {
      write((PhysicalAddress)address, value);
    }
    
    uint32_t read(BusAddress address) {
      return read((PhysicalAddress)address);
    }
    
    void write(PhysicalAddress address, uint32_t value) {
      PUT32(address.address, value);
    }
    
    uint32_t read(PhysicalAddress address) {
      return GET32(address.address);
    }
    
    uint32_t raw_read(uint32_t addr) {
      return GET32(addr);
    }
    
    void raw_write(uint32_t addr, uint32_t val) {
      PUT32(addr, val);
    }
    
    
    volatile void MemoryBarrier() {
      asm volatile( "mcr p15, 0, ip, c7, c5, 0" );
      asm volatile( "mcr p15, 0, ip, c7, c5, 6" );
      asm volatile( "mcr p15, 0, ip, c7, c10, 4" );
      asm volatile( "mcr p15, 0, ip, c7, c5, 4" );
    }
    
    namespace Locations {
      namespace UART {
        BusAddress BASE =    BusAddress { .address = 0x7E201000 };
        BusAddress DR =      BASE;
        BusAddress RSRECR =  BASE + BusAddress{0x4};
        BusAddress FR =      BASE + BusAddress{0x18};
        BusAddress ILPR =    BASE + BusAddress{0x20};
        BusAddress IBRD =    BASE + BusAddress{0x24};
        BusAddress FBRD =    BASE + BusAddress{0x28};
        BusAddress LCRH =    BASE + BusAddress{0x2c};
        BusAddress CR =      BASE + BusAddress{ .address = 0x30};
        BusAddress IFLS =    BASE + BusAddress{0x34};
        BusAddress IMSC =    BASE + BusAddress{0x38};
        BusAddress RIS =     BASE + BusAddress{0x3c};
        BusAddress MIS =     BASE + BusAddress{0x40};
        BusAddress ICR =     BASE + BusAddress{0x44};
        BusAddress DMACR =   BASE + BusAddress{0x48};
        BusAddress ITCR =    BASE + BusAddress{0x80};
        BusAddress ITIP =    BASE + BusAddress{0x84};
        BusAddress ITOP =    BASE + BusAddress{0x88};
        BusAddress TDR =     BASE + BusAddress{0x8c};
      };
    };
  }
}
