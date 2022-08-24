#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif
#include "apex/platform/launcher.h"
#include "launcher.h"
#undef USE_MISC


namespace apex_macos
{


   void launcher::start()
   {

      auto estatus = ensure_executable();
      
      if(!estatus)
      {
         
         //return estatus;
         
         throw exception(error_wrong_state);
         
      }

      string strPath(get_executable_path());
      string strDir(file_path_folder(strPath));
       

       /*vsstring strPath

      SHELLEXECUTEINFOA infoa;

      __memset(&infoa, 0, sizeof(infoa));

      infoa.cbSize         = sizeof(infoa);
      infoa.pFile         = strPath;

      infoa.pDirectory    = strDir;*/

      execlp(strPath, strPath, (char *) 0);

      //return estatus;

   }


} // namespace apex_macos



