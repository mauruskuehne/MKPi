//
//  StringFunctions.h
//  MKPi
//
//  Created by Maurus Kühne on 26.04.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#ifndef __MKPi__StringFunctions__
#define __MKPi__StringFunctions__

#include <stdint.h>

namespace Strings {
  
  int strcmp(const char* first, const char* second);
  
  void tostr(uint32_t val, char* buffer);
  
  void concat(const char* first, const char* second, char* res);
  
  uint32_t strlen(const char* str);
}


#endif /* defined(__MKPi__StringFunctions__) */
