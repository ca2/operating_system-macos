//
//  _.h
//  audio_mixer_core_audio
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 27/03/22.
//  Copyright © 2022 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once



#include "app-core/multimedia/multimedia/_.h"



#if defined(_AUDIO_MIXER_CORE_AUDIO_LIBRARY)
   #define CLASS_DECL_AUDIO_MIXER_CORE_AUDIO  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_AUDIO_MIXER_CORE_AUDIO  CLASS_DECL_IMPORT
#endif


