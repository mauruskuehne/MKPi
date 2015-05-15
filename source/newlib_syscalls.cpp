//
//  newlib_syscalls.cpp
//  MKPi
//
//  Created by Maurus Kühne on 14.05.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "newlib_syscalls.h"
#include <stdlib.h>
#include "UART.h"
#include <sys/stat.h>
#include "StringFunctions.h"

using namespace HIL;

extern "C" int _close(int file) {
  return -1;
}

extern "C" void* _sbrk(int incr) {
  /*extern char _end;		/* Defined by the linker *//*
  static char *heap_end;
  char *prev_heap_end;
  
  if (heap_end == 0) {
    heap_end = &_end;
  }
  prev_heap_end = heap_end;
  if (heap_end + incr > stack_ptr) {
    write (1, "Heap and stack collision\n", 25);
    abort ();
  }
  
  heap_end += incr;
  return (caddr_t) prev_heap_end;*/
  return 0;
}

extern "C" int _write(int file, char *ptr, int len) {
  UART* uart = UART::instance();
  uart->sendText(ptr, len);
  return len;
}

extern "C" int _fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}

extern "C" int _isatty(int file) {
  return 1;
}

extern "C" int _lseek(int file, int ptr, int dir) {
  return 0;
}

extern "C" int _read(int file, char *ptr, int len) {
  UART* uart = UART::instance();
  int i;
  for (i = 0; i < len; i++) {
    ptr[i] = uart->readByte();
    uart->sendByte(ptr[i]);

    if(ptr[i] == '\n' || ptr[i] == '\r') {
      ptr[i] = '\n';
      return i + 1;
    }
  }
  return i + 1;
}
