#include "framework.h"
#include "copydesk.h"
#include "aura/graphics/image/image.h"



bool macos_clipboard_has_changed(long & lTicket);

long macos_clipboard_init();

dispatch_source_t CreateDispatchTimer(double interval, dispatch_queue_t queue, dispatch_block_t block)
{
   dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);
   if (timer)
   {
      dispatch_source_set_timer(timer, dispatch_time(DISPATCH_TIME_NOW, interval * NSEC_PER_SEC), interval * NSEC_PER_SEC, (1ull * NSEC_PER_SEC) / 10);
      dispatch_source_set_event_handler(timer, block);
      dispatch_resume(timer);
   }
   return timer;
}


long macos_clipboard_get_file_count();

void macos_clipboard_get_filea(::file::path_array_base & stra);

void macos_clipboard_set_filea(const ::file::path_array_base & stra);

string macos_clipboard_get_plain_text();

void macos_clipboard_set_plain_text(const char * pszPlainText);

void * macos_clipboard_get_image(int & cx, int & cy, int & iScan);

bool macos_clipboard_set_image(const void * pdata, int cx, int cy, int scan);

bool macos_clipboard_has_image();

bool macos_clipboard_has_plain_text();


namespace windowing_macos
{


   copydesk::copydesk()
   {
      
      m_lTicket = macos_clipboard_init();

      m_bHasFile = false;

      m_bHasText = false;

      m_bHasDib = false;

      dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);

      double secondsToFire = 0.33333333333333333;

      m_ds = CreateDispatchTimer(secondsToFire, queue, ^ { _os_step(); });

      
      ns_main_send(^()
      {
         _on_os_clipboard_changed();
      });
                    
   }

   copydesk::~copydesk()
   {

      if (m_ds)
      {
         dispatch_source_cancel(m_ds);
         // Remove this if you are on a Deployment Target of iOS6 or OSX 10.8 and above
         dispatch_release(m_ds);
         m_ds = nil;
      }


   }


   bool copydesk::_os_clipboard_has_changed()
   {
      
      return macos_clipboard_has_changed(m_lTicket);
      
   }
   
   
   bool copydesk::_os_has_filea()
   {

      return macos_clipboard_get_file_count() > 0;

   }


   bool copydesk::_has_filea()
   {

      return m_bHasFile;

   }


   bool copydesk::_get_filea(::file::path_array_base & patha, enum_op & eop)
   {

      if(!has_filea())
      {

         return false;

      }

      eop = e_op_copy;

      macos_clipboard_get_filea(patha);

      return true;

   }


   bool copydesk::_set_filea(const ::file::path_array_base & patha, enum_op eop)
   {

      ns_main_send(^
      {
         macos_clipboard_set_filea(patha);
      });

      return true;

   }



   void copydesk::initialize(::particle * pparticle)
   {

      //auto estatus =
      
      ::user::copydesk::initialize(pparticle);
      
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }

      //    if(!m_p->CreateEx(0, ::aura::get_system()->RegisterWndClass(0), nullptr, 0, int_rectangle(0, 0, 0, 0), nullptr, id()))
      //     return false;

//      if(!m_p->CreateEx(0, nullptr, nullptr, 0, int_rectangle(0, 0, 0, 0), nullptr, id()))
      //       return false;

      //return estatus;

   }


   void copydesk::destroy()
   {

     
      //auto estatus =
      
      ::user::copydesk::destroy();

//      if(window_pointer::is_set() && window_pointer::m_p->is_window())
      //    {
      //     bOk = window_pointer::m_p->DestroyWindow() != false;
      //}
//      else
      //    {
      //     bOk = false;
      //}
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;
//
   }


   bool copydesk::_set_plain_text(const ::scoped_string & scopedstr)
   {

      macos_clipboard_set_plain_text(scopedstr);

      return true;

   }


   bool copydesk::_get_plain_text(string & str)
   {

      str = macos_clipboard_get_plain_text();

      return true;

   }


   bool copydesk::_os_has_plain_text()
   {

      return macos_clipboard_has_plain_text();

   }


   bool copydesk::_has_plain_text()
   {

      return m_bHasText;

   }


   bool copydesk::_desk_to_image(::image::image * pimage)
   {

      int w = 0;

      int h = 0;

      int iScan = 0;

      ::acme::malloc < image32_t * > pcolorref = (image32_t *) macos_clipboard_get_image(w, h, iScan);

      if(pcolorref == nullptr)
      {

         return false;

      }
      
      pimage->create({w, h});
      
      pimage->map();
      
      if(pimage->image32() != nullptr)
      {
      
         pimage->image32()->_001ProperCopyColorref(w, h, pimage->scan_size(), pcolorref, iScan);
         
      }
//      else if(pimage->m_pframea->is_set())
//      {
//
//         for(auto & ppointer : *pimage->m_pframea)
//         {
//
//            if(ppointer.is_set() & ppointer->m_pimpl.is_set())
//            {
//
//            }
//
//         }
//
//      }

      return true;

   }


   bool copydesk::_image_to_desk(const ::image::image * pimage)
   {

      bool bOk = macos_clipboard_set_image(
                                        pimage->get_data(),
                                        pimage->width(),
                                        pimage->height(),
                                        pimage->scan_size());

      if(bOk)
      {

         return false;

      }

      return true;

   }


   bool copydesk::_os_has_image()
   {

      return macos_clipboard_has_image();

   }


   bool copydesk::_has_image()
   {

      return m_bHasDib;

   }


   void copydesk::_on_os_clipboard_changed()
   {

      m_bHasFile = _os_has_filea();

      m_bHasText = _os_has_plain_text();

      m_bHasDib = _os_has_image();

   }


   void copydesk::_os_step()
   {
      
      ns_main_post(^()
      {
         
         if(_os_clipboard_has_changed())
         {

            _on_os_clipboard_changed();
            
         }
                       
      });

   }


} // namespace windowing_macos





char ** macos_clipboard_get_filea(long * pc);


void macos_clipboard_get_filea(::file::path_array_base & patha)
{

   long c = 0;

   try
   {

      char ** psza = macos_clipboard_get_filea(&c);

      patha.c_add(psza, c, false);

   }
   catch (...)
   {

   }

}


void macos_clipboard_set_filea(const char ** psza, long c);


void macos_clipboard_set_filea(const ::file::path_array_base & patha)
{

   auto psza = patha.c_ansi_get();

   macos_clipboard_set_filea(psza.data(), psza.count());

}


char * _macos_clipboard_get_plain_text();


string macos_clipboard_get_plain_text()
{
   
   string str = string_from_strdup(_macos_clipboard_get_plain_text()); 

   return str;
   
}
