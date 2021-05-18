#include "framework.h"


extern "C"
void aura_macos_factory_exchange(::factory_map * pfactorymap);


extern "C"
void node_macos_factory_exchange(::factory_map * pfactorymap)
{
   

   aura_macos_factory_exchange(pfactorymap);
   
}



