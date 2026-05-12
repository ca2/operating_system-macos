#include "framework.h" 
#include "berg/user/_.h"
#include "_windows.h"


 namespace base
 {


    namespace macos
    {


       factory_exchange::factory_exchange()
       {

          add_factory_item < ::macos::print_job, ::user::print_task >();

       }


       factory_exchange::~factory_exchange()
       {

       }


    } // namespace macos


 } // namespace base


 void __node_base_factory(::factory::factory * pfactory)
 {

    ::base::macos::factory_exchange factoryexchange;

 }




