//
//  AddressTypes.cpp
//  MKPi
//
//  Created by Maurus Kühne on 26.04.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//


#include <stdint.h>
#include <stdio.h>
#include "Memory.h"
#include "Errors.h"
#include "StringFunctions.h"
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
        
        if(address == 0)
          fatalError("not working :<");
        
        const char* text ="could not convert from bus address to physical address -> ";
        uint32_t textlen = strlen(text) - 1;
        
        char number[10];
        tostr(address, number);
        char wholeText[10 + textlen];
        
        concat((char*)text, number, wholeText);
        
        fatalError(number);
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
        fatalError("could not convert from physical address to bus address");
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
    