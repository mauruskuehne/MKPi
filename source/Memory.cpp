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
      namespace GPIO {
        const struct BusAddress BASE =    BusAddress { 0x7E200000 };
        const struct BusAddress GPFSEL0 = BASE;
        const struct BusAddress GPFSEL1 = BASE + BusAddress { 0x4 };
        const struct BusAddress GPFSEL2 = BASE + BusAddress { 0x8 };
        const struct BusAddress GPFSEL3 = BASE + BusAddress { 0xC };
        const struct BusAddress GPFSEL4 = BASE + BusAddress { 0x10 };
        const struct BusAddress GPFSEL5 = BASE + BusAddress { 0x14 };
        const struct BusAddress GPSET0 = BASE + BusAddress { 0x1C };
        const struct BusAddress GPSET1 = BASE + BusAddress { 0x20 };
        const struct BusAddress GPCLR0 = BASE + BusAddress { 0x28 };
        const struct BusAddress GPCLR1 = BASE + BusAddress { 0x2C };
        const struct BusAddress GPLEV0 = BASE + BusAddress { 0x34 };
        const struct BusAddress GPLEV1 = BASE + BusAddress { 0x38 };
        const struct BusAddress GPEDS0 = BASE + BusAddress { 0x40 };
        const struct BusAddress GPEDS1 = BASE + BusAddress { 0x44 };
        const struct BusAddress GPREN0 = BASE + BusAddress { 0x4C };
        const struct BusAddress GPREN1 = BASE + BusAddress { 0x50 };
        const struct BusAddress GPFEN0 = BASE + BusAddress { 0x58 };
        const struct BusAddress GPFEN1 = BASE + BusAddress { 0x5C };
        const struct BusAddress GPHEN0 = BASE + BusAddress { 0x64 };
        const struct BusAddress GPHEN1 = BASE + BusAddress { 0x68 };
        const struct BusAddress GPLEN0 = BASE + BusAddress { 0x70 };
        const struct BusAddress GPLEN1 = BASE + BusAddress { 0x74 };
        const struct BusAddress GPAREN0 = BASE + BusAddress { 0x7C };
        const struct BusAddress GPAREN1 = BASE + BusAddress { 0x80 };
        const struct BusAddress GPAFEN0 = BASE + BusAddress { 0x88 };
        const struct BusAddress GPAFEN1 = BASE + BusAddress { 0x8C };
        const struct BusAddress GPPUD = BASE + BusAddress { 0x94 };
        const struct BusAddress GPPUDCLK0 = BASE + BusAddress { 0x98 };
        const struct BusAddress GPPUDCLK1 = BASE + BusAddress { 0x9C };
      }
      namespace UART {
        const struct BusAddress BASE =    BusAddress { .address = 0x7E201000 };
        const struct BusAddress DR =      BASE;
        const struct BusAddress RSRECR =  BASE + BusAddress{0x4};
        const struct BusAddress FR =      BASE + BusAddress{0x18};
        const struct BusAddress ILPR =    BASE + BusAddress{0x20};
        const struct BusAddress IBRD =    BASE + BusAddress{0x24};
        const struct BusAddress FBRD =    BASE + BusAddress{0x28};
        const struct BusAddress LCRH =    BASE + BusAddress{0x2c};
        const struct BusAddress CR =      BASE + BusAddress{ .address = 0x30};
        const struct BusAddress IFLS =    BASE + BusAddress{0x34};
        const struct BusAddress IMSC =    BASE + BusAddress{0x38};
        const struct BusAddress RIS =     BASE + BusAddress{0x3c};
        const struct BusAddress MIS =     BASE + BusAddress{0x40};
        const struct BusAddress ICR =     BASE + BusAddress{0x44};
        const struct BusAddress DMACR =   BASE + BusAddress{0x48};
        const struct BusAddress ITCR =    BASE + BusAddress{0x80};
        const struct BusAddress ITIP =    BASE + BusAddress{0x84};
        const struct BusAddress ITOP =    BASE + BusAddress{0x88};
        const struct BusAddress TDR =     BASE + BusAddress{0x8c};
      };
    };
    
  }
}
