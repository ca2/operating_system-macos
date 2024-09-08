//
//  node.cpp
//  aura_macos
//
//  Created by Camilo Sasuke on 2021-05-20 14:21 BRT <3ThomasBS_!!
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"
#include "node.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/image/context.h"
#include "aura/platform/context.h"

//
//bool macos_get_file_image(::image * pimage, const char * pszFilePath);
//bool macos_get_file_image_by_type_identifier(::image * pimage, const char * pszTypeIdentifier);


namespace aura_macos
{


      node::node()
      {
      
      }


      node::~node()
      {
         
      }
   
   
      void node::initialize(::particle * pparticle)
      {
         
         //auto estatus =
         
         ::aura_apple::node::initialize(pparticle);
         
//         if(!estatus)
//         {
//
//            return estatus;
//
//         }
         
         //estatus =
         
         ::apex_macos::node::initialize(pparticle);
         
//         if(!estatus)
//         {
//            
//            return estatus;
//            
//         }
//      
//         return estatus;
         
      }
//
//   
//      ::image_pointer node::get_file_image_by_type_identifier(int iSize, const ::scoped_string & scopedstrTypeIdentifier)
//      {
//
//         auto pimage = m_pcontext->m_pauracontext->create_image( { iSize, iSize } );
//
//         synchronous_lock synchronouslock(this->synchronization());
//
//         if(!macos_get_file_image_by_type_identifier(pimage, scopedstrTypeIdentifier))
//         {
//
//            return nullptr;
//
//         }
//
//         return pimage;
//
//      }
//
//   
//      ::image_pointer node::get_file_image(int iSize, const ::file::path & path)
//      {
//         
//
//         auto pimage = m_pcontext->m_pauracontext->create_image( { iSize, iSize } );
//
//         synchronous_lock synchronouslock(this->synchronization());
//
//         if(!macos_get_file_image(pimage, path))
//         {
//
//            return nullptr;
//
//         }
//
//         return pimage;
//
//      }
//

} // namespace aura_macos



