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
#include "StringFunctions.h"
#include "Errors.h"


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
  
  blink();
  blink();
  
  
  
  
  
  //old code
  ra=Memory::GET32(GPFSEL1);
  ra&=~(7<<18);
  ra|=1<<18;
  Memory::PUT32(GPFSEL1,ra);
  
  
  blink();
  blink();
  
  UART* uart = UART::instance();
  
  
  blink();
  blink();
  
  uart->sendText("foo bar?");
  
  blink();
  blink();
  
  int byteCounter = 0;
  char killSignal[] = "KILLPI";
  
  char receivedText[7];
  
  while (true) {
    uint8_t readByte = uart->readByte();
    
    //uart->sendByte(readByte);
    if(byteCounter > 6)
      byteCounter = 0;
    
    uart->sendText("\nReceived character: ");
    uart->sendByte(readByte);
    uart->sendByte('\n');
    
    receivedText[byteCounter++] = readByte;
    
    uart->sendText("\ncomplete received text: ");
    uart->sendText(receivedText, byteCounter);
    uart->sendText("\n");
    
    if (strcmp(killSignal, receivedText)) {
      uart->sendText("self destruct");
      rebootSystem();
    }
  }
  
  /*
  Framebuffer* buffer;
  
  buffer->initialize();*/
  /*
  blink();
  
  interruptExecuted = false;
  
  blink();
  asm volatile( "SWI #0x00000A" );
  blink();*/
  return 0;
  
  ra=0;
    #define AUX_MU_LSR_REG  0x20215054
#define AUX_MU_IO_REG   0x20215040
  /*uart->sendText("Hallo Welt", 10);*/
  int length = 10;
  const char* text = "Hallo Welt";
  for(int i = 0; i < length; i++)
  {
    while(1)
    {
      blink();
      if(Memory::GET32(AUX_MU_LSR_REG)&0x20) break;
    }
    Memory::PUT32(AUX_MU_IO_REG,text[i]);
  }
  
  blink();
  blink();
  
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