//
//  windowing.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-21 02:00 <3ThomasBS_!!
//
#include "framework.h"


namespace windowing_macos
{


   windowing::windowing()
   {
      
      m_pWindowing2 = this;
      
   }


   windowing::~windowing()
   {
   
   }


   ::e_status windowing::initialize(::object * pobject)
   {
   
      auto estatus = ::windowing::windowing::initialize(pobject);
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      estatus = __construct(m_pdisplay);
      
      if(!estatus)
      {
       
         return estatus;
         
      }
         
      return estatus;
      
   }


   ::e_status windowing::windowing_branch(const ::routine & routine)
   {
      
      auto routineLocal = routine;

      ns_main_async(^
                    {
         
         routineLocal();
         
      });
      
      return success;

   }


   ::windowing::window * windowing::window(oswindow oswindow)
   {

      return oswindow;

   }


   ::windowing::display * windowing::display()
   {

      return m_pdisplay;

   }


   ::windowing::window * windowing::get_active_window(::thread * pthread)
   {
      
      
      return nullptr;
      
   }



   bool windowing::post_ui_message(const MESSAGE &message)
   {

      oswindow oswindow = message.oswindow;

      ASSERT(oswindow != nullptr);

      auto pimpl = oswindow->m_pimpl;

      if(::is_null(pimpl))
      {

         return false;

      }

      auto pinteraction = pimpl->m_puserinteraction;

      if(::is_null(pinteraction))
      {

         return false;

      }

      ::thread *pthread = nullptr;

      if (::is_set(pinteraction))
      {

         pthread = pinteraction->m_pthreadUserInteraction;

      }

      if (::is_null(pthread))
      {

         return false;

      }

      class ::message_queue *pmq = pthread->m_pmq;

      if (pmq == nullptr)
      {

         if (message.m_id == e_message_quit)
         {

            return false;

         }

         pmq = pthread->get_message_queue();

      }

      if (pmq == nullptr)
      {

         return false;

      }

      synchronous_lock ml(pmq->mutex());

      if (message.m_id == e_message_quit)
      {

         output_debug_string("e_message_quit thread");

      }

      if (message.m_id == e_message_left_button_down)
      {

         output_debug_string("post_ui_message::e_message_left_button_down\n");

      }
      else if (message.m_id == e_message_left_button_up)
      {

         output_debug_string("post_ui_message::e_message_left_button_up\n");

      }

      pmq->m_messagea.add(message);

      pmq->m_eventNewMessage.set_event();

      return true;

   }


} // namespace windowing_macos



