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

enum UartMessageType : uint32_t {
  TextMessage = 0,
  BeginMemoryDump = 1,
  MemoryDumpSegment = 2,
  EndMemoryDump = 3
} typedef UartMessageType;


struct UartMessageHeader {
  UartMessageType messageType;
  uint32_t contentSize;
};

struct UartMessageFooter {
  private : const char footer1[13] = "***MSGEND***";
  public  : uint32_t contentSize;
  private : const char footer2[13] = "***MSGEND***";
};

struct UartMessage {
  UartMessageHeader header;
  uint8_t* content;
  
  UartMessageFooter footer;
  
  UartMessage(uint8_t* content, uint32_t size, UartMessageType type) {
    this->content = content;
    header.messageType = type;
    header.contentSize = size;
    footer.contentSize = size;
  }
};

class foo {
  
  
public:
  void bar();
};

#endif /* defined(__MKPiSerialProtocol__UartMessage__) */
