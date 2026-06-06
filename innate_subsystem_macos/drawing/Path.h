// Created by camilo on 2026-06-04 19:22 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "innate_subsystem/drawing/Path.h"


namespace innate_subsystem_macos
{


   class CLASS_DECL_INNATE_SUBSYSTEM_MACOS Path :
      virtual public Implementation< ::innate_subsystem::PathInterface >
   {
   public:

      ::pointer < ::core_graphics::cg_path > m_pcgpath;
      
      CGMutablePathRef m_ppath;
      
      Path();
      ~Path();

      virtual void addArc(::f64 x, ::f64 y, ::f64 w, ::f64 h, const ::f64_angle &angleStart,
                           const ::f64_angle &angleSweep) override;

      virtual void closeFigure() override;


     
   };


} // namespace innate_subsystem_macos
