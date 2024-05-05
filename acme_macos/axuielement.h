//
//  axuielement.hpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2023-05-03 06:11.
//
#pragma once


#include <Carbon/Carbon.h>


void axuielement_post_close(AXUIElementRef axuielement);
::string axuielement_first_window_title(AXUIElementRef axuielement);
::string axuielement_application_name(AXUIElementRef axuielement);
::raw::count axuielement_application_window_count(AXUIElementRef axuielement);
AXUIElementRef axuielement_menu_bar_item_menu_item_with(AXUIElementRef axuielement, ::raw::index i, const char * psz);
AXUIElementRef axuielement_menu_bar(AXUIElementRef axuielement);

