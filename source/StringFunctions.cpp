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


char charForValue(uint8_t value) {
  switch(value) {
    case 0:
      return '0';
    case 1:
      return '1';
    case 2:
      return '2';
    case 3:
      return '3';
    case 4:
      return '4';
    case 5:
      return '5';
    case 6:
      return '6';
    case 7:
      return '7';
    case 8:
      return '8';
    case 9:
      return '9';
    case 10:
      return 'A';
    case 11:
      return 'B';
    case 12:
      return 'C';
    case 13:
      return 'D';
    case 14:
      return 'E';
    case 15:
      return 'F';
      
  }
}

void tostr(uint32_t val, char* buffer) {
  //buffer = new char[11];
  
  uint32_t halfByteMask = 0x0000000F;
  
  buffer[0] = '0';
  buffer[1] = 'x';
  buffer[2] = '0';
  buffer[3] = '0';
  buffer[4] = '0';
  buffer[5] = '0';
  buffer[6] = '0';
  buffer[7] = '0';
  buffer[8] = '0';
  buffer[9] = '0';
  int idx = 9;
  while (val > 0) {
    uint8_t halfByteValue = val & halfByteMask;
    
    buffer[idx] = charForValue(halfByteValue);
    
    val = val >> 4;
    idx--;
  }
  
  buffer[10] = '\0';
}

void strcpy(char* in, char* out) {
  uint32_t val = 0;
  while(in[val] != '\0') {
    out[val] = in[val];
    val++;
  }
}

void concat(char* first, char* second, char* res) {
  uint32_t str1Len = strlen(first);
  //res = new char[str1Len + strlen(second) + 1];
  
  
  strcpy(first, res);
  strcpy(second, &res[str1Len + 1]);
  return;
}

uint32_t strlen(char* str) {
  uint32_t val = 0;
  while(str[val] != '\0') {
    val++;
  }
  return val;
}