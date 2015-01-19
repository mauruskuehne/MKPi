//
//  UART.cpp
//  MKPi
//
//  Created by Maurus Kühne on 19.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "UART.h"
#include <stdlib.h>

using namespace HIL;


extern "C" void dummy ( unsigned int );

#define GPFSEL1 0x20200004
#define GPSET0  0x2020001C
#define GPCLR0  0x20200028
#define GPPUD       0x20200094
#define GPPUDCLK0   0x20200098

#define AUX_IRQ         0x20215000
#define AUX_ENABLES     0x20215004
#define AUX_MU_IO_REG   0x20215040
#define AUX_MU_IER_REG  0x20215044
#define AUX_MU_IIR_REG  0x20215048
#define AUX_MU_LCR_REG  0x2021504C
#define AUX_MU_MCR_REG  0x20215050
#define AUX_MU_LSR_REG  0x20215054
#define AUX_MU_MSR_REG  0x20215058
#define AUX_MU_SCRATCH  0x2021505C
#define AUX_MU_CNTL_REG 0x20215060
#define AUX_MU_STAT_REG 0x20215064
#define AUX_MU_BAUD_REG 0x20215068

namespace HIL {
  
  UART* UART::_instance;
  
  UART* UART::instance() {
    if (UART::_instance == nullptr) {
      UART uart;
      UART::_instance = &uart;
    }
    
    return UART::_instance;
  }
  
  UART::UART() {
    
    uint32_t ra;
    Memory::PUT32(AUX_ENABLES,1);       // Enable Auxiliary
    Memory::PUT32(AUX_MU_IER_REG,0);    // Mini UART Interrupt Enable
    Memory::PUT32(AUX_MU_CNTL_REG,0);   // Mini UART Extra Control
    Memory::PUT32(AUX_MU_LCR_REG,3);    // Mini UART Line Control
    Memory::PUT32(AUX_MU_MCR_REG,0);    // Mini UART Modem Control
    Memory::PUT32(AUX_MU_IER_REG,0);    // Mini UART Interrupt Enable
    Memory::PUT32(AUX_MU_IIR_REG,0xC6); // Mini UART Interrupt Identify
    Memory::PUT32(AUX_MU_BAUD_REG,270); // Mini UART Baudrate
    
    // GPIO Function Select 1
    ra=Memory::GET32(GPFSEL1);
    ra&=~(7<<12); //gpio14
    ra|=2<<12;    //alt5
    // GPIO Function Select 1
    Memory::PUT32(GPFSEL1,ra);
    
    //GPIO Pin Pull-up/down Enable
    Memory::PUT32(GPPUD,0);
    for(ra=0;ra<150;ra++) dummy(ra);
    
    // GPIO Pin Pull-up/down Enable Clock 0
    Memory::PUT32(GPPUDCLK0,(1<<14));
    for(ra=0;ra<150;ra++) dummy(ra);
    
    // GPIO Pin Pull-up/down Enable Clock 0
    Memory::PUT32(GPPUDCLK0,0);
    
    
    Memory::PUT32(AUX_MU_CNTL_REG,2); // Mini UART Extra Control
  }
  
  void UART::sendText(char* text, int length) {
    for(int i = 0; i < length; i++)
    {
      while(1)
      {
        if(Memory::GET32(AUX_MU_LSR_REG)&0x20) break;
      }
      Memory::PUT32(AUX_MU_IO_REG,text[i]);
    }
  }
  
  void UART::sendInfiniteLoop() {
    
    uint32_t ra = 0;
    while(1)
    {
      while(1)
      {
        
        if(Memory::GET32(AUX_MU_LSR_REG)&0x20) break;
      }
      Memory::PUT32(AUX_MU_IO_REG,0x30+(ra++&7));
    }
  }
  
}

