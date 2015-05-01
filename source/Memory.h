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
  };
}

#endif /* defined(__MKPi__Memory__) */
