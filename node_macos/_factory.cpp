#include "framework.h"


__FACTORY_EXPORT void windowing_macos_factory(::factory_map * pfactorymap);


__FACTORY_EXPORT void node_macos_factory(::factory_map * pfactorymap)
{
   

   windowing_macos_factory(pfactorymap);
   
   
}



