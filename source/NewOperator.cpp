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

void* operator new (std::size_t size) throw (std::bad_alloc) {
  void* addr =malloc(size);
  return addr;
}

void* operator new[] (std::size_t size) throw (std::bad_alloc) {
  void* addr =malloc(size);
  return addr;
}

void operator delete (void* ptr) {
  free(ptr);
}
