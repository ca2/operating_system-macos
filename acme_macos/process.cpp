//
//  process.cpp
//  acme_macos
//
//  Created by Camilo Sasuke on 2021-05-14 08:14 BRT <3ThomasBS_!!
//
#include "framework.h"
#include "acme/filesystem/filesystem/acme_dir.h"


bool launch_command(class ::system * psystem, const char * const pszCommand)
{
   
   if (!pszCommand)
   {
      
      return false;
      
   }
   
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
