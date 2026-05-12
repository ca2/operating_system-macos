//
// Created by camilo on 2026-04-06 10:54 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"
#include "acme/platform/user_interaction_sink.h"
#include "acme/operating_system/macos/message_box.h"
#include "innate_subsystem_macos/gui/CommonControlsEx.h"


namespace innate_subsystem_macos
{


    subsystem::subsystem()
    {



    }


    subsystem::~subsystem()
    {


    }

    //
    // ::subsystem::string_table * subsystem::string_table()
    // {
    //
    //    if (!m_pstringtable)
    //    {
    //
    //       constructø(m_pstringtable);
    //
    //    }
    //
    //    return m_pstringtable;
    //
    // }
    //
    //
    //
    // ::subsystem::resource_loader * subsystem::resource_loader()
    // {
    //
    //    if (!m_presourceloader)
    //    {
    //
    //       constructø(m_presourceloader);
    //
    //    }
    //
    //    return m_presourceloader;
    //
    // }
    //
    //
    //
    // ::subsystem::Registry * subsystem::registry()
    // {
    //
    //    if (!m_pregistry)
    //    {
    //
    //       construct_newø(m_pregistry);
    //
    //    }
    //
    //    return m_pregistry;
    //
    // }
    //
    //
    // ::subsystem::Shell * subsystem::shell()
    // {
    //
    //    if (!m_pshell)
    //    {
    //
    //       constructø(m_pshell);
    //
    //    }
    //
    //    return m_pshell;
    //
    // }
    //
    // ::pointer < ::subsystem::SecurityIdentifier > subsystem::createSidFromString(const ::scoped_string & scopedstr)
    // {
    //
    //    return nullptr;
    //
    // }


    ::enum_dialog_result subsystem::message_box(
                    const ::user_interaction_sink & userinteractionsink,
                    const ::scoped_string & scopedstrMessage,
                    const ::scoped_string & scopedstrCaption,
                    ::user::enum_message_box emessagebox)
    {

        auto operatingsystemwindow = userinteractionsink.best_effort_operating_system_window();

        auto hwnd = ::as_u64(operatingsystemwindow);
       
       auto edialogresult = ns_message_box(::string(scopedstrCaption), ::string(scopedstrMessage), emessagebox & ::user::e_message_box_yes_no);

        //auto iResult = ::MessageBox(hwnd, ::wstring(scopedstrMessage), ::wstring(scopedstrCaption), uType);

        return edialogresult;

    }


   void subsystem::initializeInnateSubsystemControls()
    {

       CommonControlsEx::init();
    }



}//namespace subsystem



