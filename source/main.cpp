//
//  main.cpp
//  MKPi
//
//  Created by Maurus Kühne on 03.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "main.h"
#include "Memory.h"
#include "Framebuffer.h"
#include "UART.h"
#include <cstdint>
#include <stdlib.h>



#define GPFSEL1 0x20200004
#define GPSET0  0x2020001C
#define GPCLR0  0x20200028
#define GPPUD       0x20200094
#define GPPUDCLK0   0x20200098

using namespace HIL;


extern "C" void dummy ( unsigned int );

void blink() {
  unsigned int ra;
  Memory::PUT32(GPSET0,1<<16);
  for(ra=0;ra<0x100000;ra++) dummy(ra);
  Memory::PUT32(GPCLR0,1<<16);
  for(ra=0;ra<0x100000;ra++) dummy(ra);
}

void blink(int speed) {
  unsigned int ra;
  Memory::PUT32(GPSET0,1<<16);
  for(ra=0;ra<speed;ra++) dummy(ra);
  Memory::PUT32(GPCLR0,1<<16);
  for(ra=0;ra<speed;ra++) dummy(ra);
}



volatile bool interruptExecuted = false;

int main() {
  unsigned int ra;
  
  ra=Memory::GET32(GPFSEL1);
  ra&=~(7<<18);
  ra|=1<<18;
  Memory::PUT32(GPFSEL1,ra);
  
  UART* uart = UART::instance();
  
  /*
  Framebuffer* buffer;
  
  buffer->initialize();*/
  /*
  blink();
  
  interruptExecuted = false;
  
  blink();
  asm volatile( "SWI #0x00000A" );
  blink();*/
  
  
  ra=0;
  
  uart->sendText("Hallo Welt", 10);
  
  uart->sendInfiniteLoop();
  
  
  while (!interruptExecuted) {
    dummy(0);
  }
  /*
  while(1)
  {
    PUT32(GPSET0,1<<16);
    for(ra=0;ra<0x100000;ra++) dummy(ra);
    PUT32(GPCLR0,1<<16);
    for(ra=0;ra<0x100000;ra++) dummy(ra);
  }*/
  
  return 0;
}

extern "C" void svc_handler( uint32_t value ) {
  
  unsigned int ra;
  for(int i = 0; i < value; i++)
  {
    Memory::PUT32(GPSET0,1<<16);
    for(ra=0;ra<0x100000;ra++) dummy(ra);
    Memory::PUT32(GPCLR0,1<<16);
    for(ra=0;ra<0x100000;ra++) dummy(ra);
  }
  interruptExecuted = true;
}

extern "C" void irq_handler( void ) {
  
  unsigned int ra;
  for(int i = 0; i < 10; i++)
  {
    Memory::PUT32(GPSET0,1<<16);
    for(ra=0;ra<0x100000;ra++) dummy(ra);
    Memory::PUT32(GPCLR0,1<<16);
    for(ra=0;ra<0x100000;ra++) dummy(ra);
  }
  interruptExecuted = true;
}