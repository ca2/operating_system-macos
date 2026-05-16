//
//  _struct.h
//  appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/26.
//

#pragma once

#include "acme/operating_system/macos/window.h"

namespace appkit
{

   struct appkit_type
   {
      
      void * m_p = nullptr;
      
      bool is_set() const
      {
         
         return m_p != nullptr;
         
      }
      
      
      bool is_null() const
      {
         
         return !this->is_set();
         
      }
      
      
      void clear()
      {
         
         m_p = nullptr;
         
      }
      operator ::hash32() const
      {
         return ::as_hash32((::uptr)this->m_p);
      }

bool operator == (const appkit_type & t) const
      {
   
   return t.m_p == m_p;
   
}
            
   };


   struct ns_window_t : public appkit_type {
      
      
      ns_window_t() = default;
      ns_window_t(const ns_window_t &) = default;
      ns_window_t(void * p)
      {
         m_p = p;
         
      }
      ns_window_t(const ::operating_system::window & operatingsystemwindow)
      {
         if(operatingsystemwindow.m_eoperatingambient == ::windowing::e_operating_ambient_macos
            || operatingsystemwindow.m_eoperatingambient == ::windowing::e_operating_ambient_macos_impact)
         {
            m_p = (void*) operatingsystemwindow.m_opaque.m_ulla[0];
         }
         else
         {
            m_p = nullptr;
         }
         
      }
      
      ::operating_system::macos_window as_macos_window() const
      {
         
         return {(::uptr) m_p};
         
      }
            
      
   };
   struct ns_image_t : public appkit_type {};


struct ns_impact_t
{
   
   void * m_p = nullptr;
   ::u64 m_uTag = 0;
   
   ns_impact_t()
   {
      
   }
   
   ns_impact_t(const ::operating_system::window & operatingsystemwindow)
   {
      
      if(operatingsystemwindow.m_eoperatingambient != ::windowing::e_operating_ambient_macos_impact)
      {
         
         //throw ::exception(error_wrong_type);
         m_p = nullptr;
         m_uTag = 0;
         
      }
      else
      {
         
         m_p = (void *) operatingsystemwindow.m_opaque.m_ulla[0];
         m_uTag = operatingsystemwindow.m_opaque.m_ulla[1];
         
      }
      
   }
   
   bool is_set() const
   {
      
      return m_p != nullptr;
      
   }
   
   
   bool is_null() const
   {
      
      return !this->is_set();
      
   }
   
   
   void clear()
   {
      
      m_p = nullptr;
      m_uTag = 0;
      
   }
   operator ::hash32() const
   {
      return ::as_hash32((::uptr)this->m_p)+::as_hash32((::uptr)this->m_uTag);
   }

bool operator == (const ns_impact_t & t) const
   {

return t.m_p == this->m_p && t.m_uTag == this->m_uTag;

}
   
   ns_window_t ns_window() const
   {
    
      return {m_p};
      
   }
   
   ::operating_system::macos_window as_macos_window() const
   {
      
      return {(::uptr) m_p, m_uTag};
      
   }
         
};



} // namespace appkit
