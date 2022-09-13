#pragma once


#include "aura/user/user/notify_icon.h"
#include "notify_icon_mm_bridge.h"


namespace windowing_macos
{


   class CLASS_DECL_WINDOWING_MACOS notify_icon :
      virtual public ::user::notify_icon,
      virtual public ::user_notify_icon_mm_bridge
   {
   public:


      notify_icon();
      ~notify_icon() override;


      void add_hidden_window(::user::interaction * puserinteraction) override;


      virtual bool DestroyWindow();


      bool ModifyIcon(__pointer(::draw2d::icon) picon, bool bForce = false);


      void create_notify_icon(const ::atom & atom, ::user::interaction * puserinteractionNotify, ::windowing::icon * picon) override;

      //DECL_GEN_SIGNAL(_001OnNotifyIconMessage);
      //DECL_GEN_SIGNAL(_001OnDestroy);

      bool step() override;
      //virtual void notify_icon_play(const char * action) override;

      
   };


} // namespace windowing_macos


