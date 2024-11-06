//
//  app_ns.cpp.h
//  acme_windowing_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-11-01.
//
#include "framework.h"



void defer_create_acme_application_delegate(::platform::application * papplication);


void apple_defer_nano_application_create(class ::platform::system * psystem)
{

   auto papplication = psystem->m_papplication;

   defer_create_acme_application_delegate(papplication);

}
