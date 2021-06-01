//
//  cursor.hpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 28/05/21 00:26 BRT <3ThomasBS_!!
//
#pragma once



namespace windowing_macos
{


   class CLASS_DECL_WINDOWING_MACOS cursor :
      virtual public ::windowing::cursor
   {
   public:

      
      void *    m_pNSCursor;
      
     
      cursor();
      ~cursor() override;
      
      
      ::e_status load_default_cursor(enum_cursor ecursor) override;
      
      ::e_status create_from_image(const ::image * pimage, int xHotSpot, int yHotSpot) override;

      
   };


} // namespace windowing_macos




