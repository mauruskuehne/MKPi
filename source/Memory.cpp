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
    
    BusAddress::operator PhysicalAddress() {
      PhysicalAddress pAddr;
      
      if (address >= 0xC0000000 && address <= (0xC0000000 + SDRAM_SIZE)) {
        pAddr.address = address - 0xC0000000;
      } else if (address >= 0x7E000000 && address <= 0xDC000000) {
        pAddr.address = address - 0x5E000000;
      } else {
        fatalError("could not convert from bus address to physical address");
      }
      
      return pAddr;
    }
    
    //physikalische Addresse zu BusAddresse
    PhysicalAddress::operator BusAddress() {
      BusAddress bAddr;

      if (address >= 0x00000000 && address <= SDRAM_SIZE) {
        bAddr.address = 0xC0000000 + address;
      }else if (address >= 0x20000000 && address <= 0x20FFFFFF) {
        bAddr.address = address + 0x5E000000;
      } else {
        fatalError("could not convert from physical address to bus address");
      }
      
      return bAddr;
    }
    
    volatile void MemoryBarrier() {
      asm volatile( "mcr p15, 0, ip, c7, c5, 0" );
      asm volatile( "mcr p15, 0, ip, c7, c5, 6" );
      asm volatile( "mcr p15, 0, ip, c7, c10, 4" );
      asm volatile( "mcr p15, 0, ip, c7, c5, 4" );
    }
    
  }
}
