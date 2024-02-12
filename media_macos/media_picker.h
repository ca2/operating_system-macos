//
//  media_picker.hpp
//  media_ios
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 10/02/24.
//
#pragma once


#include "macos_media_picker.h"
#include "aqua/multimedia/media_item_picker.h"


namespace media_macos
{


   class CLASS_DECL_MEDIA_IOS media_picker :
      virtual public ::aqua::media_item_picker,
      virtual public ::macos_media_picker
   {
   public:
      
      
      ::pointer < ::windowing_macos::window >     m_pmacoswindow;

      
      void set_windowing_window(::windowing::window * pwindow) override;
      void pick_media(const char * pszMediaType) override;
      
      void macos_media_picker_did_pick_platform_media_item(platform_media_item_t * papplemedia) override;

      
      // virtual void ios_media_picker_pick_media(const char * pszMediaType);
      // virtual void ios_window_did_pick_platform_media_item(platform_media_item_t * papplemedia) = 0;


   };


} // namespace media_macos



