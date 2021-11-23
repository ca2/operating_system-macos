#include "framework.h"
#include "apex/platform/launcher.h"
//#include "launcher.h"
//#include "FileSystemEvents/watcher.h"


__FACTORY_EXPORT void aura_apple_factory(::factory_map * pfactorymap);


__FACTORY_EXPORT void apex_macos_factory(::factory_map * pfactorymap);


__FACTORY_EXPORT void aura_macos_factory(::factory_map * pfactorymap)
{
   

   aura_apple_factory(pfactorymap);
   
   apex_macos_factory(pfactorymap);

   pfactorymap->create_factory < ::macos::interaction_impl, ::user::interaction_impl > ();

   pfactorymap->create_factory < ::macos::shell, ::user::shell > ();

}



