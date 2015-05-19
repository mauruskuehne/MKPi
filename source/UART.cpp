//
//  UART.cpp
//  MKPi
//
//  Created by Maurus Kühne on 19.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "UART.h"
#include <stdlib.h>

using namespace HIL;


extern "C" void dummy ( unsigned int );


namespace  UartMemory = Memory::Locations::UART;
namespace  GpioMemory = Memory::Locations::GPIO;

namespace HIL {
  
  UART* UART::_instance;
  
  UART* UART::instance() {
    if (UART::_instance == nullptr) {
      UART uart;
      UART::_instance = &uart;
    }
    
    return UART::_instance;
  }
  
  void delay(int32_t count) {
    asm volatile("1: subs %[count], %[count], #1; bne 1b"
                 : : [count]"r"(count));
  }
  
  UART::UART() {
    // Disable UART0
    
    Memory::write(UartMemory::CR, 0x00000000);
    // Setup the GPIO pin 14 && 15.
    
    
    // Disable pull up/down for all GPIO pins & delay for 150 cycles.
    Memory::write(GpioMemory::GPPUD, 0x00000000);
    delay(150);
    
    // Disable pull up/down for pin 14,15 & delay for 150 cycles.
    Memory::write(GpioMemory::GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);
    
    
    // Write 0 to GPPUDCLK0 to make it take effect.
    Memory::write(GpioMemory::GPPUDCLK0, 0x00000000);
    
    // Clear pending interrupts.
    Memory::write(UartMemory::ICR, 0x7FF);
    
    
    // Set integer & fractional part of baud rate.
    // Divider = UART_CLOCK/(16 * Baud)
    // Fraction part register = (Fractional part * 64) + 0.5
    // UART_CLOCK = 3000000; Baud = 115200.
    
    // Divider = 3000000/(16 * 115200) = 1.627 = ~1.
    // Fractional part register = (.627 * 64) + 0.5 = 40.6 = ~40.
    Memory::write(UartMemory::IBRD, 1);
    Memory::write(UartMemory::FBRD, 40);
    
    // Enable FIFO & 8 bit data transmissio (1 stop bit, no parity).
    Memory::write(UartMemory::LCRH, (1 << 4) | (1 << 5) | (1 << 6));
    
    // Mask all interrupts.
    Memory::write(UartMemory::IMSC, (1 << 1) | (1 << 4) | (1 << 5) |
                  (1 << 6) | (1 << 7) | (1 << 8) |
                  (1 << 9) | (1 << 10));
    
    // Enable UART0, receive & transfer part of UART.
    Memory::write(UartMemory::CR, (1 << 0) | (1 << 8) | (1 << 9));

  }
  
  void UART::writeLine(const char *text) {
    sendText(text);
    sendByte('\n');
  }
  
  void UART::sendText(const char* text) {
    for(int i = 0; text[i] != '\0'; i++) {
      sendByte(text[i]);
    }
  }
  
  void UART::sendText(const char* text, int length) {
    for(int i = 0; i < length; i++) {
      sendByte(text[i]);
    }
    
    if(text[length - 1] != '\0')
      sendByte('\0');
  }
  
  uint8_t UART::readByte() {
    while (1) {
      if(!(Memory::read(UartMemory::FR) & (1<<4))) break;
    }
    
    return Memory::read(UartMemory::DR);
  }
  
  void UART::sendByte(uint8_t byte) {
    while(1) {
      if(!(Memory::read(UartMemory::FR)&(1<<5))) break;
    }
    Memory::write(UartMemory::DR, byte);
  }
  
  void UART::sendBytes(uint8_t* bytes, size_t length) {
    for (size_t i = 0; i < length; i++) {
      this->sendByte(bytes[i]);
    }
  }
  
  void UART::sendMessage(UartMessage* msg) {
    uint32_t headerSize = sizeof(msg->header);
    uint32_t footerSize = sizeof(msg->footer);
    
    this->sendBytes((uint8_t*)&(msg->header), headerSize);
    this->sendBytes(msg->content, msg->header.contentSize);
    this->sendBytes((uint8_t*)&msg->footer, footerSize);
  }
}

