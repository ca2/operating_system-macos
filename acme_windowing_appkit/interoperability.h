//
// Created by camilo on 2026-05 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "operating_system-apple/core_graphics/_struct.h"

void ns_window_destroy_window(::appkit::ns_window_t nswindow);
void ns_window_show(::appkit::ns_window_t nswindow);
void ns_window_hide(::appkit::ns_window_t nswindow);
void ns_window_enable_window(::appkit::ns_window_t nswindow, bool bEnable);
bool ns_window_is_this_window_enabled(::appkit::ns_window_t nswindow);
bool ns_window_is_window_enabled(::appkit::ns_window_t nswindow);
bool ns_move_window_to_tab_control(::appkit::ns_impact_t nsimpactTabControl,
                                   ::appkit::ns_window_t nswindowPage);
bool ns_tab_control_set_page_caption(::appkit::ns_impact_t nsimpactTabControl,
                                     ::appkit::ns_window_t nswindowPage,
                                     const char * pszCaption);
void ns_tab_control_add_page(::appkit::ns_impact_t nsimpactTabControl,
                             ::appkit::ns_impact_t nsimpactTab,
                                     const char * pszCaption);
bool ns_tab_control_select_item(::appkit::ns_impact_t nsimpactTabControl, int iItem);
int ns_tab_control_get_selected_item(::appkit::ns_impact_t nsimpactTabControl);
void ns_tab_control_erase_page(::appkit::ns_impact_t nsimpactTabControl,
                                ::appkit::ns_impact_t nsimpactPage);
char * ns_get_window_text(::uptr u);
void ns_set_window_text(::uptr u, const char * pszText);
int ns_window_redraw(::appkit::ns_window_t nswindow, ::core_graphics::cg_rect * pcgrect, bool bErase);
void ns_window_get_client_rect(::appkit::ns_window_t nswindow, ::core_graphics::cg_rect * pcgrect);
int ns_window_set_window_pos(::appkit::ns_window_t nswindow,
                              ::appkit::ns_window_t nswindowOther,
                    int x, int y, int w, int h, int flags);
int ns_impact_set_window_pos(::appkit::ns_impact_t nswindow,
                              ::appkit::ns_impact_t nswindowOther,
                    int x, int y, int w, int h, int flags);
::core_graphics::cg_rect ns_window_monitor_rect(::appkit::ns_window_t nswindow);
void ns_window_minimize(::appkit::ns_window_t nswindow);
void ns_window_enter_immersive_fullscreen(::appkit::ns_window_t nswindow);
void ns_window_exit_immersive_fullscreen(::appkit::ns_window_t nswindow);
bool ns_window_is_in_immersive_fullscreen(::appkit::ns_window_t nswindow);
void ns_window_toggle_immersive_fullscreen(::appkit::ns_window_t nswindow);
//void ns_window_add_cursor_rectangle(::appkit::ns_window_t nswindow, ::core_graphics::cg_rect cgrect, ::enum_cursor ecursor);
void ns_window_set_mouse_cursor(::appkit::ns_window_t nswindow, ::enum_cursor ecursor);

::uptr ns_get_dlg_item(::uptr u, int iDlgItem);

void ns_impact_destroy_window(::appkit::ns_impact_t nsimpact);
void ns_impact_enable_window(::appkit::ns_impact_t nsimpact, bool bEnable);
bool ns_impact_is_this_window_enabled(::appkit::ns_impact_t nsimpact);
bool ns_impact_is_window_enabled(::appkit::ns_impact_t nsimpact);
char * ns_get_impact_text(::appkit::ns_impact_t nsimpact);
::operating_system::window ns_get_impact_operating_system_window_by_tag(const ::operating_system::window & operatingsystemwindow, int iDialogItem);
::operating_system::window ns_get_impact_operating_system_window_by_tag_from_window(::appkit::ns_window_t nswindow, int iDialogItem);
::operating_system::window ns_get_impact_operating_system_window_by_tag_from_impact(::appkit::ns_impact_t nsimpact, int iDialogItem);
void ns_set_impact_text(::appkit::ns_impact_t nsimpact, const char * pszText);
void ns_impact_get_client_rect(::appkit::ns_impact_t nsimpact, ::core_graphics::cg_rect * pcgrect);
void ns_impact_set_mouse_cursor(::appkit::ns_impact_t nsimpact, ::enum_cursor ecursor);
void ns_progress_bar_set_range(::appkit::ns_impact_t nsimpact, int iMinimum, int iMaximum);
void ns_progress_bar_set_position(::appkit::ns_impact_t nsimpact, int iPosition);
bool ns_check_box_is_checked(::appkit::ns_impact_t nsimpact);
void ns_check_box_set_checked(::appkit::ns_impact_t nsimpact, bool checked);

// NSComboBox
::collection::index ns_combo_box_insert_string(::appkit::ns_impact_t nsimpact, ::collection::index i, const char * psz);
void ns_combo_box_reset_content(::appkit::ns_impact_t nsimpact);
::collection::count ns_combo_box_get_count(::appkit::ns_impact_t nsimpact);
::collection::index ns_combo_box_get_cur_sel(::appkit::ns_impact_t nsimpact);
void ns_combo_box_set_cur_sel(::appkit::ns_impact_t nsimpact, ::collection::index i);
void ns_combo_box_set_item_data(::appkit::ns_impact_t nsimpact, ::collection::index i, void * p);
void * ns_combo_box_get_item_data(::appkit::ns_impact_t nsimpact, ::collection::index i);
::string ns_combo_box_get_lb_text(::appkit::ns_impact_t nsimpact, ::collection::index i);
void ns_combo_box_delete_string(::appkit::ns_impact_t nsimpact, ::collection::index i);



void throw_wrong_ns_type();
#define NSIMPACT(o) (o).m_opaque.m_ulla[0], (o).m_opaque.m_ulla[1]
#define NSWINDOW(o) (o).m_opaque.m_ulla[0]
