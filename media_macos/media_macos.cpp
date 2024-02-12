//
//  media_ios.cpp
//  media_ios::media_ios
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-10 00:15 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "media_macos.h"


//void * new_iosAudioPickerViewController_as_UIViewController();


namespace media_macos
{


   media_macos::media_macos()
   {
      
      
   }


   media_macos::~media_macos()
   {
      
   }


   // "iosAudioPickerViewController as UIViewController"
   void * media_macos::new_object(const char * psz)
   {
      
      if(!strcmp(psz, "iosAudioPickerViewController as UIViewController"))
      {
         
   //      return new_iosAudioPickerViewController_as_UIViewController();
         
      }
      
      
      throw ::exception(error_no_factory);
      
      return nullptr;
      
   }


} // namespace media_macos




