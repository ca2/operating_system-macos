// Create on 2021-03-22 09:12 <3ThomasBS_ // at Linux(Question)
// Recreated on 2021-05-16 15:07 <3ThomasBS_ // for macOS
#include "framework.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme_path.h"


string apple_app_module_path();
enum_status ns_create_alias(const char * pszLink, const char * pszSource);
enum_status ns_symbolic_link_destination(char ** ppszDestination, const char * pszLink);

namespace macos
{

   
   acme_path::acme_path()
   {

      m_pplatformpath = this;

   }


   acme_path::~acme_path()
   {


   }


//   ::file::path acme_path::app_module()
//   {
//
//      ::file::path path = apple_app_module_path();
//
//      return path;
//
//   }
//


   ::e_status acme_path::create_symbolic_link(const char * pszLink, const char * pszSource)
   {
      
      if(!ns_create_alias(pszLink, pszSource))
      {
         
         return error_failed;
         
      }
      
      return success;
      
   }


   ::e_status acme_path::is_symbolic_link(const char * pszLink)
   {
      
      auto estatus = ns_symbolic_link_destination(nullptr, pszLink);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      return estatus;
      
   }


   ::file::path acme_path::symbolic_link_destination(const char * pszLink)
   {
      
      string strDestination;
      
      char * pszDestination = nullptr;
      
      auto estatus = ns_symbolic_link_destination(&pszDestination, pszLink);
      
      strDestination = ::str::from_strdup(pszDestination);
      
      if(!estatus)
      {
         
         return "";
         
      }
      
      return strDestination;
      
   }


} // namespace macos



