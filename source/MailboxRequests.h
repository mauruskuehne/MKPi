//
//  MailboxRequests.h
//  MKPi
//
//  Created by Maurus Kühne on 06.01.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#ifndef MKPi_MailboxRequests_h
#define MKPi_MailboxRequests_h

namespace HIL {
  
  
  struct mb_pwr_set_state
  {
    const uint32_t requestSize = sizeof(mb_pwr_set_state);
    uint32_t responseCode = 0;
    const uint32_t tag = 0x00028001;
    const uint32_t responseSize = 2 * 4;
    uint32_t responseIndicator = 0;
    uint32_t deviceId = 0;
    uint32_t state = 0;
    const uint32_t endTag = 0;
  } __attribute__ ((aligned(16)));
  
  
  /*************************
   Framebuffer
   *************************/
  
  struct mb_fb_get_physical_size {
    const uint32_t requestSize = sizeof(mb_fb_get_physical_size);
    uint32_t responseCode = 0;
    const uint32_t tag = 0x00040003;
    const uint32_t responseSize = 2 * 4;
    uint32_t responseIndicator = 0;
    uint32_t width = 0;
    uint32_t height = 0;
    const uint32_t endTag = 0;
    
  } __attribute__ ((aligned(16)));
  
  struct mb_fb_get_pitch {
    const uint32_t requestSize = sizeof(mb_fb_get_pitch);
    uint32_t responseCode = 0;
    const uint32_t tag = 0x00040008;
    const uint32_t responseSize = 1 * 4;
    uint32_t responseIndicator = 0;
    uint32_t pitch = 0;
    const uint32_t endTag = 0;
    
  } __attribute__ ((aligned(16)));
  
  //beacause of some unknown reasen these 4 tags have to be sent together...
  struct mb_fb_alloc_buffer {
    uint32_t request_size = sizeof(mb_fb_alloc_buffer);
    uint32_t request_indicator = 0;
    
    //first tag
    const uint32_t set_physical_width_tag = 0x00048003;
    const uint32_t tag1_value_length = 2 * 4;
    uint32_t tag1_req_indicator_val_length = 2 * 4;
    
    uint32_t physical_width = 0;
    uint32_t physical_height = 0;
    
    //second tag
    const uint32_t set_virtual_width_tag = 0x00048004;
    const uint32_t tag2_value_length = 2 * 4;
    uint32_t tag2_req_indicator_val_length = 2 * 4;
    
    uint32_t virtual_width = 0;
    uint32_t virtual_height = 0;
    
    //third tag
    const uint32_t set_depth_tag = 0x00048005;
    const uint32_t tag3_value_length = 1 * 4;
    uint32_t tag3_req_indicator_val_length = 1 * 4;
    
    uint32_t depth = 0;
    
    //fourth tag
    const uint32_t alloc_buffer_tag = 0x00040001;
    const uint32_t tag4_value_length = 2 * 4;
    uint32_t tag4_req_indicator_val_length = 2 * 4;
    
    union {
      uint32_t alignment;
      
      struct {
        uint32_t address;
        uint32_t size;
      } response;
      
    } bufferInfo;
    
    const uint32_t _end_tag = 0;
    
  } __attribute__ ((aligned(16)));
  

}
#endif
