// Created by camilo on 2024-09-13 00:36 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/still.h"
//#include "__impact.h"
//#include "__image_view.h"
//#include "__text_field.h"
//#include <gtk/gtk.h>

namespace innate_ui_appkit
{

class icon;


   class CLASS_DECL_INNATE_UI_APPKIT still :
      virtual public ::innate_ui::still
   {
   public:

      //GtkWidget * m_pgtkwidget;
      
      ::pointer <::innate_ui_appkit::__image_view >   m_pimageviewOwned;
      ::pointer <::innate_ui_appkit::__text_field >   m_ptextfieldOwned;
      ::pointer <::innate_ui::still >                 m_pstillOwned;
      //virtual public ,

      bool m_bIcon;

      still();
      ~still() override;

      virtual void __create_icon();
      virtual void __create_still();

      void create_child(window * pwindowParent) override;
      void create_icon_still(::innate_ui::window * pwindowParent) override;

      void set_position(const ::i32_point & point) override;
      void set_size(const ::i32_size & size) override;
      void set_icon(::innate_ui::icon * picon) override;
      //void set_text(const ::scoped_string & scopedstr) override;
      //virtual void __set_icon(::innate_ui_appkit::icon * picon);
      //void __set_text(const char * pszText) override;
      ::i32 layout_width() override;
      ::i32 layout_height() override;
      void set_text(const ::scoped_string & scopedstr) override;
      void set_font_size(::f64 dSizeEm) override;
      void set_font_weight(::i32 iWeight) override;

      
   };


} // namespace innate_ui_appkit




