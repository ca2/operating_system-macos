//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"


void os_post_quit();


void ns_launch_app(const char * psz, const char ** argv, int iFlags);


void ansios_sigchld_handler(int sig);


void apex_application_run(const char * pszAppName, const char * pszProgName);


namespace apex_macos
{


      node::node()
      {

         m_pApexPlatform = this;

      }


      node::~node()
      {

      }

   
   int node::node_init_check(int * pi, char *** ppz)
   {
   
      return 0;
   
   }

   
      string node::app_id_to_executable_name(const string & strAppId)
      {
         
         string strName = app_id_to_app_name(strAppId);

         return "_" + strName;

      }


} // namespace apex_macos


