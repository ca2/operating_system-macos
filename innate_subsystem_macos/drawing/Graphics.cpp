// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
// Adapted by camilo on beginning of 2026-April <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "Graphics.h"
#include "DeviceContext.h"
#include "Bitmap.h"
#include "SolidBrush.h"
#include "Font.h"
#include "Pen.h"
#include "innate_subsystem/platform/subsystem.h"
#include "operating_system-apple/core_graphics/core_graphics.h"
#include "operating_system-apple/core_graphics/cg_context.h"
//#define WIN32_TRANSPARENT 0

namespace innate_subsystem_macos
{
   // Graphics::Graphics(DeviceContext *dc)
   // : m_dc(dc)
   // {
   // }

   Graphics::Graphics()
   {
//m_iBkMode = TRANSPARENT;
      //m_pfont = nullptr;
      m_pbrushText = nullptr;
   }


   Graphics::~Graphics()
   {

      if (m_pfont)
      {

         delete m_pfont;
         m_pfont = nullptr;
      }
      if (m_pbrushText)
      {

         delete m_pbrushText;
         m_pbrushText = nullptr;
      }
   }


   innate_subsystem::DeviceContextInterface * Graphics::device_context()
   {

return m_pdevicecontext;

   }


   void Graphics::initialize_graphics(innate_subsystem::DeviceContextInterface * pdevicecontext)
   {

      m_pdevicecontext = pdevicecontext;

   }


   void Graphics::initialize_graphics(innate_subsystem::BitmapInterface * pbitmap)
   {

      construct_newø(m_pdevicecontext);

      m_pdevicecontext->initialize_device_context(pbitmap);

   }

   void Graphics::setBkMode(bool transparent)
   {
      //m_iBkMode = transparent ? WIN32_TRANSPARENT : WIN32_OPAQUE;
//      SetBkMode(m_pdevicecontext->m_hdc, transparent ? TRANSPARENT : OPAQUE);

   }


   void Graphics::setBlendModeOn(bool bSet)
   {
      
      m_pcgcontext->set_blend_mode_on(bSet);

//      if (bSet)
//      {
//         m_pdevicecontext->m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
//
//      }
//      else
//      {
//         m_pdevicecontext->m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
//
//      }

   }

   void Graphics::setAntiAliasOn(bool bOn)
   {

      if (bOn)
      {
         
         m_pcgcontext->set_anti_alias_on(true);       //m_pdevicecontext->m_pgraphics->SetSmoothingMode//(Gdiplus::SmoothingModeAntiAlias);

      }
      else
      {
         m_pcgcontext->set_anti_alias_on(false);
         //m_pdevicecontext->m_pgraphics->SetSmoothingMode(Gdiplus::SmoothingModeNone);

      }

   }


   void Graphics::setTextColor(const ::color::color & color)
   {
      m_colorText= color;
      //SetTextColor(m_pdevicecontext->m_hdc, RGB(color.byte_red(), color.byte_green(), color.byte_blue()));
   }


   void Graphics::setTextRenderingHintClearType()
   {

      //m_pdevicecontext->m_pgraphics->SetTextRenderingHint(::Gdiplus::TextRenderingHintClearTypeGridFit);

   }

   void Graphics::setBkColor(const ::color::color & color)
   {
      //SetBkColor(m_pdevicecontext->m_hdc, RGB(color.byte_red(), color.byte_green(), color.byte_blue()));
      m_colorBk = color;
   }

   void Graphics::setBrush(::innate_subsystem::BrushInterface *pbrush)
   {

      // auto pbrushWin32 = pbrush->impl<Brush>();
      //
      // HGDIOBJ object = pbrushWin32 ? pbrushWin32->m_hbrush : nullptr;
      //
      //m_pdevicecontext->selectObject(pbrush);
      m_pbrush = pbrush;

   }

   void Graphics::setPen(::innate_subsystem::PenInterface *ppen)
   {

      // ::cast < ::innate_subsystem_macos::Pen > ppenWin32 = ::innate_subsystem::get_implementation(ppen);
      //
      // HGDIOBJ object = ppenWin32 ? ppenWin32->m_hpen : nullptr;
      //
      //m_pdevicecontext->selectObject(ppen);
      m_ppen = ppen;
      
      m_pcgcontext->set_line_width(m_ppen->m_iWidth);
      m_pcgcontext->set_stroke_color(m_ppen->m_pcgcolor);

   }

   void Graphics::setFont(::innate_subsystem::FontInterface *pfont)
   {

      // ::cast < ::innate_subsystem_macos::Pen > ppenWin32 = ::innate_subsystem::get_implementation(ppen);
      //
      // HGDIOBJ object = ppenWin32 ? ppenWin32->m_hpen : nullptr;
      //
      //m_pdevicecontext->selectObject(ppen);
      m_pfont = pfont;

   }


