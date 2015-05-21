//
//  UartMessage.h
//  MKPiSerialProtocol
//
//  Created by Maurus Kühne on 21/05/15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#ifndef MKPiSerialProtocol_UartMessage_h
#define MKPiSerialProtocol_UartMessage_h

#include <stdint.h>

struct UartMemDumpPacketInfo {
  uint32_t dumpSize;
  uint32_t blockCount;
  bool isPartial;
};

struct UartMemDumpDataBlock {
  uint32_t block_index;
  static const uint32_t size = 1024;
  uint8_t content[size];
};

enum UartMessageType : uint32_t {
  TextMessage = 0,
  BeginMemoryDump = 1,
  MemoryDumpSegment = 2,
  EndMemoryDump = 3,
  UserInput = 4
} typedef UartMessageType;


struct UartMessageHeader {
  private : const char header[13] = "***BEG***";
  public : UartMessageType messageType;
  public : uint32_t contentSize;
  public : uint32_t messageSize;
};

struct UartMessageFooter {
  private : const char footer[13] = "***END***";
};

struct UartMessage {
  UartMessageHeader header;
  
  union content {
    UartMemDumpPacketInfo memDumpPacketInfo;
    UartMemDumpDataBlock memDumpDataBlock;
  } content;
  
  UartMessageFooter footer;
  
  UartMessage(UartMessageType type) {
    header.messageType = type;
    header.contentSize = sizeof(content);
    header.messageSize = sizeof(UartMessage);
  }
};

#endif
