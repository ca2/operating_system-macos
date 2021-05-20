//
//  node.cpp
//  aura_macos
//
//  Created by Camilo Sasuke on 2021-05-20 14:21 BRT <3ThomasBS_!!
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"


namespace aura
{

   
   namespace macos
   {

      
      node::node()
      {
      
      }


      node::~node()
      {
         
      }
   
   
      ::e_status node::initialize(::object * pobject)
      {
         
         auto estatus = ::aura::apple::node::initialize(pobject);
         
         if(!estatus)
         {
          
            return estatus;
            
         }
         
         estatus = ::apex::macos::node::initialize(pobject);
         
         if(!estatus)
         {
            
            return estatus;
            
         }
      
         return estatus;
         
      }

          
   } // namespace macos


} // namespace aura



