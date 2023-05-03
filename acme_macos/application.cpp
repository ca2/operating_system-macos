// Created by camilo on 2023-04-15 19:17 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#include "axuielement.h"
#include "acme/exception/interface_only.h"


void show_accessibility_preferences_page();


namespace acme_macos
{


   application::application()
   {

      m_processidentifier = -1;
      
      if(!AXIsProcessTrusted())
      {
         
         show_accessibility_preferences_page();
         
      }

   }

   
   application::~application()
   {


   }

   
   void application::open_by_module_path(const ::scoped_string & scopedstr)
   {

      auto processesidentifiers = acmenode()->module_path_processes_identifiers(scopedstr, false);
      
      if(processesidentifiers.has_element())
      {
         
         m_processidentifier = processesidentifiers.first();
         
      }

   }


   void application::post_close()
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


   ::count application::window_count() const
   {
      
      ::string strTitle;

      auto axuielement = AXUIElementCreateApplication((pid_t) m_processidentifier);
      
      ::count c = 0;
      
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



