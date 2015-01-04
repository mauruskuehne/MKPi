//
//  main.cpp
//  MKPi
//
//  Created by Maurus Kühne on 03.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "main.h"
#include <cstdint>

extern "C" void PUT32 ( unsigned int, unsigned int );
extern "C" unsigned int GET32 ( unsigned int );
extern "C" void dummy ( unsigned int );


#define GPFSEL1 0x20200004
#define GPSET0  0x2020001C
#define GPCLR0  0x20200028

void blink() {
  unsigned int ra;
  PUT32(GPSET0,1<<16);
  for(ra=0;ra<0x100000;ra++) dummy(ra);
  PUT32(GPCLR0,1<<16);
  for(ra=0;ra<0x100000;ra++) dummy(ra);
}

volatile bool interruptExecuted = false;

bool irq_enable( void ) {
  
  volatile uint32_t* address = (volatile uint32_t*)( 0x2000b000 );
  
  // ENABLE IRQ 1
  //*( address + 0x210 ) = (uint32_t)0x1000000000000; //0xFFFFFFFF;
  
  // ENABLE IRQ 2
  //*( address + 0x214 ) = 0xFFFFFFFF;
  
  // ENABLE BASIC IRQ
  //*( address + 0x218 ) = 0x000000FF;
  
  return true;
}

int main() {
  unsigned int ra;
  
  ra=GET32(GPFSEL1);
  ra&=~(7<<18);
  ra|=1<<18;
  PUT32(GPFSEL1,ra);
  
  blink();
  
  interruptExecuted = false;
  
  blink();
  
  irq_enable();
  
  blink();
  asm volatile( "SWI #0x0000FF" );
  blink();
  while (!interruptExecuted) {
    dummy(0);
  }
  
  while(1)
  {
    PUT32(GPSET0,1<<16);
    for(ra=0;ra<0x100000;ra++) dummy(ra);
    PUT32(GPCLR0,1<<16);
    for(ra=0;ra<0x100000;ra++) dummy(ra);
  }
  
  return 0;
}

extern "C" void irq_handler( void ) {
  blink();
  //interruptExecuted = true;
}