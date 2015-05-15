//
//  ActLed.h
//  MKPi
//
//  Created by Maurus Kühne on 15.05.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#ifndef __MKPi__ActLed__
#define __MKPi__ActLed__

#include "System.h"
#include "HIL.h"

namespace HIL {
  class ActLed
  {
  public:
    static ActLed* instance();
    
    void blink();
    void blink(uint32_t speed);
    
  private:
    ActLed();
    static ActLed* _instance;
  };
  
}
#endif /* defined(__MKPi__ActLed__) */
