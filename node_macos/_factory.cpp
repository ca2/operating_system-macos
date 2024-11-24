#include "framework.h"
#include "node.h"


__FACTORY_EXPORT void aura_macos_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void node_macos_factory(::factory::factory * pfactory)
{
   

   aura_macos_factory(pfactory);
   
   pfactory->add_factory_item < node_macos::node, ::platform::node > ();
   
}



