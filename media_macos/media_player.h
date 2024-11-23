//
//  media_player.hpp
//  media_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-10 22:21.
//
#pragma once


#include "media_apple/media_player.h"


namespace media_macos
{

      
   class CLASS_DECL_MEDIA_APPLE media_player :
   virtual public ::media_apple::media_player
   {
   public:
      
      
      media_player();
      ~media_player();
      
      
      void OnHappening(::aqua::enum_player_happening ehappening, ::aqua::media_player_command * pcommand) override;
      
      void post_command(::aqua::media_player_command* pcommand) override;

   };


} // namespace media_macos