   void Graphics::moveTo(const ::i32_point & point)
   {
      //MoveToEx(m_pdevicecontext->m_hdc, x, y, NULL);
      m_pointCurrent = point;
      //m_pointCurrent.y = y;
   }

   void Graphics::lineTo(const ::i32_point & point)
   {
      
      //set_pen(m_ppen);
      m_pcgcontext->draw_line(m_pointCurrent, point);
      m_pointCurrent = point;
//      //LineTo(m_pdevicecontext->m_hdc, x, y);
//      m_pdevicecontext->m_pgraphics->DrawLine(m_ppen->m_ppen, m_pointCurrent.x, m_pointCurrent.y, point.x, point.y);
//      m_pointCurrent = point;
//      //m_pointCurrent.y = y;

   }

   void Graphics::fillRect(const ::i32_rectangle & rectangle, ::innate_subsystem::BrushInterface *pbrush)
   {
//      Gdiplus::Rect gdiplusrect;
//
//      ::copy(gdiplusrect, rectangle);
//
      auto pbrushMacos = pbrush->impl<::innate_subsystem_macos::Brush>();
//      
      //set
      
      m_pcgcontext->set_fill_color(pbrushMacos->m_pcgcolor);

      //auto hbrush = (HBRUSH) pbrush->_HGDIOBJ();
      
      m_pcgcontext->fill_rect(rectangle);

//m_pdevicecontext->m_pgraphics->FillRectangle(pbrushWin32->m_pbrush, gdiplusrect);
      //FillRect(m_pdevicecontext->m_hdc, &rect, hbrush);

   }

// Sets current brush to the device context.
void Graphics::_set_brush(::innate_subsystem::BrushInterface * pbrush)
{
   
   auto pbrushMacos = pbrush->impl<::innate_subsystem_macos::Brush>();
   m_pcgcontext->set_fill_color(pbrushMacos->m_pcgcolor);
   
}
// Sets current pen to the device context.
void Graphics::_set_pen(::innate_subsystem::PenInterface * ppen)
{
   
   
   auto ppenMacos = ppen->impl<::innate_subsystem_macos::Pen>();
   m_pcgcontext->set_line_width(ppenMacos->m_iWidth);
   m_pcgcontext->set_stroke_color(ppenMacos->m_pcgcolor);
}



   void Graphics::fillRect(const ::i32_rectangle & rectangle, const ::color::color & color)
   {
      //Gdiplus::Rect gdiplusrect;

     // ::copy(gdiplusrect, rectangle);

      //auto pbrushMacos = create_newø<::innate_subsystem_macos::Brush>();
      
      auto pcgcolor = CoreGraphics().create_color(color);
      
      //Gdiplus::Color gdipluscolor(color.byte_opacity(), color.byte_red(), color.byte_green(), color.byte_blue());
      //Gdiplus::SolidBrush solidbrush(gdipluscolor);
      
      m_pcgcontext->set_fill_color(pcgcolor);
      

      //auto hbrush = (HBRUSH) pbrush->_HGDIOBJ();

      m_pcgcontext->fill_rect(rectangle);
      //m_pdevicecontext->m_pgraphics->FillRectangle(&solidbrush, gdiplusrect);
      //FillRect(m_pdevicecontext->m_hdc, &rect, hbrush);

   }

   void Graphics::ellipse(const ::i32_rectangle & rectangle)
   {
      //Ellipse(m_pdevicecontext->m_hdc, l, t, r, b);
//      Gdiplus::Rect gdiplusrect;
//
//      ::copy(gdiplusrect, rectangle);
//      // gdiplusrect.X = t;
//      // gdiplusrect.Y = l;
//      // gdiplusrect.Width = r-l;
      if(m_pbrush)
      {
         _set_brush(m_pbrush);
         m_pcgcontext->fill_ellipse(rectangle);
         
      }
      if(m_ppen)
      {
         _set_pen(m_ppen);
         m_pcgcontext->draw_ellipse(rectangle);
      }
//      m_pdevicecontext->m_pgraphics->FillEllipse(m_pbrush->m_pbrush, gdiplusrect);
//      m_pdevicecontext->m_pgraphics->DrawEllipse(m_ppen->m_ppen, gdiplusrect);
   }

