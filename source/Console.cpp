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
    char* buffer = new char[1024];
    
    while (true) {
    //  char buffer[1024];
      
      printf("\n> ");
      scanf("%s", buffer);
      
      _interpreter->interpretCommand(buffer);
      
    }
  }
}
