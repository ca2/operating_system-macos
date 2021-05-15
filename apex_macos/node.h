//
// Created by camilo on 19/01/2021. <33TBS!!
//
//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
//  Created by Camilo Sasuke Tsumanuma on 2021-05-14 02:20 PM BRT <3ThomasBorregaardSørensen!!
//
#pragma once


namespace apex
{


   namespace macos
   {


      class CLASS_DECL_APEX_MACOS node :
         virtual public ::apex::apple::node,
         virtual public ::acme::macos::node
      {
      public:


         node();
         virtual ~node();


      };


   } // namespace macos


} // namespace apex



