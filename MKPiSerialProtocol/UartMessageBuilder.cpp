//
//  UartMessage.cpp
//  MKPiSerialProtocol
//
//  Created by Maurus Kühne on 20.05.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "Include/UartMessageBuilder.h"
#include "Include/UartMessage.h"
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <new>
#include <stdio.h>
#include <string.h>

UartMessage* UartMessageBuilder::CreateMemDumpPacketInfo(uint32_t memDumpSize, bool isPartial) {
  UartMemDumpPacketInfo pkgInfo;
  
  pkgInfo.blockCount = memDumpSize / 1024;
  
  if(memDumpSize % 1024 != 0)
    pkgInfo.blockCount++;
  
  pkgInfo.dumpSize = memDumpSize;
  pkgInfo.isPartial = isPartial;
  
  UartMessage* msg = new UartMessage(BeginMemoryDump);
  msg->content.memDumpPacketInfo = pkgInfo;
  return msg;
}

UartMessage* UartMessageBuilder::CreateMemDumpBlock(uint32_t block_index, uint8_t* block_start) {
  
  UartMemDumpDataBlock block;
  
  block.block_index = block_index;
  
  memcpy(block.content, block_start, 1024);
  
  UartMessage* msg = new UartMessage(BeginMemoryDump);
  msg->content.memDumpDataBlock = block;
  return msg;
}