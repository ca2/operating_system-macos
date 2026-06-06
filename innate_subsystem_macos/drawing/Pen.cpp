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
#include "Pen.h"
#include "acme/nano/graphics/pen.h"
#include "operating_system-apple/core_graphics/core_graphics.h"
//#include <crtdbg.h>


namespace innate_subsystem_macos
{


   // Pen::Pen(::innate_subsystem::enum_pennt type, int width, COLORREF color)
   // : m_pen(NULL)
   // {
   //    m_pen = CreatePen(type, width, color);
   //
   //    ASSERT(m_pen != NULL);
   // }

   Pen::Pen()//:
//   m_hpen(nullptr)
   //m_ppen(nullptr)
   {
      //m_elinecapStart = ::nano::graphics::e_line_cap_none;
      //m_elinecapEnd = ::nano::graphics::e_line_cap_none;
      
   }


   Pen::~Pen()
   {

      destroyGraphicsObject();

   }


   // void * Pen::_HGDIOBJ()
   // {
   //
   //    return m_hpen;
   //
   // }

   void Pen::initialize_pen(::nano::graphics::enum_pen epen, ::f64 fWidth, const color::color& color)
   {

      destroyGraphicsObject();
      
      defer_constructø(m_ppen);
      
      m_ppen->create_pen(epen, fWidth, color);
      
      //m_iWidth = width;
      
      //m_pcgcolor = CoreGraphics().create_color(color);

      //m_hpen = CreatePen((int) epen, width, RGB(color.byte_red(), color.byte_green(), color.byte_blue()));
//
//      Gdiplus::Color gdipluscolor(color.byte_opacity(), color.byte_red(), color.byte_green(), color.byte_blue());
//
//      m_ppen = new Gdiplus::Pen(gdipluscolor, width);
//
//      if (!m_ppen || m_ppen->GetLastStatus() != Gdiplus::Ok)
//      {
//
//         throw ::exception(error_failed);
//
//      }

   }


void Pen::setStartCap(::nano::graphics::enum_line_cap elinecap)
{
   
   m_ppen->set_start_cap(elinecap);
   //m_elinecapStart = elinecap;
   
}
void Pen::setEndCap(::nano::graphics::enum_line_cap elinecap)
{
   
   m_ppen->set_end_cap(elinecap);
   //m_elinecapEnd = elinecap;
   
}


   void Pen::destroyGraphicsObject()
   {

//      if (m_ppen)
//      {
//
//         delete m_ppen;
//
//         m_ppen = nullptr;
//
//      }

      // if (m_hpen)
      // {
      //    ::DeleteObject(m_hpen);
      //    m_hpen= nullptr;
      // }

   }


} // namespace innate_subsystem_macos


