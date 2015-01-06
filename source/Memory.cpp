//
//  Memory.cpp
//  MKPi
//
//  Created by Maurus Kühne on 06.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "Memory.h"

namespace HIL {
  void Memory::MemoryBarrier() {
    asm volatile( "mcr p15, 0, ip, c7, c5, 0" );
    asm volatile( "mcr p15, 0, ip, c7, c5, 6" );
    asm volatile( "mcr p15, 0, ip, c7, c10, 4" );
    asm volatile( "mcr p15, 0, ip, c7, c5, 4" );
  }
}
