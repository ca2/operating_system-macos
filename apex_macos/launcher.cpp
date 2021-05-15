#include "framework.h"
#include "apex/platform/launcher.h"
#include "launcher.h"
#undef USE_MISC


namespace macos
{


   ::e_status launcher::start()
   {

      auto estatus = ensure_executable();
      
      if(!estatus)
      {
         
         return estatus;
         
      }

      string strPath(get_executable_path());
      string strDir(dir::name(strPath));
       

       /*vsstring strPath

      SHELLEXECUTEINFOA infoa;

      __memset(&infoa, 0, sizeof(infoa));

      infoa.cbSize         = sizeof(infoa);
      infoa.pFile         = strPath;

      infoa.pDirectory    = strDir;*/

      execlp(strPath, strPath, (char *) 0);

      return estatus;

   }


} // namespace macos



