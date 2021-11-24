#include "framework.h"
#include "apex/platform/launcher.h"
#include "launcher.h"
#include "FileSystemEvents/watcher.h"


extern "C"
void apex_apple_factory(::factory::factory * pfactory);


extern "C"
void acme_macos_factory(::factory::factory * pfactory);


extern "C"
void apex_macos_factory(::factory::factory * pfactory)
{
   

   apex_apple_factory(pfactory);
   
   acme_macos_factory(pfactory);

   pfactory->add_factory_item < ::apex::macos::node, ::acme::node > ();

   pfactory->add_factory_item < ::FileSystemEvents::watcher, ::file::watcher > ();

   pfactory->add_factory_item < ::FileSystemEvents::watch, ::file::watch > ();

   pfactory->add_factory_item < ::macos::file_context, ::file_context > ();
   pfactory->add_factory_item < ::macos::dir_context, ::dir_context > ();
   pfactory->add_factory_item < ::macos::file_system, ::file_system > ();
   pfactory->add_factory_item < ::macos::dir_system, ::dir_system > ();

   pfactory->add_factory_item < ::macos::os_context, ::os_context > ();
   
   pfactory->add_factory_item < ::macos::interprocess_communication_base, ::interprocess_communication::base >();
   pfactory->add_factory_item < ::macos::interprocess_communication_rx, ::interprocess_communication::rx >();
   pfactory->add_factory_item < ::macos::interprocess_communication_tx, ::interprocess_communication::tx >();
//   pfactory->add_factory_item < ::macos::launcher, ::launcher > ();
//   pfactory->add_factory_item < ::macos::shell_launcher, ::shell_launcher > ();


}