   void Graphics::rectangle(const ::i32_rectangle & rectangle)
   {
      //Rectangle(m_pdevicecontext->m_hdc, l, t, r, b);
//      Gdiplus::Rect gdiplusrect;

  //    ::copy(gdiplusrect, rectangle);
      // gdiplusrect.X = t;
      // gdiplusrect.Y = l;
      // gdiplusrect.Width = r-l;
      if(m_pbrush)
      {
         _set_brush(m_pbrush);
         m_pcgcontext->fill_rect(rectangle);
      }
      //m_pdevicecontext->m_pgraphics->FillRectangle(m_pbrush->m_pbrush, gdiplusrect);
      if(m_ppen)
      {
         _set_pen(m_ppen);
         //m_pdevicecontext->m_pgraphics->DrawRectangle(m_ppen->m_ppen, gdiplusrect);
         m_pcgcontext->draw_ellipse(rectangle);
      }

   }

   void Graphics::drawBitmap(::innate_subsystem::BitmapInterface *pbitmap, const ::i32_rectangle & rectangle)
   {

      auto pbitmapMacos = pbitmap->impl<::innate_subsystem_macos::Bitmap>();
      //DeviceContext memDC;

      //memDC.initialize_device_context(m_pdevicecontext);

      //Gdiplus::Rect gdiplusrect;

      //::copy(gdiplusrect, rectangle);

      m_pcgcontext->draw_image(pbitmapMacos->m_pcgimage, rectangle);
      //auto pobjOld = memDC.selectObject(pbitmap);
      //m_pdevicecontext->m_pgraphics->DrawImage(pbitmapWin32->m_pbitmap, gdiplusrect);

      //BitBlt(m_pdevicecontext->m_hdc, x, y, w, h, memDC.m_hdc, 0, 0, SRCCOPY);

      //memDC.selectObject(pobjOld);
   }


   void Graphics::drawBitmap(::innate_subsystem::BitmapInterface *pbitmap, const ::i32_point & point, const ::i32_rectangle & rectangle)
   {

      auto pbitmapMacos = pbitmap->impl<::innate_subsystem_macos::Bitmap>();
      
      m_pcgcontext->draw_image(pbitmapMacos->m_pcgimage, point, rectangle);

//      m_pdevicecontext->m_pgraphics->DrawImage(pbitmapWin32->m_pbitmap,
//         point.x, point.y,
//         rectangle.left, rectangle.top,
//         rectangle.width(), rectangle.height(),
//         Gdiplus::UnitPixel);

   }

   void Graphics::_defer_text_tools()
   {

      if (!m_pfont)
      {

         constructø(m_pfont);

         m_pfont->initialize_font("Arial", 14);

      }
      if (!m_pbrushText || m_colorBrushText != m_colorText)
      {
         if (m_pbrushText)
         {

            delete m_pbrushText;
            m_pbrushText = nullptr;
         }
         auto color = m_colorText;
         m_colorBrushText = color;
         
         m_pbrushText = InnateSubsystem().createSolidBrush(color);
        // Gdiplus::Color gdipluscolor(color.byte_opacity(), color.byte_red(), color.byte_green(), color.byte_blue());
         //m_pbrushText = new Gdiplus::SolidBrush(gdipluscolor);

      }

   }

   void Graphics::drawText(const char *text, int cchText, ::i32_rectangle &rectangle, unsigned int format, enum_align ealign)
   {

      ::string str;

      if (cchText >= 0)
      {

         str.assign(text, cchText);

      }
      else
      {

         str = text;

      }

//      ::wstring wstr(str);
//
//      Gdiplus::RectF gdiplusrect;
//
//      ::copy(gdiplusrect, rectangle);
//
//      _defer_text_tools();
//
//      // Create string format
//     Gdiplus:: StringFormat stringFormat(Gdiplus::StringFormat::GenericTypographic());
//
//      if (ealign & e_align_right)
//      {
//         stringFormat.SetAlignment(Gdiplus::StringAlignmentFar);
//      }
//      else if (ealign & e_align_horizontal_center)
//      {
//         // Horizontal alignment (center)
//         stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
//      }
//      else
//      {
//         stringFormat.SetAlignment(Gdiplus::StringAlignmentNear);
//
//      }
//      if (ealign & e_align_bottom)
//      {
//         stringFormat.SetLineAlignment(Gdiplus::StringAlignmentFar);
//      }
//      else if (ealign & e_align_vertical_center)
//      {
//         // Vertical alignment (center)
//         stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
//      }
//      else
//      {
//         stringFormat.SetLineAlignment(Gdiplus::StringAlignmentNear);
//
//      }
//
//
//      // Optional: prevent wrapping
//      stringFormat.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);
//
//      stringFormat.SetFormatFlags(Gdiplus::StringFormatFlagsNoClip);
//      //
//      // RECT rc;
//      // ::copy(rc, rect);
//      // DrawText(m_pdevicecontext->m_hdc, wstr, wstr.length(), &rc, format);
//      m_pdevicecontext->m_pgraphics->DrawString(wstr, wstr.length(), m_pfont->m_pfont, gdiplusrect, &stringFormat, m_pbrushText);
   }

   
} // namespace innate_subsystem_macos


