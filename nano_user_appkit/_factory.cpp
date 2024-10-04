#include "framework.h"
//#include "dialog.h"
//#include "icon.h"
#include "window.h"
//#include "button.h"
//#include "still.h"
//#include "innate_ui.h"



IMPLEMENT_FACTORY(nano_user_appkit)
{

   pfactory->add_factory_item < ::appkit::nano::user::window, ::windowing::window_base >();
   //pfactory->add_factory_item < ::innate_ui_appkit::dialog, ::innate_ui::dialog >();
   
   
   //pfactory->add_factory_item < ::innate_ui_appkit::button, ::innate_ui::button >();
   //pfactory->add_factory_item < ::innate_ui_appkit::still, ::innate_ui::still >();


   //pfactory->add_factory_item < ::innate_ui_appkit::icon, ::innate_ui::icon >();


   //pfactory->add_factory_item < ::innate_ui_appkit::innate_ui, ::innate_ui::innate_ui >();

}



