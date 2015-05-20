//
//  AddressTypes.h
//  MKPi
//
//  Created by Maurus Kühne on 01.05.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#ifndef MKPi_AddressTypes_h
#define MKPi_AddressTypes_h

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
    
  }
}

#endif
