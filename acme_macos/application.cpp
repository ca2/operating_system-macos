// Created by camilo on 2023-04-15 19:17 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#include "axuielement.h"
#include "acme/exception/interface_only.h"


void show_accessibility_preferences_page();


bool ns_running_application_hide_by_bundle_identifier(const char * pszBundleIdentifier);
bool ns_running_application_terminate_by_bundle_identifier(const char * pszBundleIdentifier);


namespace acme_macos
{


   application::application()
   {

      m_processidentifier = -1;
      
   }

   
   application::~application()
   {


   }

   
   void application::open_by_module_path(const ::scoped_string & scopedstr)
   {

      auto processesidentifiers = node()->module_path_processes_identifiers(scopedstr, false);
      
      if(processesidentifiers.has_element())
      {
         
         m_processidentifier = processesidentifiers.first();
         
         if(!AXIsProcessTrusted())
         {
            
            show_accessibility_preferences_page();
            
         }

      }

   }


   ::string application::__ns_get_bundle_identifier() const
   {
      
      if(m_strRepos.has_char() && m_strApp.has_char())
      {
         
         return m_strRepos + "." + m_strApp;
         
      }
      
      return "";
   
   }


   void application::post_close()
   {
      
      if(m_processidentifier > 0)
      {
         
         
         auto axuielement = AXUIElementCreateApplication((pid_t) m_processidentifier);
         
         try
         {
            
            axuielement_post_close(axuielement);
            
         }
         catch (...)
         {
            
         }
         
         CFRelease(axuielement);
         
      }
      else if(m_strRepos.has_char() && m_strApp.has_char())
      {
         
         ::string strBundleIdentifier = __ns_get_bundle_identifier();
         
         ns_running_application_hide_by_bundle_identifier(strBundleIdentifier);
         
      }
      else
      {
      
         throw ::exception(error_wrong_state);
         
      }

   }

   
   void application::post_exit()
   {
      
      if(m_processidentifier > 0)
      {
         
         ::operating_system::application::post_exit();
         
      }
      else if(m_strRepos.has_char() && m_strApp.has_char())
      {
         
         ::string strBundleIdentifier = __ns_get_bundle_identifier();
         
         ns_running_application_terminate_by_bundle_identifier(strBundleIdentifier);
         
      }
      else
      {
      
         throw ::exception(error_wrong_state);
         
      }
      
   }


   ::string application::name()
   {
      
      ::string strTitle;

      auto axuielement = AXUIElementCreateApplication((pid_t) m_processidentifier);
      
      try
      {
      
         strTitle = axuielement_application_name(axuielement);

      }
      catch (...)
      {
      
      }
      
      CFRelease(axuielement);
      
      return strTitle;

   }


   ::string application::main_window_title()
   {
      
      ::string strTitle;

      auto axuielement = AXUIElementCreateApplication((pid_t) m_processidentifier);
      
      try
      {
      
         strTitle = axuielement_first_window_title(axuielement);

      }
      catch (...)
      {
      
      }
      
      CFRelease(axuielement);
      
      return strTitle;

   }


   ::collection::collection::count application::window_count() const
   {
      
      ::string strTitle;

      auto axuielement = AXUIElementCreateApplication((pid_t) m_processidentifier);
      
      ::collection::collection::count c = 0;
      
      try
      {
      
         c = axuielement_application_window_count(axuielement);

      }
      catch (...)
      {
      
      }
      
      CFRelease(axuielement);
      
      return c;

   }


} // namespace acme_macos



