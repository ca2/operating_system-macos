#include "framework.h"
#include "control.h"
#include "destination.h"
#include "device.h"
#include "line_info.h"
#include "audio_mixer.h"
#include "source.h"


__FACTORY_EXPORT void audio_mixer_core_audio_factory(::factory::factory * pfactory)
{

      //System.factory().cloneable_large < callback                    >  (System.type_info < ::audio_mixer::callback                 > ());
   pfactory->add_factory_item < ::audio_mixer_core_audio::control, ::audio_mixer::control                  > ();
      //System.factory().creatable_small < control_data                >  (System.type_info < ::audio_mixer::control_data             > ());
   pfactory->add_factory_item < ::audio_mixer_core_audio::destination, ::audio_mixer::destination                  > ();
   pfactory->add_factory_item < ::audio_mixer_core_audio::device, ::audio_mixer::device                  > ();         pfactory->add_factory_item < ::audio_mixer_core_audio::line_info, ::audio_mixer::line_info                  > ();
   pfactory->add_factory_item < ::audio_mixer_core_audio::audio_mixer, ::audio_mixer::audio_mixer                  > ();
      //System.factory().cloneable_large < section                   >  (System.type_info < ::audio_mixer::font                     > ());
   pfactory->add_factory_item < ::audio_mixer_core_audio::source, ::audio_mixer::source                  > ();      //System.factory().creatable_small < thread                      >  (System.type_info < ::audio_mixer::thread                   > ());
      /*System.factory().creatable_small < user::label                 >  (System.type_info < ::audio_mixer::user::label              > ());
      System.factory().creatable_small < user::control               >  (System.type_info < ::audio_mixer::user::control            > ());
      System.factory().creatable_small < user::level_control         >  (System.type_info < ::audio_mixer::user::level_control      > ());
      System.factory().creatable_small < user::toggle_control        >  (System.type_info < ::audio_mixer::user::toggle_control     > ());*/

}


