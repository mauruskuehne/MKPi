//
//  CommandInterpreter.cpp
//  MKPi
//
//  Created by Maurus Kühne on 16.05.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "CommandInterpreter.h"
#include "System.h"

namespace System {
  void CommandInterpreter::interpretCommand(const char *input) {
    
    if(strcasecmp("KILLPI", input) == 0) {
      printf("self destruct\n");
      //led->blink();
      rebootSystem();
    } else if (strcasecmp("TESTPI", input) == 0) {
      printf("hello world");
    } else if(strcasecmp("FAILPI", input) == 0) {
      char txt[80];
      sprintf(txt, "could not convert from bus address to physical address -> %#010x", 0x400);
      fatalError(txt);
    } else {
      printf("didn't recognize command");
    }
  }
}