//
//  process.cpp
//  acme_macos
//
//  Created by Camilo Sasuke on 2021-05-14 08:14 BRT <3ThomasBS_!!
//
#include "framework.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include <spawn.h>

namespace acme
{


   namespace macos
   {

   
      bool node::_launch_command(const char * const pszCommand)
      {
         
         if (!pszCommand)
         {
            
            return false;
            
         }
         
         auto psystem = m_psystem;
         
         auto pacmedir = psystem->m_pacmedir;
         
         string strParams;
         
         string strCommand(pszCommand);
         
         strCommand.replace("\"", "\\\"");
         
         strParams.Format("-c \"screen -d -m %s\"", strCommand.c_str());
         
         auto estatus = call_async("/bin/bash", strParams, pacmedir->home(), e_display_none, false);
         
         if(!estatus)
         {
            
            return estatus;
            
         }
         
         return estatus;
         
      }

      
      ::e_status node::create_process(const char * pszCommandLine, u32 * pprocessId)
      {

         string_array stra;
         
         stra = get_c_args_for_c(pszCommandLine);

         char * argv[1024 + 1];

         int argc = 0;

         for(auto & str : stra)
         {

            argv[argc] = (char *) str.c_str();

            argc++;

         }

         argv[argc] = nullptr;
         
         auto envp = m_psystem->m_envp;

         pid_t pid = 0;

         int status = posix_spawn(&pid, argv[0], nullptr, nullptr, argv, envp);

         int iError = errno;

         char * pszError = strerror(iError);
         
         if(pszError)
         {
         
            ::output_debug_string(pszError);
            
         }

         if (status == 0)
         {

            if(pprocessId != nullptr)
            {

               *pprocessId = pid;

            }

            return 1;

         }
         else
         {

            return 0;

         }

      }


   } // namespace macos


} // namespace acme



