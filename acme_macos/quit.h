//
//  quit.h
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 20/08/22 15:39
//
#pragma once


namespace acme_macos
{

   
   class CLASS_DECL_ACME_MACOS quit :
      virtual public ::element
   {
   public:
      
      
      __pointer(::acme::node) & m_pnode;
      __pointer(class ::system) & m_psystem;

      quit(__pointer(::acme::node) & pnode,__pointer(class ::system) & psystem
            
            ) :
      m_pnode(pnode),m_psystem(psystem)
      {

      }
      
      
      void run() override;
      
   
   };

} // namespace acme_macos
