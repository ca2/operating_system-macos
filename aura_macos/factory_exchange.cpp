#include "framework.h"
#include "apex/platform/launcher.h"
//#include "launcher.h"
//#include "FileSystemEvents/watcher.h"


extern "C"
void aura_apple_factory_exchange(::factory::factory * pfactory);


extern "C"
void apex_macos_factory_exchange(::factory::factory * pfactory);


extern "C"
void aura_macos_factory_exchange(::factory::factory * pfactory)
{
   

   aura_apple_factory_exchange(pfactory);
   
   apex_macos_factory_exchange(pfactory);

   pfactory->add_factory_item < ::macos::interaction_impl, ::user::interaction_impl > ();

   pfactory->add_factory_item < ::macos::shell, ::user::shell > ();

}



