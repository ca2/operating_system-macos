#include "framework.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme_dir.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme_path.h"
//#include "copydesk.h"
//#include "file_os_watcher.h"
//#include "acme/node/posix/pipe.h"
//#include "acme/node/apple/process.h"
//#include "acme/node/macos/shell_macos.h"
//#include "acme/node/unix/process.h"


//namespace macos
//{
//
//   factory_exchange::factory_exchange()
//   {
//
//
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
//} // namespace macos


extern "C"
void acme_apple_factory_exchange(::factory_map * pfactorymap);


extern "C"
void acme_macos_factory_exchange(::factory_map * pfactorymap)
{
   
   acme_apple_factory_exchange(pfactorymap);

   pfactorymap->create_factory < ::macos::stdio_file, ::file::text_file > ();
   pfactorymap->create_factory < ::macos::file, ::file::file > ();
   
   pfactorymap->create_factory < ::macos::acme_dir, ::acme_dir > ();
   pfactorymap->create_factory < ::macos::acme_path, ::acme_path > ();

   //create_factory < ::macos::os_context         , ::os_context       > ();
   //create_factory < ::apple::process            , ::process::process > ();
   
  pfactorymap->create_factory < ::posix::pipe               , ::process::pipe    > ();
   
   //create_factory < ::macos::dir_system         , ::dir_system       > ();
   //create_factory < ::macos::file_system        , ::file_system      > ();
   //create_factory < ::macos::dir_context        , ::dir_context      > ();
   //create_factory < ::macos::file_context       , ::file_context     > ();
   //create_factory < ::macos::interaction_impl   , ::user::interaction_impl > ();
   
   //create_factory < ::macos::copydesk           , ::user::copydesk > ();

   //create_factory < ::file::os_watcher          , ::file::watcher    > ();
   //create_factory < ::file::os_watch            , ::file::watch      > ();
   
   
   //create_factory < ::macos::shell   , ::user::shell > ();

}



