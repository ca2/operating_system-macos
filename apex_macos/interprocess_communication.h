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
      ~interprocess_communication_tx() override;



      void open(const ::string & strChannel, ::launcher * plauncher = nullptr) override;
      void close() override;


      void send(const ::string & strMessage, const duration & durationTimeout) override;
      void send(int message, void * pdata, int len, const duration & durationTimeout) override;


      bool is_tx_ok() override;
      

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


      void create(const ::string & strChannel) override;
      void destroy() override;


//      void on_interprocess_receive(::string && strMessage) override;
//      void on_interprocess_receive(int message, memory && memory) override;
//      void on_interprocess_post(i64 a, i64 b) override;


      virtual bool on_idle() override;
//
//
//      LRESULT message_queue_proc(UINT message, WPARAM wparam, LPARAM lparam);


      bool is_rx_ok() override;
      
      bool start_receiving();

      void * receive();

   };


} // namespace macos



