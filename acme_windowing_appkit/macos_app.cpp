//
//  app_ns.cpp.h
//  acme_windowing_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-11-01.
//
#include "framework.h"
void defer_create_nano_application_delegate(void * pApplication);

void apple_defer_nano_application_create(class ::platform::system * psystem)
{

   auto papp = psystem->m_papplication;

   void * pApplication = (void *) (::platform::application *) papp;

   defer_create_nano_application_delegate(pApplication);

}
