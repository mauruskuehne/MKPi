//
//  ActLed.cpp
//  MKPi
//
//  Created by Maurus Kühne on 15.05.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "ActLed.h"
#include "Memory.h"

extern "C" void dummy ( unsigned int );


namespace HIL {
  using namespace Memory::Locations;
  
  ActLed* ActLed::_instance;
  
  ActLed::ActLed() {
    
  }
  
  ActLed* ActLed::instance() {
    if (ActLed::_instance == nullptr) {
      ActLed led;
      ActLed::_instance = &led;
    }
    
    return ActLed::_instance;
  }

  
  void ActLed::blink() {
    blink(0x100000);
  }
  
  void ActLed::blink(uint32_t speed) {
    unsigned int ra;
    
    Memory::write(GPIO::GPSET0,1<<16);
    for(ra=0;ra<speed;ra++) dummy(ra);
    Memory::write(GPIO::GPCLR0,1<<16);
    for(ra=0;ra<speed;ra++) dummy(ra);
  }
}
