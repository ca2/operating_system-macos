//
//  menu.h
//  innate_ui_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/06/26 08:26
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#pragma once


#include "acme/operating_system/window.h"
#include "apex/innate_ui/menu.h"



namespace innate_ui_appkit
{


   class CLASS_DECL_INNATE_UI_APPKIT menu : virtual public ::innate_ui::menu
   {
   public:


      void * m_pNSMenu;
      void * m_pMenuTarget;
      ::function<void(::i32)> m_functionOnActionId;

      menu();
      ~menu() override;


      void load_menu_from_resource(::i32 iMenuResourceId) override;

      void set_default_menu_item_command_id(::i32 iDefaultMenuItemCommandId) override;

      void erase_menu_item_by_command_id(::i32 iDefaultMenuItemCommandId) override;


      void track_popup_menu(const ::operating_system::window & operatingsystemwindow, const ::function<void(::i32)> &functionOnActionId) override;

      void add_item(const ::scoped_string & scopedstr, int iId) override;
      void add_separator() override;

      void on_action(::i32 iActionId);

      void __create_menu();
      void __destroy_menu();
      void __set_default_menu_item_command_id(::i32 iDefaultMenuItemCommandId);
      void __erase_menu_item_by_command_id(::i32 iDefaultMenuItemCommandId);
      void __track_popup_menu();
      void __add_item(const ::scoped_string & scopedstr, int iId);
      void __add_separator();


   };


} // namespace innate_ui_appkit
