//
//  main_window.hpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2023-05-02 22:44:44.
//
#pragma once


namespace acme_macos
{


   class CLASS_DECL_ACME main_window :
      virtual public ::operating_system::main_window
   {
   public:

      
      AXUIElementRef m_axuielement;

      main_window();
      ~main_window() override;


      virtual void from_application(application * papplication);

      virtual void post_close();

      virtual ::string get_window_text(const ::iptr_array & idPath);
      virtual ::string indexed_get_window_text(const ::iptr_array & idPath);


   };


} // namespace operating_system




