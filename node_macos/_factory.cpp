#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif


__FACTORY_EXPORT void windowing_macos_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void node_macos_factory(::factory::factory * pfactory)
{
   

   windowing_macos_factory(pfactory);
   pfactory->add_factory_item < node_macos::node, ::acme::node > ();
   
}



