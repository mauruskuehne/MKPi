//
//  ArrayList.h
//  MKPi
//
//  Created by Maurus Kühne on 02.05.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#ifndef __MKPi__ArrayList__
#define __MKPi__ArrayList__

#include <stdint.h>

template <typename T>
class ArrayList {
  private :
  uint32_t _idx;
  T _arr[];
  
public:
  ArrayList() {
    _arr[10];
    _idx = 0;
  }

  void add(T obj) {
    _arr[_idx++] = obj;
  }
};

#endif /* defined(__MKPi__ArrayList__) */

