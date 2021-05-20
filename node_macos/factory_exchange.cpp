#include "framework.h"


extern "C"
void windowing_macos_factory_exchange(::factory_map * pfactorymap);


extern "C"
void node_macos_factory_exchange(::factory_map * pfactorymap)
{
   

   windowing_macos_factory_exchange(pfactorymap);
   
   
}



