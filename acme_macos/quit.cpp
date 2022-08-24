//
//  quit.cpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 20/08/22 16:35
//
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif
#include "quit.h"


void ns_app_terminate();


namespace acme_macos
{


   void quit::run()
   {

      m_pnode->m_pAcmePlatform->m_peventReadyToTerminateApp->set_event();

      auto htaskSystem = (pthread_t) m_pnode->m_htaskSystem;

      pthread_join(htaskSystem, nullptr);
    
      m_pnode.release();
    
      m_psystem.release();

      ns_app_terminate();

      delete this;

   //         return ::success;
   //
   }


} // namespace acme_macos



