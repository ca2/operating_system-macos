//
//  menu.cpp
//  innate_ui_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/06/26 08:27
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#include "framework.h"
#include "menu.h"


namespace innate_ui_appkit
{


   menu::menu() :
      m_pNSMenu(nullptr),
      m_pMenuTarget(nullptr)
   {
   }


   menu::~menu()
   {
      main_send([this]()
      {
         __destroy_menu();
      });
   }


   void menu::load_menu_from_resource(::i32 iMenuResourceId)
   {
      throw ::interface_only();

   }


   void menu::set_default_menu_item_command_id(::i32 iDefaultMenuItemCommandId)
   {
      main_send([this, iDefaultMenuItemCommandId]()
      {
         __create_menu();
         __set_default_menu_item_command_id(iDefaultMenuItemCommandId);
      });

   }


   void menu::erase_menu_item_by_command_id(::i32 iDefaultMenuItemCommandId)
   {
      main_send([this, iDefaultMenuItemCommandId]()
      {
         __create_menu();
         __erase_menu_item_by_command_id(iDefaultMenuItemCommandId);
      });

   }


   void menu::track_popup_menu(const ::operating_system::window &operatingsystemwindow,
                               const ::function<void(::i32)> &functionOnActionId)
   {
      m_functionOnActionId = functionOnActionId;

      main_send([this]()
      {
         __create_menu();
         __track_popup_menu();
      });

      m_functionOnActionId = {};

   }


   void menu::add_item(const ::scoped_string & scopedstr, int iId)
   {
      ::string str(scopedstr);

      main_send([this, str, iId]()
      {
         __create_menu();
         __add_item(str, iId);
      });

   }


   void menu::add_separator()
   {
      main_send([this]()
      {
         __create_menu();
         __add_separator();
      });

   }


   void menu::on_action(::i32 iActionId)
   {
      if (m_functionOnActionId)
      {
         m_functionOnActionId(iActionId);
      }
   }


} // namespace innate_ui_appkit
