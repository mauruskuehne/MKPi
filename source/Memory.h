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
    
    extern "C" volatile void PUT32 ( uint32_t, uint32_t );
    extern "C" volatile unsigned int GET32 ( uint32_t );
    
    
    namespace Locations {
      namespace UART {
        static BusAddress BASE =    BusAddress { 0x7E201000 };
        static BusAddress DR =      BASE;
        static BusAddress RSRECR =  BASE + BusAddress{0x4};
        static BusAddress FR =      BASE + BusAddress{0x18};
        static BusAddress ILPR =    BASE + BusAddress{0x20};
        static BusAddress IBRD =    BASE + BusAddress{0x24};
        static BusAddress FBRD =    BASE + BusAddress{0x28};
        static BusAddress LCRH =    BASE + BusAddress{0x2c};
        static BusAddress CR =      BASE + BusAddress{0x30};
        static BusAddress IFLS =    BASE + BusAddress{0x34};
        static BusAddress IMSC =    BASE + BusAddress{0x38};
        static BusAddress RIS =     BASE + BusAddress{0x3c};
        static BusAddress MIS =     BASE + BusAddress{0x40};
        static BusAddress ICR =     BASE + BusAddress{0x44};
        static BusAddress DMACR =   BASE + BusAddress{0x48};
        static BusAddress ITCR =    BASE + BusAddress{0x80};
        static BusAddress ITIP =    BASE + BusAddress{0x84};
        static BusAddress ITOP =    BASE + BusAddress{0x88};
        static BusAddress TDR =     BASE + BusAddress{0x8c};
      };
    };
    
    
    enum UartMemory {
      // The GPIO registers base address.
      
      PERIPHERAL_START = 0x20000000,
      
      GPIO_OFFSET = PERIPHERAL_START + 0x00200000,
      
      // The offsets for reach register.
      
      // Controls actuation of pull up/down to ALL GPIO pins.
      GPPUD = (GPIO_OFFSET + 0x94),
      
      // Controls actuation of pull up/down for specific GPIO pin.
      GPPUDCLK0 = (GPIO_OFFSET + 0x98),
      
      // The base address for UART.
      UART0_OFFSET = GPIO_OFFSET + 0x00001000,
      
      // The offsets for reach register for the UART.
      UART0_DR     = (UART0_OFFSET + 0x00),
      UART0_RSRECR = (UART0_OFFSET + 0x04),
      UART0_FR     = (UART0_OFFSET + 0x18),
      UART0_ILPR   = (UART0_OFFSET + 0x20),
      UART0_IBRD   = (UART0_OFFSET + 0x24),
      UART0_FBRD   = (UART0_OFFSET + 0x28),
      UART0_LCRH   = (UART0_OFFSET + 0x2C),
      UART0_CR     = (UART0_OFFSET + 0x30),
      UART0_IFLS   = (UART0_OFFSET + 0x34),
      UART0_IMSC   = (UART0_OFFSET + 0x38),
      UART0_RIS    = (UART0_OFFSET + 0x3C),
      UART0_MIS    = (UART0_OFFSET + 0x40),
      UART0_ICR    = (UART0_OFFSET + 0x44),
      UART0_DMACR  = (UART0_OFFSET + 0x48),
      UART0_ITCR   = (UART0_OFFSET + 0x80),
      UART0_ITIP   = (UART0_OFFSET + 0x84),
      UART0_ITOP   = (UART0_OFFSET + 0x88),
      UART0_TDR    = (UART0_OFFSET + 0x8C),
    };
  };
}

#endif /* defined(__MKPi__Memory__) */
