//
// Created by camilo on 2026-04-06 10:58 <3ThomasBorregaardSørensen!!
//

#pragma once


#include "subsystem_macos/platform/subsystem.h"
#include "innate_subsystem/platform/subsystem.h"

namespace innate_subsystem_macos
{


   class CLASS_DECL_INNATE_SUBSYSTEM_MACOS subsystem :
      virtual public ::subsystem_macos::subsystem,
      virtual public ::innate_subsystem::subsystem
   {
   public:



      subsystem();
      ~subsystem() override;





       ::enum_dialog_result message_box(
       const ::user_interaction_sink & userinteractionsink,
         const ::scoped_string & scopedstrMessage,
         const ::scoped_string & scopedstrCaption,
         const ::user::e_message_box & emessagebox) override;
#ifdef WINDOWS
        ::user::enum_key virtual_key_code_to_user_key(int iVirtualKeyCode) override;
#endif
      void initializeInnateSubsystemControls() override;



   };



} // namespace innate_subsystem_macos




