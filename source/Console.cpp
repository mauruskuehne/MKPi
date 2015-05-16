//
//  Console.cpp
//  MKPi
//
//  Created by Maurus Kühne on 16.05.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "Console.h"

namespace System {
  
  Console::Console(CommandInterpreter* interpreter) {
    
  }
  
  void Console::run() {
    while (true) {
      char buffer[1024];
      printf("\n> ");
      scanf("%s", &buffer);
      
      if(strcasecmp("KILLPI", buffer) == 0) {
        printf("self destruct\n");
        //led->blink();
        rebootSystem();
      } else if (strcasecmp("TESTPI", buffer) == 0) {
        printf("hello world");
      } else if(strcasecmp("FAILPI", buffer) == 0) {
        char txt[80];
        sprintf(txt, "could not convert from bus address to physical address -> %#010x", 0x400);
        fatalError(txt);
      } else {
        printf("didn't recognize command");
      }
    }
  }
}
