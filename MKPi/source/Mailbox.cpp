//
//  Mailbox.cpp
//  MKPi
//
//  Created by Maurus Kühne on 06.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "Mailbox.h"
#include "Memory.h"

using namespace HIL;
using namespace HIL::Memory;

extern void blink(int speed);
namespace HIL {
  
  uint32_t read32 (uint32_t nAddress)
  {
    return *(uint32_t *) nAddress;
  }
  
  void write32 (uint32_t nAddress, uint32_t nValue)
  {
    *(uint32_t *) nAddress = nValue;
  }
  
  
  Mailbox::Mailbox()
  {
  }
  
  uint32_t Mailbox::Read(uint32_t channel)
  {
    unsigned int ra;
    unsigned int mailbox;
    
    mailbox=0x2000B880;
    while(1)
    {
      while(1)
      {
        ra=Memory::read(PhysicalAddress{mailbox+0x18});
        if((ra&0x40000000)==0) break;
      }
      
      Memory::MemoryBarrier();
      ra=Memory::read(PhysicalAddress{mailbox+0x00});
      Memory::MemoryBarrier();
      
      if((ra&0xF)==channel) break;
    }
    return(ra);
  }
  
  void Mailbox::Write(uint32_t channel, uint32_t value)
  {
    unsigned int mailbox;
    
    mailbox=0x2000B880;
    while(1)
    {
      if((Memory::read(PhysicalAddress{mailbox+0x18})&0x80000000)==0) break;
    }
    Memory::MemoryBarrier();
    Memory::write(PhysicalAddress{mailbox+0x20},value + channel);
    return;
  }
}