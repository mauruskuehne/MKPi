//
//  Errors.cpp
//  MKPi
//
//  Created by Maurus Kühne on 26.04.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "Errors.h"

#include "UART.h"
#include "StringFunctions.h"

using namespace HIL;
using namespace HIL::Memory;

void fatalError(const char* errorMessage) {
  int byteCounter = 0;
  char killSignal[] = "KILLPI";
  
  char receivedText[7];
  
  UART* uart = UART::instance();
  
  uart->sendText(errorMessage);
  
  while (true) {
    uint8_t readByte = uart->readByte();
    
    if(byteCounter > 6)
      byteCounter = 0;
    
    uart->sendByte(readByte);
    
    receivedText[byteCounter++] = readByte;
    
    if (Strings::strcmp(killSignal, receivedText)) {
      uart->sendText("self destruct");
      rebootSystem();
    }
  }
}

void rebootSystem()
{
  PhysicalAddress PM_RSTC {0x2010001c};
  PhysicalAddress PM_WDOG = {0x20100024};
  const int PM_PASSWORD = 0x5a000000;
  const int PM_RSTC_WRCFG_FULL_RESET = 0x00000020;
  
  Memory::write(PM_WDOG, PM_PASSWORD | 1); // timeout = 1/16th of a second? (whatever)
  Memory::write(PM_RSTC, PM_PASSWORD | PM_RSTC_WRCFG_FULL_RESET);
  while(1);
}