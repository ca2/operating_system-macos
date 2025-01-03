//
//  __impact.h
//  innate_ui_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-09-20 16:46
//

// Created by camilo on 2024-09-12 22:34 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/window.h"
//#include "acme/_operating_system.h"
//#include "acme/operating_system/windows/window.h"
//#include <gtk/gtk.h>
//#include <QMainWindow>

namespace innate_ui_appkit
{

   class innate_ui;

   class CLASS_DECL_INNATE_UI_APPKIT __impact :
      virtual public ::innate_ui::window  //,
      //virtual public ::windows::window
   {
   public:

#ifdef __OBJC__
      NSView * m_pnsview;
#else
      void * m_pNSView;
#endif
      //QWidget * m_pqwidget;
      //GtkWidget * m_pgtkwidget;
      //HWND m_hwnd;
      //HMENU m_hmenuSystem;
      //int m_iChildIdSeed;
      //int m_iCreateStyle;


      __impact();
      ~__impact() override;

      void set_text(const ::scoped_string & scopedstr) override;

      //LONG_PTR _get_style();

//      void _post(const ::procedure & procedure);
      //virtual const char * __get_class_name();
      //virtual wstring _get_class_name();
      //virtual ATOM _register_class();
      //virtual void _get_class(WNDCLASSEXW & wcex);
      virtual void _create();
      virtual void _create_child(window * pwindow);

      void create() override;
      void create_child(::innate_ui::window * pwindow) override;
      void destroy_window() override;
      void center() override;

      void show() override;
      void hide() override;

      void set_position(const ::int_point & point) override;
      void set_size(const ::int_size & size) override;
      void adjust_for_client_size(const ::int_size & size) override;

      
      
      ::innate_ui_appkit::innate_ui * innate_ui();

      //virtual ::pointer < window > _get_child_with_id(int iId);
      //virtual LRESULT _window_procedure(UINT message, WPARAM wparam, LPARAM lparam);

      //virtual bool _on_command();

      //virtual int _get_id();

      void defer_show_system_menu(::user::mouse * pmouse) override;

      virtual void __show();
      
      virtual void __set_text(const char * psz);
      virtual void __set_position(int x, int y);
      virtual void __set_size(int cx, int cy);
      void __impact_release();
   };


} // namespace innate_ui_appkit




