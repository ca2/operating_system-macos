//
//  ns_acme_form_impact_controller.h
//  acme_windowing_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 13/05/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


#include "acme/prototype/collection/map.h"
#include "acme/constant/lightui.h"
namespace lightui
{
   class control_helper
      
   {
      public:
      ::comparable_array_base < ::lightui::enum_notification > m_enotificationaBlocked;
      void unblock_notification(::lightui::enum_notification enotification)
      {
         m_enotificationaBlocked.erase(enotification);
      }
      bool is_notification_blocked(::lightui::enum_notification enotification) const
      {
         return m_enotificationaBlocked.contains(enotification);
      }
      void block_notification(::lightui::enum_notification enotification)
      {
         m_enotificationaBlocked.add_unique(enotification);
      }
   };

};



@interface ns_acme_form_impact_controller : NSViewController<NSComboBoxDelegate>
{
   @public
   map_base < ::uptr, ::lightui::control_helper > m_mapControlHelper;
   
   
}

-(bool)isNotificationBlockedForTag:(::uptr)tag andID:(::lightui::enum_notification) enotification;
// Your button interception logic goes here
@end


namespace lightui
{
  
class block_control_notification
{
public:
   ::lightui::control_helper * m_pcontrolhelper;
   ::lightui::enum_notification m_enotificationBlocked;
   block_control_notification(ns_acme_form_impact_controller * pcontroller, ::uptr uTag, ::lightui::enum_notification enotification):
   m_enotificationBlocked(enotification)
   
   {
      m_pcontrolhelper = &pcontroller->m_mapControlHelper[uTag];
      m_pcontrolhelper->block_notification(m_enotificationBlocked);
   }
   ~block_control_notification()
   {
      
      m_pcontrolhelper->unblock_notification(m_enotificationBlocked);
   }
};

};
