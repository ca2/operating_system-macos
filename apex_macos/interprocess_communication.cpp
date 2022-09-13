#include "framework.h"
#include <sys/ipc.h>
#include <sys/msg.h>
#include "acme/operating_system/ansi/_pthread.h"


namespace apex_macos
{


   interprocess_communication_base::interprocess_communication_base()
   {
      
      m_port = nullptr;
      
   }

   
   interprocess_communication_base::~interprocess_communication_base()
   {
      
      
   }


   interprocess_communication_tx::interprocess_communication_tx()
   {

      
   }


   interprocess_communication_tx::~interprocess_communication_tx()
   {

      
   }


   void interprocess_communication_tx::open(const ::string & strChannel,launcher * plauncher)
   {

      //CFDataRef data;

      //SInt32 messageID = 0x1111; // Arbitrary

      //CFTimeInterval timeout = 10.0;

      CFStringRef name = CFStringCreateWithCString(nullptr,  (string("com.ca2.app.port.server.") + strChannel), kCFStringEncodingUTF8);

      m_port =        CFMessagePortCreateRemote(nil,name);

      CFRelease(name);

      //return true;

   }


   void interprocess_communication_tx::close()
   {

      if(m_port == nullptr)
      {

         throw exception(error_wrong_state);

      }

      CFRelease(m_port);

      m_port = nullptr;

      //return true;

   }


   void interprocess_communication_tx::send(const ::string & strMessage, const ::duration & durationTimeout)
   {

      if(m_port == nullptr)
      {
         
         throw exception(error_wrong_state);
         
      }

      ::count c = ansi_length(strMessage);

      //::count cSend;

      memory m;

      m.assign(strMessage, c);

      CFDataRef data = get_os_cf_data(m);

      CFTimeInterval sendTimeout = durationTimeout.floating_second().m_d;

      CFTimeInterval rcvimeout = durationTimeout.floating_second().m_d;

      SInt32 status =
      CFMessagePortSendRequest(m_port,
                               0x80000000,
                               data,
                               sendTimeout,
                               rcvimeout,
                               nullptr,
                               nullptr);
      if (status == kCFMessagePortSuccess)
      {

         return;

      }

      if(status != kCFMessagePortSendTimeout && status != kCFMessagePortReceiveTimeout)
      {

         close();

      }

      //return false;

   }


   void interprocess_communication_tx::send(int message,void * pdata,int len, const duration & durationTimeout)
   {

      if(message == 0x80000000)
         throw exception(error_wrong_state);


      if(!is_tx_ok())
         throw exception(error_wrong_state);

      memory m(pdata, len);

      //::count c = len;

      //::count cSend;


      SInt32 status =
      CFMessagePortSendRequest(m_port,
                               message,
                               get_os_cf_data(m),
                               (double) durationTimeout.floating_second().m_d,
                               (double) durationTimeout.floating_second().m_d,
                               nullptr,
                               nullptr);
      if (status == kCFMessagePortSuccess)
      {
         // ...
      }
      //return true;

   }



   bool interprocess_communication_tx::is_tx_ok()
   {

      return m_port != nullptr;

   }




interprocess_communication_rx::interprocess_communication_rx()
   {

      m_atom = "::interprocess_communication::rx";
   
      m_runloop = nullptr;

      m_preceiver    = nullptr;

   }


interprocess_communication_rx::~interprocess_communication_rx()
   {

   }


   CFDataRef Callback(CFMessagePortRef port,
                      SInt32 messageID,
                      CFDataRef data,
                      void *info)
   {
      
      interprocess_communication_rx * prx = (interprocess_communication_rx*) info;

      if(messageID == 0x80000000)
      {

         memory m;

         set_os_cf_data(m, data);

         prx->on_interprocess_receive(::move(__string(m)));

      }
      else
      {

         memory m;

         set_os_cf_data(m, data);

         prx->on_interprocess_receive(messageID, ::move(m));

      }
      
      return nullptr;
      
   }
   

   void interprocess_communication_rx::create(const ::string & strChannel)
   {

      CFMessagePortContext c = {};

      c.info = this;

      CFStringRef kungfuck = CFStringCreateWithCString(nullptr,  (string("com.ca2.app.port.server.") + strChannel), kCFStringEncodingUTF8);

      Boolean b = false;

      m_port = CFMessagePortCreateLocal(nil, kungfuck, Callback, &c, &b);

      start_receiving();

      //return true;

   }


   void interprocess_communication_rx::destroy()
   {

      if(m_port == nullptr)
      {
         
         return;
         
      }

      CFRelease(m_port);

      m_port = nullptr;

      //return ::success;

   }


