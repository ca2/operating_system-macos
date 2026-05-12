//
// Created by camilo on 2026-04-08 18:41 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace innate_subsystem_macos
{


   class CLASS_DECL_INNATE_SUBSYSTEM_MACOS WindowCache :
   virtual public ::particle
   {
   public:

      //HWND m_hwnd;

      virtual void initialize_window_cache(Window * pwindow);

   };


} // namespace innate_subsystem_macos



