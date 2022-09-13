#include "framework.h"
#include "apex/platform/launcher.h"
#include "shell.h"
#include "interaction_impl.h"


//#include "launcher.h"
//#include "FileSystemEvents/watcher.h"


__FACTORY_EXPORT void aura_apple_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void apex_macos_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void aura_macos_factory(::factory::factory * pfactory)
{
   

   aura_apple_factory(pfactory);
   
   apex_macos_factory(pfactory);

   pfactory->add_factory_item < ::aura_macos::interaction_impl, ::user::interaction_impl > ();

   pfactory->add_factory_item < ::aura_macos::shell, ::user::shell > ();

}



