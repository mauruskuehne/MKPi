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
      
      BusAddress& operator+=(const BusAddress& rhs);
      BusAddress& operator-=(const BusAddress& rhs);
    };
    
    BusAddress operator+(BusAddress lhs, const BusAddress& rhs);
    BusAddress operator-(BusAddress lhs, const BusAddress& rhs);
    
    struct PhysicalAddress {
      uint32_t address;
      explicit operator BusAddress();
      
      PhysicalAddress& operator+=(const PhysicalAddress& rhs);
      PhysicalAddress& operator-=(const PhysicalAddress& rhs);
    };
    
    PhysicalAddress operator+(PhysicalAddress lhs, const PhysicalAddress& rhs);
    PhysicalAddress operator-(PhysicalAddress lhs, const PhysicalAddress& rhs);
    
    struct VirtualAddress {
      uint32_t address;
      
      VirtualAddress& operator+=(const VirtualAddress& rhs);
      VirtualAddress& operator-=(const VirtualAddress& rhs);
    };
    
    VirtualAddress operator+(VirtualAddress lhs, const VirtualAddress& rhs);
    VirtualAddress operator-(VirtualAddress lhs, const VirtualAddress& rhs);
    
    
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
        extern BusAddress BASE;
        extern BusAddress DR;
        extern BusAddress RSRECR;
        extern BusAddress FR;
        extern BusAddress ILPR;
        extern BusAddress IBRD;
        extern BusAddress FBRD;
        extern BusAddress LCRH;
        extern BusAddress CR;
        extern BusAddress IFLS;
        extern BusAddress IMSC;
        extern BusAddress RIS;
        extern BusAddress MIS;
        extern BusAddress ICR;
        extern BusAddress DMACR;
        extern BusAddress ITCR;
        extern BusAddress ITIP;
        extern BusAddress ITOP;
        extern BusAddress TDR;
      };
    };
  };
}

#endif /* defined(__MKPi__Memory__) */
