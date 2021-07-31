// created by Camilo 2021-05-14 15:06 <3CamiloSasukeThomasBorregaardSoerensen!!
#pragma once


namespace macos
{


   class CLASS_DECL_APEX_MACOS interprocess_communication_base :
      virtual public interprocess_communication::base
   {
   public:


      CFMessagePortRef  m_port;
      //HWND              m_hwnd;
      string            m_strBaseChannel;


      interprocess_communication_base();
      virtual ~interprocess_communication_base();


      //HWND get_hwnd() const { return (HWND) m_hwnd; }
      //void set_hwnd(HWND hwnd) { m_hwnd = hwnd; }

   };


   class CLASS_DECL_APEX_MACOS interprocess_communication_tx :
      virtual public interprocess_communication_base,
      virtual public interprocess_communication::tx
   {
   public:


      interprocess_communication_tx();
      virtual ~interprocess_communication_tx();



#if defined(_UWP)
      bool open(const char * pszChannel);
#else
      bool open(const char * pszChannel, ::launcher * plauncher = nullptr);
#endif
      bool close();


      bool send(const char * pszMessage, duration durationTimeout);
      bool send(int message, void * pdata, int len, duration durationTimeout);


      bool is_tx_ok();

   };


   class rx_private;


   class CLASS_DECL_APEX_MACOS interprocess_communication_rx :
      virtual public interprocess_communication_base,
      virtual public interprocess_communication::rx
   {
   public:

      
      CFRunLoopRef      m_runloop;
      

      interprocess_communication_rx();
      ~interprocess_communication_rx() override;


      bool create(const char * pszChannel) override;
      ::e_status destroy() override;


      void * on_interprocess_receive(::interprocess_communication::rx * prx, const char * pszMessage) override;
      void * on_interprocess_receive(::interprocess_communication::rx * prx, int message, void * pdata, memsize len) override;
      void * on_interprocess_post(::interprocess_communication::rx * prx, i64 a, i64 b) override;


      virtual bool on_idle() override;
//
//
//      LRESULT message_queue_proc(UINT message, WPARAM wparam, LPARAM lparam);


      bool is_rx_ok() override;
      
      bool start_receiving();

      void * receive();

   };


} // namespace macos



