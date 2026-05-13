#include "framework.h"
#include "apex/platform/launcher.h"
//#include "launcher.h"
//#include "FileSystemEvents/watcher.h"


__FACTORY_EXCHANGE void aura_apple_factory(::factory::factory * pfactory);


__FACTORY_EXCHANGE void apex_macos_factory(::factory::factory * pfactory);


__FACTORY_EXCHANGE void aura_macos_factory(::factory::factory * pfactory)
{

   aura_apple_factory(pfactory);
   
   apex_macos_factory(pfactory);

   pfactory->add_factory_item < ::macos::interaction_impl, ::user::interaction_impl > ();

   pfactory->add_factory_item < ::macos::shell, ::user::shell > ();

}



