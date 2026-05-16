//
// Created by camilo on 2026-05 <3ThomasBorregaardSorensen!!
//
#pragma once

#define WIN32_CBERR (-1)
#define WIN32_CBERRSPACE (-2)

namespace cross_windows
{

   ::operating_system::window create_window(::i32 xPos, ::i32 yPos, ::i32 width, ::i32 height, const ::operating_system::window & hwndParent, ::acme::windowing::window * pacmewindowingwindow,
                                            ::appkit::acme_window_bridge * pacmewindowbridge);
void get_client_rect(const ::operating_system::window & operatingsystemwindow, ::i32_rectangle * prectangle);
void show_window_show(const ::operating_system::window & operatingsystemwindow);
void show_window_hide(const ::operating_system::window & operatingsystemwindow);
void invalidate_rect(const ::operating_system::window & operatingsystemwindow,
                     const ::i32_rectangle * prectangle, bool bErase);
int set_window_pos(const ::operating_system::window & operatingsystemwindow,
                    const ::operating_system::window & operatingsystemwindowOther,
                    int x, int y, int w, int h, int flags);
::i32_rectangle get_window_monitor_rect(const ::operating_system::window & operatingsystemwindow);


   ::operating_system::window get_dlg_item(const ::operating_system::window & operatingsystemwindow, int iDlgItem);
   ::string get_window_text(const ::operating_system::window & operatingsystemwindow);
   void set_window_text(const ::operating_system::window & operatingsystemwindow, const ::scoped_string & scopedstr);
   ::collection::index combo_box_insert_string(const ::operating_system::window & operatingsystemwindow, ::collection::index i, const ::scoped_string & scopedstr);
   void combo_box_reset_content(const ::operating_system::window & operatingsystemwindow);
::collection::count combo_box_get_count(const ::operating_system::window & operatingsystemwindow);
::collection::index combo_box_get_cur_sel(const ::operating_system::window & operatingsystemwindow);
void combo_box_set_cur_sel(const ::operating_system::window & operatingsystemwindow, ::collection::index i);
void combo_box_set_item_data(const ::operating_system::window & operatingsystemwindow, ::collection::index i, void * p);
void * combo_box_get_item_data(const ::operating_system::window & operatingsystemwindow, ::collection::index i);
::string combo_box_get_lb_text(const ::operating_system::window & operatingsystemwindow, ::collection::index i);
void combo_box_delete_string(const ::operating_system::window & operatingsystemwindow, ::collection::index i);


} // namespace cross_windows

namespace cross_ns {

void enter_immersive_fullscreen(const ::operating_system::window & operatingsystemwindow);
void exit_immersive_fullscreen(const ::operating_system::window & operatingsystemwindow);
bool is_in_immersive_fullscreen(const ::operating_system::window & operatingsystemwindow);
void toggle_immersive_fullscreen(const ::operating_system::window & operatingsystemwindow);
void set_mouse_cursor(const ::operating_system::window & operatingsystemwindow, ::enum_cursor ecursor);
//void add_cursor_rectangle(const ::operating_system::window & operatingsystemwindow, const ::i32_rectangle & rectangle, ::enum_cursor ecursor);
} // namespace cross_ns
