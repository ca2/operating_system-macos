//
//  _struct.h
//  appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/26.
//

#pragma once


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
      
            
   };


   struct ns_window_t : public ::appkit_type {};
   struct ns_image_t : public ::appkit_type {};



} // namespace appkit
