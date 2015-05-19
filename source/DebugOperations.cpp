//
//  DebugOperations.cpp
//  MKPi
//
//  Created by Maurus Kühne on 19/05/15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "DebugOperations.h"
#include "UART.h"


extern uint32_t __ram_end;

using namespace HIL;

namespace System {
  namespace Diagnostics {
    
    void DebugOperations::dump_memory(uint32_t startAddress, uint32_t endAddress) {
      
      const uint32_t blockSize = 1024;
      
      printf("*** begin memory dump ***\n");
      
      uint32_t size = endAddress - startAddress;
      
      
      printf("dump size: %lx bytes\n", size);
      
      UartMemDumpPacketInfo* pkgInfo = new UartMemDumpPacketInfo();
      
      pkgInfo->dumpSize = size;
      pkgInfo->blockCount = (size / blockSize) + 1;
      
      UartMessage* msg = new UartMessage((uint8_t*)&pkgInfo, sizeof(UartMemDumpPacketInfo), UartMessageType::BeginMemoryDump);
      
      printf("created begin dump message packet\n");
      
      UART* uart = UART::instance();
      
      
      uart->sendMessage(msg);
      
      printf("sent begin dump message packet\n");
      
      printf("begin sending dump packets...\n");
      
      UartMemDumpDataBlock* blockData = new UartMemDumpDataBlock();
      
      UartMessage* packetMsg = new UartMessage((uint8_t*)&blockData, sizeof(blockData), UartMessageType::MemoryDumpSegment);
      for (uint32_t i = 0; i <= pkgInfo->blockCount; i++) {
        
        uint32_t currentAddress = (startAddress + (pkgInfo->blockCount * i));
        
        uint32_t currentBlockSize = (currentAddress > endAddress) ? currentAddress - endAddress : blockSize;
        
        printf("sending packet %lu/%lu containing %lu bytes\n", i, pkgInfo->blockCount, currentBlockSize);
        
        blockData->content = 
        
        uart->sendMessage(packetMsg);
      }
      
      delete pkgInfo;
      delete msg;
      delete packetMsg;
    }
    
    void DebugOperations::dump_memory() {
      dump_memory(0x0, __ram_end);
    }
    
    
  }
}