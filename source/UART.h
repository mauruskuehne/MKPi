//
//  UART.h
//  MKPi
//
//  Created by Maurus Kühne on 19.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#ifndef __MKPi__UART__
#define __MKPi__UART__


#include "Memory.h"
#include "HIL.h"
#include <stdint.h>

namespace HIL {
  
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
  
  class UART
  {
  public:
    static UART* instance();
    void writeLine(const char* text);
    void sendText(const char* text);
    void sendText(const char* text, int length);
    
    uint8_t readByte();
    
    void sendBytes(uint8_t* bytes, size_t length);
    void sendByte(uint8_t byte);
    void sendMessage(UartMessage* msg);
    
  private:
    UART();
    static UART* _instance;
  };
  
}

#endif /* defined(__MKPi__UART__) */
