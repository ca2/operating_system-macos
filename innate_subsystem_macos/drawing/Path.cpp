// Created by camilo on 2026-06-04 19:27 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "Path.h"
#include "operating_system-apple/core_graphics/cg_affine_transform.h"
#include "operating_system-apple/core_graphics/cg_path.h"


namespace innate_subsystem_macos
{

Path::Path()
{
   //m_ppath = CGPathCreateMutable();
   
      
}

Path::~Path()
{
   
//   if(m_ppath)
//   {
//      
//      CGPathRelease(m_ppath);
//      
//   }
   
}

void Path::addArc(::f64 x, ::f64 y, ::f64 w, ::f64 h, const ::f64_angle &angleStart,
       const ::f64_angle &angleSweep)
{
   
   
   defer_constructø(m_ppath);
   
   m_ppath->add_arc(x, y, w, h, angleStart, angleSweep);
   
//   auto paffinetransform = create_newø<cg_affine_transform >();
//   
//   auto rectangle = ::f64_rectangle_dimension(x, y, w, h);
//   
//   auto pointCenter = rectangle.center();
//
//   auto sizeRadius = rectangle.radius();
//   
//   paffinetransform->translate(pointCenter);
//
//   paffinetransform->scale(sizeRadius);
//
//   auto angleEnd = angleStart + angleSweep;
//   
//   auto fStartRad = angleStart.radians();
//   
//   auto fEndRad = angleEnd.radians();
//   
//   bool clockwise = angleSweep > 0.;
//
////   CGPathAddArc(
////       m_ppath,
////       &t,
////       0.0,
////       0.0,
////       1.0,
////       fStartRad,
////       fEndRad,
////       clockwise);
//   
//   m_ppath->add_arc(paffinetransform, 0., 0., 1., fStartRad, fEndRad, clockwise);
   
}


void Path::closeFigure()
{
   
   m_ppath->close_figure();
   
}


} // namespace innate_subsystem_macos



