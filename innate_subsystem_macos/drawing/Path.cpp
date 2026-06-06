// Created by camilo on 2026-06-04 19:27 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "Path.h"



namespace innate_subsystem_macos
{

Path::Path()
{
   m_ppath = CGPathCreateMutable();
   
}

Path::~Path()
{
   
   if(m_ppath)
   {
      
      CGPathRelease(m_ppath);
      
   }
   
}

void Path::addArc(::f64 x, ::f64 y, ::f64 w, ::f64 h, const ::f64_angle &angleStart,
       const ::f64_angle &angleSweep)
{
   
   CGRect rect = CGRectMake(x, y, w, h);

   CGFloat cx = rect.origin.x + rect.size.width  / 2.0;
   CGFloat cy = rect.origin.y + rect.size.height / 2.0;

   CGFloat rx = rect.size.width  / 2.0;
   CGFloat ry = rect.size.height / 2.0;

   CGAffineTransform t =
       CGAffineTransformTranslate(
           CGAffineTransformIdentity,
           cx,
           cy);

   t = CGAffineTransformScale(t, rx, ry);

   auto angleEnd = angleStart + angleSweep;
   
   auto fStartRad = angleStart.radians();
   
   auto fEndRad = angleEnd.radians();
   
   bool clockwise = angleSweep > 0.;

   CGPathAddArc(
       m_ppath,
       &t,
       0.0,
       0.0,
       1.0,
       fStartRad,
       fEndRad,
       clockwise);
   
}


void Path::closeFigure()
{
   
   CGPathCloseSubpath(m_ppath);
   
}


} // namespace innate_subsystem_macos



