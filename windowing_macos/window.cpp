//
//  macos_window.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//

#include "framework.h"
#include "window_impl.h"
#include "oswindow_data.h"
#include "acme/parallelization/message_queue.h"
#include <CoreGraphics/CoreGraphics.h>


namespace windowing_macos
{



class aura_window_draw_life_time
{
public:


   interaction_impl * m_pimpl;

   aura_window_draw_life_time(interaction_impl * pimpl) :
      m_pimpl(pimpl)
   {

      m_pimpl->m_nanosLastUpdateBeg.Now();

   }

   ~aura_window_draw_life_time()
   {

      m_pimpl->m_nanosLastUpdateEnd.Now();

   }

};



::e_status window::create_window(::user::interaction_impl * pimpl)
{

   //if (::is_window(get_handle()))
   //{

   //   DestroyWindow();

   //}

   //      ASSERT(lpszClassName == nullptr || __is_valid_string(lpszClassName) ||
   //       __is_valid_atom(lpszClassName));
//      ENSURE_ARG(pusersystem->m_createstruct.lpszName == nullptr || __is_valid_string(pusersystem->m_createstruct.lpszName));

   // allow modification of several common create parameters
   //::user::system createstruct;
   //      pusersystem->m_createstruct.hwndParent = hWndParent;
   //   pusersystem->m_createstruct.hMenu = hWndParent == nullptr ? nullptr : nIDorHMenu;
   m_pusersystem->m_createstruct.hMenu = nullptr;
   //      pusersystem->m_createstruct.hInstance = ::aura::get_system()->m_hInstance;
   //pusersystem->m_createstruct.lpCreateParams = lpParam;

   if (!m_puserinteraction->pre_create_window(m_pusersystem))
   {

      return false;

   }

   install_message_routing(m_puserinteraction);

   hook_window_create(m_puserinteraction);

   CGRect rectangle_i32;

   RECTANGLE_I32 rectParam;

//      rectParam.left = m_pusersystem->m_createstruct.x;
//      rectParam.top = pusersystem->m_createstruct.y;
//      rectParam.right = pusersystem->m_createstruct.x + pusersystem->m_createstruct.cx;
//      rectParam.bottom = pusersystem->m_createstruct.y + pusersystem->m_createstruct.cy;

//      __copy(rectangle, rectParam);
//
//      if (pusersystem->m_createstruct.hwndParent == MESSAGE_WINDOW_PARENT)
//      {
//
//         return true;
//
//      }
//      else
//      {

      unsigned uStyle = 0;

      if(m_puserinteraction->m_ewindowflag & ::e_window_flag_miniaturizable)
      {

#define NSWindowStyleMaskMiniaturizable (1 << 2)

         uStyle |= NSWindowStyleMaskMiniaturizable;

      }
   
      auto rectangle = m_puserinteraction-> get_window_rect();

      m_oswindow = oswindow_get(new_aura_window(this, rectangle, uStyle));

      m_puserinteraction->layout().window() = ::top_left(rectParam);

      m_puserinteraction->layout().window() = ::size_i32(rectParam);

      __refer(m_puserinteraction->m_pthreadUserInteraction, ::get_task());

      //m_puserinteraction->place(rectParam);



      m_oswindow->set_user_interaction_impl(this);

      oswindow_assign(m_oswindow, this);

   }

   LRESULT lresult = m_puserinteraction->send_message(e_message_create, 0, (LPARAM)&cs);

   bool bOk = true;

   if (!unhook_window_create() || lresult == -1)
   {

      bOk = false;
      
      finalize();

      //children_post_quit();

      //children_wait_quit(one_minute());

      PostNcDestroy();        // cleanup if CreateWindowEx fails too soon
      
      return false;

   }

   if(pusersystem->m_createstruct.style & WS_VISIBLE)
   {

      m_puserinteraction->display();

      m_puserinteraction->set_need_redraw();

      //m_puserinteraction->post_redraw();

      //;//aura_window_show();

   }

   m_puserinteraction->set_need_layout();

   m_puserinteraction->add_ref(OBJ_REF_DBG_P_NOTE(this, "native_create_window"));

   m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;
   
   return bOk;

}


// for child windows
bool interaction_impl::pre_create_window(::user::system * pusersystem)
{
   /*      if (pusersystem->m_createstruct.lpszClass == nullptr)
    {
/xcore/app/aura/node/macos/macos_interaction_impl.cpp:712:44: No member named 'get_window_rect' in 'user::interaction_impl'       // make sure the default user::interaction class is registered
    VERIFY(__end_defer_register_class(__WND_REG, &pusersystem->m_createstruct.lpszClass));

    // no WNDCLASS provided - use child user::interaction default
    ASSERT(pusersystem->m_createstruct.style & WS_CHILD);
    }*/
   return true;
}

void window::aura_window_add_ref()
{

   add_ref(OBJ_REF_DBG_P_NOTE(this, "aura_window_add_ref"));

   m_puserinteraction->add_ref(OBJ_REF_DBG_P_NOTE(this, "aura_window_add_ref"));

}


void window::aura_window_dec_ref()
{

   m_puserinteraction->dec_ref(OBJ_REF_DBG_P_NOTE(this, "aura_window_dec_ref"));

   dec_ref(OBJ_REF_DBG_P_NOTE(this, "aura_window_dec_ref"));

}


} // namespace windowing_macos
