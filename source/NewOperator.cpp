//
//  NewOperator.cpp
//  MKPi
//
//  Created by Maurus Kühne on 02.05.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "NewOperator.h"
#include <new>
#include "System.h"
#include "UART.h"

using namespace HIL;

void* operator new (std::size_t size) throw (std::bad_alloc) {
  
  UART* uart = UART::instance();
  
  char chrSize[10];
  System::Strings::tostr(size, chrSize);
  uart->sendText("should allocate space: ");
  uart->sendText(chrSize, 10);
  uart->sendByte('\n');
}

namespace System {
  
  
}