//
//  newlib_syscalls.h
//  MKPi
//
//  Created by Maurus Kühne on 14.05.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#ifndef __MKPi__newlib_syscalls__
#define __MKPi__newlib_syscalls__

#include <sys/stat.h>

extern "C" int _lose(int file);

extern "C" void* _sbrk(int incr);

extern "C" int _write(int file, char *ptr, int len);

extern "C" int _fstat(int file, struct stat *st);

extern "C" int _isatty(int file);

extern "C" int _lseek(int file, int ptr, int dir);

extern "C" int _read(int file, char *ptr, int len);

extern "C" void _exit();

extern "C" int _getpid();

extern "C" int _kill(int pid, int sig);

#endif /* defined(__MKPi__newlib_syscalls__) */