   bool interprocess_communication_rx::start_receiving()
   {

      m_bRunning = true;

      m_bRun = true;

      m_pthread = fork([&]()
      {

         receive();
      });

      return true;

   }


//      void rx::receiver::on_ipc_receive(rx * prx,const ::string & pszMessage)
//      {
//
//      }
//
//
//      void rx::receiver::on_receive(rx * prx,int message,void * pdata,memsize len)
//      {
//      }
//
//      void rx::receiver::on_post(rx * prx,i64 a,i64 b)
//      {
//      }



//   void interprocess_communication_rx::on_interprocess_receive(::string && pszMessage)
//   {
//
//      if(m_preceiver != nullptr)
//      {
//
//         string strMessage(pszMessage);
//
//            m_preceiver->on_interprocess_receive(this,strMessage);
//
//      }
//
//      // ODOW - on date of writing : return ignored by this windows implementation
//
//   }
//
//
//   void interprocess_communication_rx::on_interprocess_receive(int message,memory && memory)
//   {
//
//      if(m_preceiver != nullptr)
//      {
//
//         m_preceiver->on_interprocess_receive(message, memory);
//
//      }
//
//      // ODOW - on date of writing : return ignored by this windows implementation
//
//      return nullptr;
//
//   }
//
//
//   void * interprocess_communication_rx::on_interprocess_post(::interprocess_communication::rx * prx,i64 a,i64 b)
//   {
//
//      if(m_preceiver != nullptr)
//      {
//
//         m_preceiver->on_interprocess_post(prx, a, b);
//
//      }
//
//      // ODOW - on date of writing : return ignored by this windows implementation
//
//      return nullptr;
//
//   }
//
//

   bool interprocess_communication_rx::on_idle()
   {

      return false;

   }


   bool interprocess_communication_rx::is_rx_ok()
   {

      return m_port != nullptr;
   }



   void * interprocess_communication_rx::receive()
   {

      if(m_port == nullptr)
         return nullptr;


      CFRunLoopSourceRef runLoopSource =
      CFMessagePortCreateRunLoopSource(nil, m_port, 0);

      CFRunLoopRef runloop = CFRunLoopGetCurrent();

      m_runloop = runloop;

      CFRunLoopAddSource(CFRunLoopGetCurrent(),
                         runLoopSource,
                         kCFRunLoopCommonModes);

      //while(m_bRun && ::task_get_run())
      // Set up an autorelease pool here if not using garbage collection.
      bool done = false;

      // Add your sources or timers to the run loop and do any other setup.

      do
      {
         // Start the run loop but return after each source is handled.
         SInt32    result = CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.5, true);

         // If a source explicitly stopped the run loop, or if there are no
         // sources or timers, go ahead and exit.
         if ((result == kCFRunLoopRunStopped) || (result == kCFRunLoopRunFinished))
            done = true;

         // Check for any other exit conditions here and set the
         // done variable as needed.
      }
      while(!done && ::task_get_run());

//         while(m_bRun)
//         {
//
//            m_bRunning = true;
//
//            ssize_t  result;
//
//            int length;
//
//            data_struct data;
//
//            /* The length is essentially the size_i32 of the structure minus sizeof(mtype) */
//            length = sizeof(data) - sizeof(data.message);
//
//            memory mem;
//
//            do
//            {
//
//               __zero(data);
//               if((result = msgrcv(m_iQueue,&data,length,2000,IPC_NOWAIT)) == -1)
//               {
//
//                  if(errno == ENOMSG)
//                  {
////                     if(!on_idle())
//  //                   {
//    //                    sleep(84 * 1000);
//      //               }
//                     sleep(100_ms);
//                  }
//                  else
//                  {
//                     return (void *)-1;
//                  }
//
//               }
//
//               mem.append(data.data,data.size_i32);
//
//
//               if(data.size_i32 < 512)
//                  break;
//
//            } while(true);
//
//            if(data.size_i32 > 0)
//            {
//            if(data.request == 5)
//            {
//
//               on_receive(this,mem.to_string());
//
//            }
//            else
//            {
//
//               on_receive(this,data.request,mem.get_data(),(int)mem.get_size());
//
//            }
//            }
//
//         }
//
//         m_bRunning = false;

      return nullptr;

   }
//
//
//   interprocess_communication::interprocess_communication()
//   {
//
//      m_millisTimeout = (5000) * 11;
//
//   }
//
//
//   interprocess_communication::~interprocess_communication()
//   {
//
//
//   }
//
//
//
//   bool interprocess_communication::open_ab(const ::string & pszChannel,launcher * plauncher)
//   {
//
//      m_strChannel = pszChannel;
//
//      m_rx.m_preceiver = this;
//
//      string strChannelRx = m_strChannel + "-a";
//      string strChannelTx = m_strChannel + "-b";
//
//
//      if(!m_rx.create(strChannelRx))
//      {
//         return false;
//      }
//
//      if(!tx::open(strChannelTx,plauncher))
//      {
//         return false;
//      }
//
//      return true;
//
//   }
//
//   bool interprocess_communication::open_ba(const ::string & pszChannel,launcher * plauncher)
//   {
//
//      m_strChannel = pszChannel;
//
//      m_rx.m_preceiver = this;
//
//      string strChannelRx = m_strChannel + "-b";
//      string strChannelTx = m_strChannel + "-a";
//
//
//      if(!m_rx.create(strChannelRx))
//      {
//         return false;
//      }
//
//      if(!tx::open(strChannelTx,plauncher))
//      {
//         return false;
//      }
//
//      return true;
//
//   }
//
//
//   bool interprocess_communication::is_rx_tx_ok()
//   {
//
//      return m_rx.is_rx_ok() && is_tx_ok();
//
//   }


} // namespace apex_macos





