//
//  Framebuffer.h
//  MKPi
//
//  Created by Maurus Kühne on 06.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#ifndef __MKPi__Framebuffer__
#define __MKPi__Framebuffer__

#include "Memory.h"
#include "Mailbox.h"

struct Colour{
  uint8_t r;
  uint8_t g;
  uint8_t b;
};
namespace HIL {
  
  class Framebuffer {
  private:
    uint32_t _address;
    uint32_t _bufferSize;
    uint32_t _xSize;
    uint32_t _ySize;
    uint32_t _pitch;
    uint32_t _depth;
    Mailbox _mailbox;
    
  public:
    Framebuffer();
    bool initialize();
    void put_pixel_RGB24(uint32_t x, uint32_t y, Colour colour);
    void DrawCharacter(int x, int y, char c, uint32_t color);
  };
}


#endif /* defined(__MKPi__Framebuffer__) */
