//
//  newlib_syscalls.cpp
//  MKPi
//
//  Created by Maurus Kühne on 14.05.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "newlib_syscalls.h"
#include <cstdint>
#include <stdlib.h>
#include <stdio.h>
#include "UART.h"
#include <sys/stat.h>
#include "Errors.h"

extern void blink();
extern void rebootSystem();

void intToChars(uint32_t val, char* arr, int len) {
  snprintf(arr, len, "%#08x", val);
}

using namespace HIL;

extern "C" int _close(int file) {
  return -1;
}

extern "C" uint32_t* __heap_start;
static uint32_t _current_heap_end = 0;
extern "C" void* _sbrk(int incr) {
    _current_heap_end += incr;
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

extern "C" void _exit() {
  
}

extern "C" int _getpid() {
  return 0;
}

extern "C" int _kill(int pid, int sig) {
  return 0;
}
