#!/bin/sh

#  compile_newlib.sh
#  MKPi
#
#  Created by Maurus Kühne on 14.05.15.
#  Copyright (c) 2015 Maurus Kühne. All rights reserved.

cd ../external/newlib

CC=arm-none-eabi-gcc CFLAGS=--specs=nosys.specs ./configure --host arm-none-eabi
CC=arm-none-eabi-gcc CFLAGS=--specs=nosys.specs ./newlib/configure --host arm-none-eabi


cd ../external/newlib
make
cd newlib
make
