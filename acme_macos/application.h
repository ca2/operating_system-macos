// Created by camilo on 2023-04-15 19:07 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/operating_system/application.h"


namespace acme_macos
{

   
   class main_window;


   class CLASS_DECL_ACME_MACOS application :
      virtual public ::operating_system::application
   {
   public:

      
      application();
      ~application() override;


      void open_by_module_path(const ::scoped_string & scopedstr) override;

      void post_close() override;
      
      void post_exit() override;
      
      ::string name() override;
      
      ::string main_window_title() override;

      ::raw::count window_count() const override;
      
      virtual ::string __ns_get_bundle_identifier() const;

   };


} // namespace acme_macos



