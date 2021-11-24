#include "framework.h"


extern "C"
void windowing_macos_factory(::factory::factory * pfactory);


extern "C"
void node_macos_factory(::factory::factory * pfactory)
{
   

   windowing_macos_factory(pfactory);
   
   
}



