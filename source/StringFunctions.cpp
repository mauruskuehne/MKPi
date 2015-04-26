//
//  StringFunctions.cpp
//  MKPi
//
//  Created by Maurus Kühne on 26.04.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "StringFunctions.h"


int strcmp(char* first, char* second) {
  int pos = 0;
  while (first[pos] != '\0') {
    if (first[pos] != second[pos]) {
      return 0;
    }
    pos++;
  }
  return 1;
}
