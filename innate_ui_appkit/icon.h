// Created by camilo on 2024-09-13 07:18 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/icon.h"
//#include <gtk/gtk.h>
//#include <QPixmap>


namespace innate_ui_appkit
{


   class CLASS_DECL_INNATE_UI_APPKIT icon :
      virtual public ::innate_ui::icon
   {
   public:


      //GdkPaintable *  m_pgdkpaintable;
      //QPixmap *m_pqpixmap;
      void * m_pNSImage;
      icon();
      ~icon() override;


      void _create() override;
      virtual void __create_icon();
      
      void __icon_release();

   };


} // namespace innate_ui_appkit



