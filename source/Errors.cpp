//
//  Errors.cpp
//  MKPi
//
//  Created by Maurus Kühne on 26.04.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "Errors.h"

#include "System.h"
#include "HIL.h"

using namespace HIL;
using namespace HIL::Memory;


void fatalError(const char* errorMessage) {
  printf(errorMessage);

  while (true) {
    
    printf("\nsystem failed with a fatal error.\n");
    printf("enter KILLPI to reboot.\n");
    
    char buffer[1024];
    printf("> ");
    scanf("%s", &buffer);
    
    if(strcasecmp("KILLPI", buffer) == 0) {
      printf("self destruct\n");
      ActLed* led = ActLed::instance();
      led->blink();
      rebootSystem();
    }
  }
}

void rebootSystem()
{
  PhysicalAddress PM_RSTC {0x2010001c};
  PhysicalAddress PM_WDOG = {0x20100024};
  const int PM_PASSWORD = 0x5a000000;
  const int PM_RSTC_WRCFG_FULL_RESET = 0x00000020;
  
  Memory::write(PM_WDOG, PM_PASSWORD | 1); // timeout = 1/16th of a second? (whatever)
  Memory::write(PM_RSTC, PM_PASSWORD | PM_RSTC_WRCFG_FULL_RESET);
  while(1);
}