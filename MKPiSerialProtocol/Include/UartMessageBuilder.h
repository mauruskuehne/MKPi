//
//  UartMessage.h
//  MKPiSerialProtocol
//
//  Created by Maurus Kühne on 20.05.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#ifndef __MKPiSerialProtocol__UartMessage__
#define __MKPiSerialProtocol__UartMessage__

#include <stdio.h>
#include <stdint.h>
#include "UartMessage.h"

class UartMessageBuilder {
  
  
public:
  static UartMessage* CreateMemDumpPacketInfo(uint32_t memDumpSize, bool isPartial);
  static UartMessage* CreateMemDumpBlock(uint32_t block_index, uint8_t* block_start);
};

#endif /* defined(__MKPiSerialProtocol__UartMessage__) */
