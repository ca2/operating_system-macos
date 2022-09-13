//
// Created by camilo on 19/01/2021. <33TBS!!
//
//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
//  Created by Camilo Sasuke Tsumanuma on 2021-05-14 02:20 PM BRT <3ThomasBorregaardSørensen!!
//
#pragma once


#include "apex_apple/node.h"
#include "acme_macos/node.h"


namespace apex_macos
{


   class CLASS_DECL_APEX_MACOS node :
      virtual public ::apex_apple::node,
      virtual public ::acme_macos::node
   {
   public:


      node();
      ~node() override;
      
      
      virtual int node_init_check(int * pi, char *** ppz) override;


      
      string app_id_to_executable_name(const string & strAppId) override;


   };


} // namespace apex_macos



