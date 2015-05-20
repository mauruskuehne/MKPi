//
//  Console.h
//  MKPi
//
//  Created by Maurus Kühne on 16.05.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#ifndef __MKPi__Console__
#define __MKPi__Console__

#include <stdio.h>
#include "System.h"
#include "HIL.h"
#include "CommandInterpreter.h"

namespace System {
  class Console {
  private:
    CommandInterpreter* _interpreter;
    
    
  public:
    Console(CommandInterpreter* interpreter);
    
    void run();
  };
}



#endif /* defined(__MKPi__Console__) */
