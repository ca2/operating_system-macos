//
//  appkit.h
//  appkit
//
//  From appkit/appkit.h by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11 07:14
//  <3ThomasBorregaardSørensen!!
//
#pragma once



namespace appkit
{


   class CLASS_DECL_APPKIT appkit :
      virtual public ::particle
   {
   public:
   
      
      appkit();
      
      ~appkit();
   
      ::pointer < ns_image > load_icon(enum_cursor ecursor);
      

   
   };


} // namespace appkit


CLASS_DECL_CORE_GRAPHICS ::appkit::appkit & AppKit();
