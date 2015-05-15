//
//  AddressTypes.cpp
//  MKPi
//
//  Created by Maurus Kühne on 26.04.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//


#include <stdint.h>
#include <stdio.h>
#include "AddressTypes.h"
#include "Errors.h"
#include "System.h"
#include <cstdint>
#include <stdlib.h>

const uint32_t ARM_BUS_LOCATION = 0x40000000;

const uint32_t SDRAM_SIZE = 1024* 1024 * 256;

namespace HIL {
  namespace Memory {
    
    //Bus Address
    
    BusAddress::operator PhysicalAddress() {
      PhysicalAddress pAddr;
      
      if (address >= 0xC0000000 && address <= (0xC0000000 + SDRAM_SIZE)) {
        pAddr.address = address - 0xC0000000;
      } else if (address >= 0x7E000000 && address <= 0xDC000000) {
        pAddr.address = address - 0x5E000000;
      } else {
        char txt[80];
        sprintf(txt, "could not convert from bus address to physical address -> %#010x", address);
        fatalError(txt);
      }
      
      return pAddr;
    }
    
    BusAddress operator+(BusAddress lhs, const BusAddress& rhs) {
      lhs += rhs;
      return lhs;
    }
    
    BusAddress& BusAddress::operator+=(const HIL::Memory::BusAddress& rhs) {
      address += rhs.address;
      return *this;
    }
    
    BusAddress operator-(BusAddress lhs, const BusAddress& rhs) {
      lhs -= rhs;
      return lhs;
    }
    
    BusAddress& BusAddress::operator-=(const HIL::Memory::BusAddress& rhs) {
      address -= rhs.address;
      return *this;
    }
    
    //Physical Address
    
    PhysicalAddress::operator BusAddress() {
      BusAddress bAddr;
      
      if (address >= 0x00000000 && address <= SDRAM_SIZE) {
        bAddr.address = 0xC0000000 + address;
      }else if (address >= 0x20000000 && address <= 0x20FFFFFF) {
        bAddr.address = address + 0x5E000000;
      } else {
        char txt[80];
        sprintf(txt, "could not convert from physical address to bus address -> %#010x", address);
        fatalError(txt);
      }
      
      return bAddr;
    }
    
    PhysicalAddress operator+(PhysicalAddress lhs, const PhysicalAddress& rhs) {
      lhs += rhs;
      return lhs;
    }
    
    PhysicalAddress& PhysicalAddress::operator+=(const PhysicalAddress& rhs) {
      address += rhs.address;
      return *this;
    }
    
    PhysicalAddress operator-(PhysicalAddress lhs, const PhysicalAddress& rhs) {
      lhs -= rhs;
      return lhs;
    }
    
    PhysicalAddress& PhysicalAddress::operator-=(const PhysicalAddress& rhs) {
      address -= rhs.address;
      return *this;
    }

    
    // Virtual Address
    
    VirtualAddress operator+(VirtualAddress lhs, const VirtualAddress& rhs) {
      lhs += rhs;
      return lhs;
    }
    
    VirtualAddress& VirtualAddress::operator+=(const VirtualAddress& rhs) {
      address += rhs.address;
      return *this;
    }
    
    VirtualAddress operator-(VirtualAddress lhs, const VirtualAddress& rhs) {
      lhs -= rhs;
      return lhs;
    }
    
    VirtualAddress& VirtualAddress::operator-=(const VirtualAddress& rhs) {
      address -= rhs.address;
      return *this;
    }
    
    
  }
}
    