//
//  DebugOperations.cpp
//  MKPi
//
//  Created by Maurus Kühne on 19/05/15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "DebugOperations.h"
#include "UART.h"
#include "UartMessage.h"
#include "UartMessageBuilder.h"


extern uint32_t __ram_end;

using namespace HIL;

namespace System {
  namespace Diagnostics {
    
    void DebugOperations::dump_memory(uint32_t startAddress, uint32_t endAddress) {
      
      const uint32_t blockSize = 1024;
      
      printf("*** begin memory dump ***\n");
      
      uint32_t size = endAddress - startAddress;
      
      
      printf("dump size: %lx bytes\n", size);
      
//      UartMessage* msg = new UartMessage((uint8_t*)&pkgInfo, sizeof(UartMemDumpPacketInfo), UartMessageType::BeginMemoryDump);
      
      UartMessage* msg = UartMessageBuilder::CreateMemDumpPacketInfo(size, true);
      
      
      
      printf("created begin dump message packet\n");
      
      UART* uart = UART::instance();
      
      
      uart->sendMessage(msg);
      
      printf("sent begin dump message packet\n");
      
      printf("begin sending dump packets...\n");
      
      for (uint32_t i = 0; i <= msg->content.memDumpPacketInfo.blockCount; i++) {
      
        
        
        uint32_t currentAddress = (startAddress + (msg->content.memDumpPacketInfo.blockCount * i));
        
        uint32_t currentBlockSize = (currentAddress > endAddress) ? currentAddress - endAddress : blockSize;
        
        UartMessage* packetMsg = UartMessageBuilder::CreateMemDumpBlock(i, (uint8_t*) currentAddress);
        
        printf("sending packet %lu/%lu containing %lu bytes\n", i, pkgInfo->blockCount, currentBlockSize);
        
        
        uart->sendMessage(packetMsg);
        
        delete packetMsg;
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