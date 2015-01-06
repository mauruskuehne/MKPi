//
//  Framebuffer.cpp
//  MKPi
//
//  Created by Maurus Kühne on 06.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include "Framebuffer.h"
#include "MailboxRequests.h"
#include <stdint.h>
#include <string>

#define CHARSIZE_X	6
#define CHARSIZE_Y	10

extern  unsigned char kernel_default_font[];
extern void blink();

volatile void PUT4( uint32_t addr, char value ) {
  // Create a pointer to our location in memory.
  volatile char* ptr = (volatile char*)( addr );
  // Set the value.
  *ptr = value;
}

namespace HIL {
  
  extern "C" void PUT32 ( unsigned int, unsigned int );
  extern "C" unsigned int GET32 ( unsigned int );
  
  Framebuffer::Framebuffer() {
    _depth = 24;
  }
  
  bool Framebuffer::initialize() {
    volatile mb_fb_get_physical_size sizeReq;
    
    
    _mailbox.Write( 8, 0x40000000 + ((uint32_t)&sizeReq) );
    
    uint32_t retval = _mailbox.Read(8);
    if((retval == 0) || (sizeReq.responseCode != 0x80000000)){
      return false;
    }
    
    _xSize = sizeReq.width;
    _ySize = sizeReq.height;
    
    mb_fb_alloc_buffer req;
    
    req.physical_width = _xSize;
    req.physical_height = _ySize;
    
    req.virtual_width = _xSize;
    req.virtual_height = _ySize;
    
    req.depth = _depth;
    
    req.bufferInfo.alignment = 16;
    
    _mailbox.Write(8, 0x40000000 + ((uint32_t)&req) );
    
    retval = _mailbox.Read(8);
    if((retval == 0)) {//|| (req.responseCode != 0x80000000)){
      return false;
    }
    
    _address = req.bufferInfo.response.address;
    _bufferSize = req.bufferInfo.response.size;
    
    mb_fb_get_pitch pitchReq;
    
    _mailbox.Write(8, 0x40000000 + ((uint32_t)&pitchReq) );
    retval = _mailbox.Read(8);
    if((retval == 0) || (pitchReq.responseCode != 0x80000000)){
      return false;
    }
    
    _pitch = pitchReq.pitch;
    
    Colour colour;
    colour.r = 255;
    colour.b = 0;
    colour.g = 0;
    /*
    for (uint32_t x = 0; x < _xSize; x++) {
      for (uint32_t y = 0; y < _ySize; y++) {
        this->put_pixel_RGB24(x, y, colour);
      }
    }*/
    
    //return true;
    //_backbuffer = (uint32_t*) malloc(3 * _xSize * _ySize);
    
    char* str = "Hallo Welt";
    
    for (int i = 0; 0 < 10; i++) {
      char c = str[i];
      DrawCharacter(i * 10, i *10, c, 0xFF0000);
    }
    
    return true;
  }
  
  
  void Framebuffer::put_pixel_RGB24(uint32_t x, uint32_t y, Colour colour)
  {
    
    //volatile uint32_t *ptr=0;
    uint32_t offset=0;
    
    offset = (y * _pitch) + (x * 3);
    /*ptr = (uint32_t*)(_address + offset);
    *((uint8_t*)ptr) = colour.r;
    *((uint8_t*)(ptr+1)) = colour.g;
    *((uint8_t*)(ptr+2)) = colour.b;*/
    
    
  }
  
  void Framebuffer::DrawCharacter(int x, int y, char c, uint32_t color) {
    char bytes[16];
    uint32_t start = (uint32_t)c * 16, end = start + 16, i = 0;
    for ( i = 0; i < 16; i++ ) {
      bytes[i] = kernel_default_font[start + i];
    }
    
    // Create a loop.
    short num1 = 0, num2 = 0;
    for ( num1 = 0; num1 < 16; num1++ ) {
      
      char databit = bytes[num1];
      
      bool show = false;
      
      // Do some bit math.
      for ( num2 = 0; num2 < 8; num2++ ) {
        
        // Figure out whether to show a given bit.
        show = ( databit & (0x01 << num2) ) != 0;
        
        // If show, then show.
        if ( show ) {
          
          uint32_t offset = ( ( y + num1 ) * _pitch ) + ( (x + num2) * 3 );
          PUT4( _address + offset + 0, 255 );
          PUT4( _address + offset + 1, 0 );
          PUT4( _address + offset + 2, 0 );
        }
        
      }
    }
  }
}