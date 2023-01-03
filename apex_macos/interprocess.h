// created by Camilo 2021-05-14 15:06 <3CamiloSasukeThomasBorregaardSoerensen!!
#pragma once


#include "apex/interprocess/base.h"
#include "apex/interprocess/caller.h"
#include "apex/interprocess/target.h"


#include <CoreFoundation/CoreFoundation.h>


namespace apex_macos
{


   class CLASS_DECL_APEX_MACOS interprocess_base :
      virtual public interprocess::base
   {
   public:


      CFMessagePortRef  m_port;
      //HWND              m_hwnd;
      string            m_strBaseChannel;


      interprocess_base();
      virtual ~interprocess_base();


      //HWND get_hwnd() const { return (HWND) m_hwnd; }
      //void set_hwnd(HWND hwnd) { m_hwnd = hwnd; }

   };


   class CLASS_DECL_APEX_MACOS interprocess_caller :
      virtual public interprocess_base,
      virtual public interprocess::caller
   {
   public:


      interprocess_caller();
      ~interprocess_caller() override;



      void open(const ::string & strChannel, ::launcher * plauncher = nullptr) override;
      void close() override;


      void call(const ::string & strMessage, const class ::time & timeTimeout) override;
//      void send(int message, void * pdata, int len, const class ::time & timeTimeout) override;


      bool is_caller_ok() override;
      

   };


   class rx_private;


   class CLASS_DECL_APEX_MACOS interprocess_target :
      virtual public interprocess_base,
      virtual public interprocess::target
   {
   public:

      
      CFRunLoopRef      m_runloop;
      

      interprocess_target();
      ~interprocess_target() override;


      void create(const ::string & strChannel) override;
      void destroy() override;


//      void on_interprocess_receive(::string && strMessage) override;
//      void on_interprocess_receive(int message, memory && memory) override;
//      void on_interprocess_post(i64 a, i64 b) override;


      virtual bool on_idle() override;
//
//
//      LRESULT message_queue_proc(UINT message, WPARAM wparam, LPARAM lparam);


      bool is_target_ok() override;
      
      bool start_receiving();

      void * receive();

   };


} // namespace apex_macos



