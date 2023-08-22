// From apex-linux/integration_context.h by camilo on 2023-02-17 20:49 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "node.h"
#include "integration_context.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/url.h"
#include "acme/filesystem/filesystem/acme_file.h"
//#include "apex/networking/http/context.h"
//#include "acme/platform/system.h"


#include "acme/_operating_system.h"


namespace acme_macos
{


   namespace integration
   {


      context::context()
      {

         m_bMsys = false;

      }


      context::~context()
      {


      }


      void context::initialize(::particle *pparticle)
      {

         ::particle::initialize(pparticle);

         m_pmutexLines = acmenode()->create_mutex();

      }


      void context::prepare()
      {

         m_pathBase = m_strName / m_strRelease;
         
         m_pathPlatformConfiguration = m_strPlatform / m_strConfiguration;

         m_pathSource = m_pathFolder / m_pathBase / m_pathPlatformConfiguration / "source";

         acmedirectory()->create(m_pathSource);

      }


      void context::change_to_source_directory(const ::scoped_string & scopedstrRelative)
      {

         ::integration::context::change_to_source_directory(scopedstrRelative);
         
         //acmedirectory()->change_current(m_pathSource2);

      }


      void context::prepare_compile_and_link_environment()
      {

         if (m_pathPrefix.has_char())
         {

            acmedirectory()->create(m_pathPrefix);

         }

      }


      void context::prepare_compilation_script(::string &str)
      {

         // introjection/compiler
         //str.find_replace("%VS_VARS%", m_strContext);
         //str.find_replace("%VS_VARS_PLAT2%", m_strPlat2);
         //str.find_replace("%PROJECT_DIR%", m_pathProjectDir);
         //str.find_replace("%PLATFORM%",m_strPlatform);
         //str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);

         //str.find_replace("%SDK1%",m_strSdk1);



         // programming/compiler
//      str.find_replace("%VS_VARS%", m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%", m_strPlat2);
//      str.find_replace("%PROJECT_DIR%", m_pathProjectDir);
//      str.find_replace("%SDK1%", m_strSdk1);


// script_compiler cl
//      str.find_replace("%VS_VARS%",m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);




      }

      void context::prepare_linking_script(::string &str)
      {

         prepare_compilation_script(str);


//      str.find_replace("%VS_VARS%",m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
//      str.find_replace("%PROJECT_DIR%", m_pathProjectDir);
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);


// script_compiler cl
//      str.find_replace("%VS_VARS%",m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);


// script_compiler cl 2
//      str.find_replace("%VS_VARS%",m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);


// script_compiler cl 3
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      str.find_replace("%LIBPLATFORM%",m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);


// script_compiler cl 4
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      str.find_replace("%LIBPLATFORM%",m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);


      }


      int context::command_system(const ::scoped_string &scopedstrCommand)
      {
         
         information() << scopedstrCommand;

         auto iExitCode = acmenode()->command_system(scopedstrCommand, ::std_inline_log());

         return iExitCode;

      }


      void context::clean()
      {

         {

            string strPath;

            strPath = this->prepare_path(m_pathFolder / m_pathBase / m_pathPlatformConfiguration / "source");

            if (strPath.length() > 20)
            {

               {

                  ::string strCommand = "shopt -s dotglob; rm -Rf " + strPath + "/*";

                  this->bash(strCommand);

               }

            }

         }

         {

            string strPath;

            strPath = this->prepare_path(m_pathPrefix);

            if (strPath.length() > 20)
            {

               {

                  ::string strCommand = "shopt -s dotglob; rm -Rf " + strPath + "/*";

                  this->bash(strCommand);

               }

            }

         }

      }


      void context::download_and_uncompress()
      {

         if (m_pathDownloadURL.case_insensitive_ends(".tar.gz"))
         {

            property_set set;

            acmesystem()->url()->defer_raw_http(set);

            set["disable_common_name_cert_check"] = true;

            //auto path = m_pathFolder / m_path / (m_strName + ".tar.gz");

            auto pmemoryFileTarGz = create_memory_file();

            auto url = m_pathDownloadURL;

            acmesystem()->http_download(pmemoryFileTarGz, url, set);

            //auto pathTar = m_pathFolder / m_path / (m_strName + ".tar");

            pmemoryFileTarGz->seek_to_begin();

            auto pmemoryFileTar = create_memory_file();

            acmesystem()->uncompress(pmemoryFileTar, pmemoryFileTarGz, "zlib");

            pmemoryFileTar->seek_to_begin();

            this->untar(m_pathFolder / m_pathBase / m_pathPlatformConfiguration, pmemoryFileTar, 1);

         }

      }


      void context::git_clone()
      {
         
         information() << "Current Directory: " << acmedirectory()->get_current();

         command_system("git clone " + m_pathDownloadURL + " .");

      }


      ::i32 context::bash(const ::scoped_string &scopedstr)
      {

         string strEscaped = scopedstr;

         ::string strCommand;

//         if (m_bMsys)
//         {
//
//            strCommand = "\"C:\\msys64\\usr\\bin\\bash.exe\" -c \'" + strEscaped + "\'";
//
//         }
//         else
         {
            
            strEscaped.find_replace("\"", "\\\"");
            
#ifdef __APPLE__
            
            if(strEscaped.contains("shopt"))
            {
               
               strCommand = "/bin/bash -l -o braceexpand -o hashall -o interactive-comments -c \"" + strEscaped + "\"";
               
            }
            else
            {
               
               strCommand = "/bin/zsh -l -o braceexpand -o hashall -o interactive_comments -c \"" + strEscaped + "\"";

               
            }
            
#else
            
            strCommand = "/bin/bash -l -o braceexpand -o hashall -o interactive-comments -c \"" + strEscaped + "\"";
            
#endif
            
            //strCommand = "/bin/bash -c " + strEscaped;

            //information() << strCommand;
            
            
         }
//         int iExitCode1 = command_system("/bin/bash -c \'echo $PATH\'");

         //

         int iExitCode = command_system(strCommand);

         ///command_system("cmd.exe -c \"C:\\msys64\\msys2_shell.cmd\" \"" + strEscaped + "\"");

         return iExitCode;

      }


      ::i32 context::zsh(const ::scoped_string &scopedstr)
      {

         string strEscaped = scopedstr;

         ::string strCommand;

   //         if (m_bMsys)
   //         {
   //
   //            strCommand = "\"C:\\msys64\\usr\\bin\\bash.exe\" -c \'" + strEscaped + "\'";
   //
   //         }
   //         else
         {
            
            strEscaped.find_replace("\"", "\\\"");
            

            strCommand = "/bin/zsh -o braceexpand -o hashall -o interactive_comments -l -c \"" + strEscaped + "\"";
            
            //strCommand = "/bin/bash -c " + strEscaped;

            //information() << strCommand;
            
            
         }
   //         int iExitCode1 = command_system("/bin/bash -c \'echo $PATH\'");

         //

         int iExitCode = command_system(strCommand);

         ///command_system("cmd.exe -c \"C:\\msys64\\msys2_shell.cmd\" \"" + strEscaped + "\"");

         return iExitCode;

      }

   
      ::string context::prepare_path(const ::file::path &path)
      {

         return path;

      }


   } // namespace integration


   void node::integration_factory()
   {

      acmesystem()->m_psubsystem->m_pfactory->add_factory_item<::acme_macos::integration::context, ::integration::context>();

   }


} // namespace apex_macos
