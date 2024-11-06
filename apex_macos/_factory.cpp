#include "framework.h"
#include "apex/platform/launcher.h"
#include "launcher.h"
//#include "os_context.h"
#include "interprocess.h"
#include "node.h"
//#include "FileSystemEvents/watcher.h"


extern "C"
void apex_apple_factory(::factory::factory * pfactory);


extern "C"
void acme_macos_factory(::factory::factory * pfactory);


extern "C"
void apex_macos_factory(::factory::factory * pfactory)
{
   

   apex_apple_factory(pfactory);
   
   acme_macos_factory(pfactory);

   pfactory->add_factory_item < ::apex_macos::node, ::platform::node > ();


//   pfactory->add_factory_item < ::apex_macos::os_context, ::os_context > ();
   
   pfactory->add_factory_item < ::apex_macos::interprocess_base, ::interprocess::base >();
   pfactory->add_factory_item < ::apex_macos::interprocess_target, ::interprocess::target >();
   pfactory->add_factory_item < ::apex_macos::interprocess_caller, ::interprocess::caller >();
//   pfactory->add_factory_item < ::macos::launcher, ::launcher > ();
//   pfactory->add_factory_item < ::macos::shell_launcher, ::shell_launcher > ();


}



