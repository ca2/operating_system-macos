//
// Created by camilo on 2026-04-06 10:57 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "platform/subsystem.h"
#include "drawing/Cursor.h"
#include "drawing/Icon.h"
#include "drawing/Path.h"
#include "drawing/Pen.h"
#include "drawing/SolidBrush.h"
#include "drawing/Font.h"
#include "drawing/DeviceContext.h"
#include "drawing/Graphics.h"
#include "drawing/Bitmap.h"
#include "framebuffer/DibSection.h"
#include "gui/SystemMetrics.h"
#include "gui/Window.h"
#include "gui/Control.h"
#include "gui/Dialog.h"
#include "gui/CheckBox.h"
#include "gui/TextBox.h"
#include "gui/SpinControl.h"
#include "gui/Trackbar.h"
#include "gui/ComboBox.h"
#include "gui/NotifyIconWindow.h"
#include "gui/NotifyIcon.h"
#include "gui/Menu.h"
//#include "gui/PaintWindow.h"
#include "gui/Scrollbar.h"
#include "gui/Toolbar.h"
#include "gui/ProgressBar.h"
#include "gui/KeyboardLayout.h"
//#include "gui/OperatingSystemApplication.h"
#include "gui/ListBox.h"
#include "gui/ListView.h"
#include "gui/TabControl.h"
#include "gui/Tab.h"
#include "gui/Tooltip.h"
#include "platform/ResourceLoader.h"
#include "platform/subsystem.h"


DECLARE_FACTORY(subsystem_macos);

DECLARE_FACTORY(nano_graphics_quartz2d);


IMPLEMENT_FACTORY(innate_subsystem_macos)
{
   
   nano_graphics_quartz2d_factory(pfactory);

   subsystem_macos_factory(pfactory);

   pfactory->add_factory_item<::innate_subsystem_macos::subsystem, ::platform::subsystem>();

   pfactory->add_factory_item<::innate_subsystem_macos::SystemMetrics, ::innate_subsystem::SystemMetrics>();

   pfactory->add_factory_item<::innate_subsystem_macos::Window, ::innate_subsystem::WindowInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::Control, ::innate_subsystem::ControlInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::Dialog, ::innate_subsystem::DialogInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::CheckBox, ::innate_subsystem::CheckBoxInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::TextBox, ::innate_subsystem::TextBoxInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::SpinControl, ::innate_subsystem::SpinControlInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::Trackbar, ::innate_subsystem::TrackbarInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::ComboBox, ::innate_subsystem::ComboBoxInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::NotifyIconWindow, ::innate_subsystem::NotifyIconWindowInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::NotifyIcon, ::innate_subsystem::NotifyIconInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::Menu, ::innate_subsystem::MenuInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::Toolbar, ::innate_subsystem::ToolbarInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::TabControl, ::innate_subsystem::TabControlInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::Tab, ::innate_subsystem::TabInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::Tooltip, ::innate_subsystem::TooltipInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::ListView, ::innate_subsystem::ListViewInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::ListBox, ::innate_subsystem::ListBoxInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::ScrollBar, ::innate_subsystem::ScrollBarInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::ProgressBar, ::innate_subsystem::ProgressBarInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::Icon, ::innate_subsystem::IconInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::Cursor, ::innate_subsystem::CursorInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::Pen, ::innate_subsystem::PenInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::Path, ::innate_subsystem::PathInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::SolidBrush, ::innate_subsystem::SolidBrushInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::Font, ::innate_subsystem::FontInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::DibSection, ::innate_subsystem::DibSectionInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::Bitmap, ::innate_subsystem::BitmapInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::Graphics, ::innate_subsystem::GraphicsInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::DeviceContext, ::innate_subsystem::DeviceContextInterface>();

   //pfactory->add_factory_item<::innate_subsystem_macos::PaintWindow, ::innate_subsystem::PaintWindowInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::KeyboardLayout, ::innate_subsystem::KeyboardLayoutInterface>();

   pfactory->add_factory_item<::innate_subsystem_macos::ResourceLoader, ::subsystem::ResourceLoader>();

   //pfactory->add_factory_item<::innate_subsystem_macos::OperatingSystemApplication,
     //                         ::subsystem::OperatingSystemApplicationInterface>();

}
