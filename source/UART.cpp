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
/*
#define GPFSEL1 0x20200004
#define GPSET0  0x2020001C
#define GPCLR0  0x20200028
#define GPPUD       0x20200094
#define GPPUDCLK0   0x20200098*/

#define AUX_IRQ         0x20215000
#define AUX_ENABLES     0x20215004
#define AUX_MU_IO_REG   0x20215040
#define AUX_MU_IER_REG  0x20215044
#define AUX_MU_IIR_REG  0x20215048
#define AUX_MU_LCR_REG  0x2021504C
#define AUX_MU_MCR_REG  0x20215050
#define AUX_MU_LSR_REG  0x20215054
#define AUX_MU_MSR_REG  0x20215058
#define AUX_MU_SCRATCH  0x2021505C
#define AUX_MU_CNTL_REG 0x20215060
#define AUX_MU_STAT_REG 0x20215064
#define AUX_MU_BAUD_REG 0x20215068

extern void blink(int speed);
extern void blink();

namespace HIL {
  //0x 7E20 0000
  //
  enum UartMemory {
    // The GPIO registers base address.
    
    PERIPHERAL_START = 0x20000000,
    
    GPIO_OFFSET = PERIPHERAL_START + 0x00200000,
    
    // The offsets for reach register.
    
    // Controls actuation of pull up/down to ALL GPIO pins.
    GPPUD = (GPIO_OFFSET + 0x94),
    
    // Controls actuation of pull up/down for specific GPIO pin.
    GPPUDCLK0 = (GPIO_OFFSET + 0x98),
    
    // The base address for UART.
    UART0_OFFSET = GPIO_OFFSET + 0x00001000,
    
    // The offsets for reach register for the UART.
    UART0_DR     = (UART0_OFFSET + 0x00),
    UART0_RSRECR = (UART0_OFFSET + 0x04),
    UART0_FR     = (UART0_OFFSET + 0x18),
    UART0_ILPR   = (UART0_OFFSET + 0x20),
    UART0_IBRD   = (UART0_OFFSET + 0x24),
    UART0_FBRD   = (UART0_OFFSET + 0x28),
    UART0_LCRH   = (UART0_OFFSET + 0x2C),
    UART0_CR     = (UART0_OFFSET + 0x30),
    UART0_IFLS   = (UART0_OFFSET + 0x34),
    UART0_IMSC   = (UART0_OFFSET + 0x38),
    UART0_RIS    = (UART0_OFFSET + 0x3C),
    UART0_MIS    = (UART0_OFFSET + 0x40),
    UART0_ICR    = (UART0_OFFSET + 0x44),
    UART0_DMACR  = (UART0_OFFSET + 0x48),
    UART0_ITCR   = (UART0_OFFSET + 0x80),
    UART0_ITIP   = (UART0_OFFSET + 0x84),
    UART0_ITOP   = (UART0_OFFSET + 0x88),
    UART0_TDR    = (UART0_OFFSET + 0x8C),
  };

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
    
    Memory::PUT32(UART0_CR, 0x00000000);
    // Setup the GPIO pin 14 && 15.
    
    blink();
    
    // Disable pull up/down for all GPIO pins & delay for 150 cycles.
    Memory::PUT32(GPPUD, 0x00000000);
    delay(150);
    
    blink();
    
    // Disable pull up/down for pin 14,15 & delay for 150 cycles.
    Memory::PUT32(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);
    
    blink();
    
    // Write 0 to GPPUDCLK0 to make it take effect.
    Memory::PUT32(GPPUDCLK0, 0x00000000);
    
    blink();
    
    // Clear pending interrupts.
    Memory::PUT32(UART0_ICR, 0x7FF);
    
    blink();
    
    // Set integer & fractional part of baud rate.
    // Divider = UART_CLOCK/(16 * Baud)
    // Fraction part register = (Fractional part * 64) + 0.5
    // UART_CLOCK = 3000000; Baud = 115200.
    
    // Divider = 3000000/(16 * 115200) = 1.627 = ~1.
    // Fractional part register = (.627 * 64) + 0.5 = 40.6 = ~40.
    Memory::PUT32(UART0_IBRD, 1);
    Memory::PUT32(UART0_FBRD, 40);
    
    blink();
    
    // Enable FIFO & 8 bit data transmissio (1 stop bit, no parity).
    Memory::PUT32(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));
    
    blink();
    
    // Mask all interrupts.
    Memory::PUT32(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) |
                (1 << 6) | (1 << 7) | (1 << 8) |
                (1 << 9) | (1 << 10));
    
    blink();
    
    // Enable UART0, receive & transfer part of UART.
    Memory::PUT32(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));

    blink();
  }
  
  void UART::sendText(char* text) {
    for(int i = 0; text[i] != '\0'; i++)
    {
      sendByte(text[i]);
    }
  }
  
  void UART::sendText(char* text, int length) {
    for(int i = 0; i < length; i++)
    {
      sendByte(text[i]);
    }
    
    if(text[length - 1] != '\0')
      sendByte('\0');
  }
  
  uint8_t UART::readByte() {
    while (1) {
      if(!(Memory::GET32(UART0_FR) & (1<<4))) break;
    }
    
    return Memory::GET32(UART0_DR);
  }
  
  void UART::sendByte(uint8_t byte) {
    while(1)
    {
      if(!(Memory::GET32(UART0_FR)&(1<<5))) break;
    }
    Memory::PUT32(UART0_DR,byte);
  }
  
  void UART::sendInfiniteLoop() {
    
    uint32_t ra = 0;
    while(1)
    {
      while(1)
      {
        
        if(Memory::GET32(UART0_FR)&0x20) break;
      }
      Memory::PUT32(UART0_DR,0x30+(ra++&7));
    }
  }
  
}

