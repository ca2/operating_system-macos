#include "framework.h"
#include "apex/platform/launcher.h"
#include "launcher.h"
#include "FileSystemEvents/watcher.h"


__FACTORY_EXPORT void apex_apple_factory(::factory_map * pfactorymap);


__FACTORY_EXPORT void acme_macos_factory(::factory_map * pfactorymap);


__FACTORY_EXPORT void apex_macos_factory(::factory_map * pfactorymap)
{
   

   apex_apple_factory(pfactorymap);
   
   acme_macos_factory(pfactorymap);

   pfactorymap->create_factory < ::apex::macos::node, ::acme::node > ();

   pfactorymap->create_factory < ::FileSystemEvents::watcher, ::file::watcher > ();

   pfactorymap->create_factory < ::FileSystemEvents::watch, ::file::watch > ();

   pfactorymap->create_factory < ::macos::file_context, ::file_context > ();
   pfactorymap->create_factory < ::macos::dir_context, ::dir_context > ();
   pfactorymap->create_factory < ::macos::file_system, ::file_system > ();
   pfactorymap->create_factory < ::macos::dir_system, ::dir_system > ();

   pfactorymap->create_factory < ::macos::os_context, ::os_context > ();
   
   pfactorymap->create_factory < ::macos::interprocess_communication_base, ::interprocess_communication::base >();
   pfactorymap->create_factory < ::macos::interprocess_communication_rx, ::interprocess_communication::rx >();
   pfactorymap->create_factory < ::macos::interprocess_communication_tx, ::interprocess_communication::tx >();
//   pfactorymap->create_factory < ::macos::launcher, ::launcher > ();
//   pfactorymap->create_factory < ::macos::shell_launcher, ::shell_launcher > ();


}



