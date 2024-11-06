//
//  macos_media_picker.mm
//  media_ios
//
//  Created as ios_media_picker by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-10 01:37 <3ThomasBorregaardSorensen!!
//  Refactored as macos_media_picker by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-11 18:44 <3ThomasBorregaardSorensen!!
//

#include "macos_media_picker.h"
#include "windowing_macos/macos/macos_window.h"
#include "macosMediaPickerViewController.h"


void ns_main_post(dispatch_block_t block);


macos_media_picker::macos_media_picker()
{
 
   m_pmacoscontroller = [ [ macosMediaPickerViewController alloc ] initWithMediaPicker: this];
   
}


void macos_media_picker::macos_media_picker_pick_media(const char * pszMediaType, macos_window * pmacoswindow)
{
   
   ns_main_post(^{
      [ m_pmacoscontroller pickMedia : pszMediaType window:pmacoswindow->m_pnswindow ];
      
   });
   
}
