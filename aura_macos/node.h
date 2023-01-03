//
//  node.hpp
//  aura_macos
//
//  Created by Camilo Sasuke on 2021-05-20 14:20 BRT <3ThomasBS_!!
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#pragma once


#include "aura_apple/node.h"
#include "apex_macos/node.h"


namespace aura_macos
{

   
      class CLASS_DECL_AURA_MACOS node :
         virtual public aura_apple::node,
         virtual public apex_macos::node
      {
      public:
         
         
         node();
         ~node() override;
         
         
         void initialize(::particle * pparticle) override;
         
         
         ::image_pointer get_file_image_by_type_identifier(int iSize, const ::scoped_string & scopedstrTypeIdentifier) override;

         ::image_pointer get_file_image(int iSize, const ::file::path & path) override;

         
      };
      
   
} // namespace aura_macos



