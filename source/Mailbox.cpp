//
//  Mailbox.cpp
//  MKPi
//
//  Created by Maurus Kühne on 06.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "Mailbox.h"

extern void blink(int speed);
namespace HIL {
  extern "C" void PUT32 ( unsigned int, unsigned int );
  extern "C" unsigned int GET32 ( unsigned int );

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
        ra=GET32(mailbox+0x18);
        if((ra&0x40000000)==0) break;
      }
      
      Memory::MemoryBarrier();
      ra=GET32(mailbox+0x00);
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
      if((GET32(mailbox+0x18)&0x80000000)==0) break;
    }
    Memory::MemoryBarrier();
    PUT32(mailbox+0x20,value + channel);
    return;
  }
}