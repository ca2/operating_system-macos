//
//  dir_system.cpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 28/02/20.
//
#include "framework.h"

//#include "apex/os/_.h"
//#include "apex/os/_os.h"
//#include "apex/xml/_.h"
//#include "_.h"

char * ns_user_local_desktop_folder();
char * ns_user_local_documents_folder();
char * ns_user_local_downloads_folder();
char * ns_user_local_music_folder();
char * ns_user_local_image_folder();
char * ns_user_local_video_folder();


namespace apex_macos
{


   dir_system::dir_system()
   {


   }




   void dir_system::initialize(::particle * pparticle)
   {
      
      //auto estatus =
      
      ::dir_system::initialize(pparticle);
      
//      if(!estatus)
//      {
//         
//         return estatus;
//         
//      }
//      
//      return estatus;

   }


   void dir_system::init_system()
   {

      //auto estatus =
      
      ::dir_system::init_system();
      
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      auto psystem= m_psystem->m_papexsystem;
      
//      ::file::path pathModule = psystem->m_pfilesystem->m_pathModule;
      
      m_pathHome = getenv("HOME");
      
//      auto pathCa2 = pathModule - 2;
//
//      ::str::case_insensitive_ends_eat(pathCa2, ".app");
//
//      m_pathCa2 = pathCa2;
      
      m_pathCa2Config = m_pathHome / "Library/Application Support/ca2";

      //return estatus;
      
   }


} // namespace apex_macos

