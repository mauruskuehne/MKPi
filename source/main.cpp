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
#include "ArrayList.h"
#include "System.h"

#define GPFSEL1 PhysicalAddress{0x20200004}
#define GPSET0  PhysicalAddress{0x2020001C}
#define GPCLR0  PhysicalAddress{0x20200028}
#define GPPUD       PhysicalAddress{0x20200094}
#define GPPUDCLK0   PhysicalAddress{0x20200098}

using namespace HIL;
using namespace HIL::Memory;
using namespace System;

extern "C" void dummy ( unsigned int );

extern "C" void (*__init_array_start)();
extern "C" void (*__init_array_end)();


extern uint32_t __heap_start;
extern uint32_t __heap_end;

extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

extern uint32_t __data_rom_start__;
extern uint32_t __data_start__;
extern uint32_t __data_end__;

void blink() {
  unsigned int ra;
  Memory::write(GPSET0,1<<16);
  for(ra=0;ra<0x100000;ra++) dummy(ra);
  Memory::write(GPCLR0,1<<16);
  for(ra=0;ra<0x100000;ra++) dummy(ra);
}

void blink(int speed) {
  unsigned int ra;
  Memory::write(GPSET0,1<<16);
  for(ra=0;ra<speed;ra++) dummy(ra);
  Memory::write(GPCLR0,1<<16);
  for(ra=0;ra<speed;ra++) dummy(ra);
}

volatile bool interruptExecuted = false;


int main() {
  
  //initialize static variables
  for (uint32_t* address =((uint32_t*)&__init_array_start); address < (uint32_t*)&__init_array_end; address++) {
    uint32_t addrToCall = *address;
    void (*funcPtr)();
    funcPtr = (void(*)())addrToCall;
    (*funcPtr)();
  }
  
  UART* uart = UART::instance();
  
  
  uart->sendByte('\n');
  uart->sendByte('\n');
  uart->sendText("MKPi (rev ");
  uart->sendText(VERSION);
  uart->writeLine(")");
  
  blink();
  blink();
  
  int byteCounter = 0;
  char killSignal[] = "KILLPI";
  char testSignal[] = "TESTPI";
  
  char receivedText[7];
  
  while (true) {
    uint8_t readByte = uart->readByte();
    
    if(byteCounter > 6)
      byteCounter = 0;
    
    uart->sendText("\nReceived character: ");
    uart->sendByte(readByte);
    uart->sendByte('\n');
    
    receivedText[byteCounter++] = readByte;
    
    uart->sendText("\ncomplete received text: ");
    uart->sendText(receivedText, byteCounter);
    uart->sendText("\n");
    
    if (Strings::strcmp(killSignal, (const char*)receivedText)) {
      uart->sendText("self destruct");
      rebootSystem();
    }
    if(Strings::strcmp(testSignal, receivedText)) {
      
      //char * c = new char[50];
      ArrayList<uint32_t>* _arrlst = new ArrayList<uint32_t>();
      _arrlst->add(30);
    }
  }
  
  return 0;
}

extern "C" void svc_handler( uint32_t value ) {
  
  unsigned int ra;
  for(int i = 0; i < value; i++)
  {
    Memory::write(GPSET0,1<<16);
    for(ra=0;ra<0x100000;ra++) dummy(ra);
    Memory::write(GPCLR0,1<<16);
    for(ra=0;ra<0x100000;ra++) dummy(ra);
  }
  interruptExecuted = true;
}

extern "C" void irq_handler( void ) {
  
  unsigned int ra;
  for(int i = 0; i < 10; i++)
  {
    Memory::write(GPSET0,1<<16);
    for(ra=0;ra<0x100000;ra++) dummy(ra);
    Memory::write(GPCLR0,1<<16);
    for(ra=0;ra<0x100000;ra++) dummy(ra);
  }
  interruptExecuted = true;
}