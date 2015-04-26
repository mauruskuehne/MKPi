//
//  UART.h
//  MKPi
//
//  Created by Maurus Kühne on 19.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#ifndef __MKPi__UART__
#define __MKPi__UART__


#include "Memory.h"

namespace HIL {
  class UART
  {
  public:
    static UART* instance();
    void sendText(const char* text);
    void sendText(const char* text, int length);
    void sendInfiniteLoop();
    
    uint8_t readByte();
    void sendByte(uint8_t byte);
    
  private:
    UART();
    static UART* _instance;
  };

}

#endif /* defined(__MKPi__UART__) */
