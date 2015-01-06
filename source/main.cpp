//
//  main.cpp
//  MKPi
//
//  Created by Maurus Kühne on 03.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "main.h"
#include "Memory.h"
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

int main() {
  unsigned int ra;
  
  ra=GET32(GPFSEL1);
  ra&=~(7<<18);
  ra|=1<<18;
  PUT32(GPFSEL1,ra);
  
  blink();
  
  interruptExecuted = false;
  
  blink();
  asm volatile( "SWI #0x00000A" );
  blink();
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
    PUT32(GPSET0,1<<16);
    for(ra=0;ra<0x100000;ra++) dummy(ra);
    PUT32(GPCLR0,1<<16);
    for(ra=0;ra<0x100000;ra++) dummy(ra);
  }
  interruptExecuted = true;
}

extern "C" void irq_handler( void ) {
  
  unsigned int ra;
  for(int i = 0; i < 10; i++)
  {
    PUT32(GPSET0,1<<16);
    for(ra=0;ra<0x100000;ra++) dummy(ra);
    PUT32(GPCLR0,1<<16);
    for(ra=0;ra<0x100000;ra++) dummy(ra);
  }
  interruptExecuted = true;
}