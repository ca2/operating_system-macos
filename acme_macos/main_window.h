//
//  main_window.hpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2023-05-02 22:44:44.
//
#pragma once


#include "acme/operating_system/main_window.h"


#include <Carbon/Carbon.h>


namespace acme_macos
{


   class CLASS_DECL_ACME main_window :
      virtual public ::operating_system::main_window
   {
   public:

      
      AXUIElementRef m_axuielement;

      main_window();
      ~main_window() override;


      void from_application(::operating_system::application * papplication) override;

      virtual void post_close() override;

      virtual ::string get_window_text(const ::iptr_array & idPath) override;
      virtual ::string indexed_get_window_text(const ::iptr_array & idPath) override;


   };


} // namespace operating_system




