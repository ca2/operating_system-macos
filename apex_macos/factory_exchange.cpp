#include "framework.h"
#include "apex/platform/launcher.h"
#include "launcher.h"
#include "FileSystemEvents/watcher.h"


extern "C"
void apex_apple_factory_exchange(::factory_map * pfactorymap);


extern "C"
void acme_macos_factory_exchange(::factory_map * pfactorymap);


extern "C"
void apex_macos_factory_exchange(::factory_map * pfactorymap)
{
   

   apex_apple_factory_exchange(pfactorymap);
   
   acme_macos_factory_exchange(pfactorymap);

   pfactorymap->create_factory < ::apex::macos::node, ::acme::node > ();

   pfactorymap->create_factory < ::FileSystemEvents::watcher, ::file::watcher > ();


}



