#include "framework.h"
#include "media_macos.h"
#include "media_picker.h"


//namespace coreimage_imaging
//{
//
//
//#define new ACME_NEW
//
//
//   factory_exchange::factory_exchange()
//   {
//
//      create_factory < imaging, ::imaging >();
//
//   }
//
//
//   factory_exchange::~factory_exchange()
//   {
//
//   }
//
//
//} // namespace coreimage_imaging

__FACTORY_EXPORT void media_apple_factory(::factory::factory * pfactory);

__FACTORY_EXPORT void media_macos_factory(::factory::factory * pfactory)
{

   media_apple_factory(pfactory);
   

//   pfactory->add_factory_item<::media_ios::media_ios>("media_ios::media_ios");

   
   pfactory->add_factory_item < ::media_macos::media_picker, ::aqua::media_item_picker>();

   pfactory->add_factory_item < ::media_macos::media_macos,  ::media_apple::media_apple >();

   
}



