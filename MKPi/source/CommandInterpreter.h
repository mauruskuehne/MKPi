//
//  CommandInterpreter.h
//  MKPi
//
//  Created by Maurus Kühne on 16.05.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#ifndef __MKPi__CommandInterpreter__
#define __MKPi__CommandInterpreter__

#include <stdio.h>

namespace System {
  class CommandInterpreter {
    
  public:
    
    void interpretCommand(const char* input);
    
  };
}


#endif /* defined(__MKPi__CommandInterpreter__) */
