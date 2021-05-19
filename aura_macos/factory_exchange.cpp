#include "framework.h"
#include "apex/platform/launcher.h"
//#include "launcher.h"
//#include "FileSystemEvents/watcher.h"


extern "C"
void aura_apple_factory_exchange(::factory_map * pfactorymap);


extern "C"
void apex_macos_factory_exchange(::factory_map * pfactorymap);


extern "C"
void apex_macos_factory_exchange(::factory_map * pfactorymap)
{
   

   aura_apple_factory_exchange(pfactorymap);
   
   apex_macos_factory_exchange(pfactorymap);

   pfactorymap->create_factory < ::macos::interaction_impl, ::user::interaction_impl > ();


}



