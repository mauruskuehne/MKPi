//
//  Mailbox.h
//  MKPi
//
//  Created by Maurus Kühne on 06.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#ifndef __MKPi__Mailbox__
#define __MKPi__Mailbox__

#include <stdint.h>
#include "Memory.h"

namespace HIL {
  
  class Mailbox {
  private:

  public:
    Mailbox();
    uint32_t Read(uint32_t channel);
    void Write(uint32_t channel, uint32_t value);
  };
}


#endif /* defined(__MKPi__Mailbox__) */
