//
//  node.cpp
//  aura_macos
//
//  Created by Camilo Sasuke on 2021-05-20 14:21 BRT <3ThomasBS_!!
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif
#include "aura/graphics/image/context_image.h"


bool macos_get_file_image(::image * pimage, const char * pszFilePath);
bool macos_get_file_image_by_type_identifier(::image * pimage, const char * pszTypeIdentifier);


namespace aura_macos
{


      node::node()
      {
      
      }


      node::~node()
      {
         
      }
   
   
      void node::initialize(::object * pobject)
      {
         
         //auto estatus =
         
         ::aura_apple::node::initialize(pobject);
         
//         if(!estatus)
//         {
//
//            return estatus;
//
//         }
         
         //estatus =
         
         ::apex_macos::node::initialize(pobject);
         
//         if(!estatus)
//         {
//            
//            return estatus;
//            
//         }
//      
//         return estatus;
         
      }

   
      ::image_pointer node::get_file_image_by_type_identifier(int iSize, const char * pszTypeIdentifier)
      {

         auto pimage = m_pcontext->m_pauracontext->create_image( { iSize, iSize } );

         if(!macos_get_file_image_by_type_identifier(pimage, pszTypeIdentifier))
         {

            return nullptr;

         }

         return pimage;

      }

   
      ::image_pointer node::get_file_image(int iSize, const char * path)
      {

         auto pimage = m_pcontext->m_pauracontext->create_image( { iSize, iSize } );

         if(!macos_get_file_image(pimage, path))
         {

            return nullptr;

         }

         return pimage;

      }



} // namespace aura_macos



