﻿#include "framework.h"
#include <math.h>


struct FIBITMAP;


namespace coreimage_imaging
{


   //bool draw2d_gif_load_frame(::image * pimageCompose, image_frame_array * pframea, image_frame * pointer, ::collection::index uFrameIndex, unsigned char * ba, int iScan, colorref_array & cra, int transparentIndex);

   bool coreimage_load_imagea_frame(::image * pimageCompose, image_frame_array * pimagea, index iFrame, FIBITMAP * pfi);

   ::e_status imaging::_load_image(::image * pimageCompose, ::pointer < image_frame_array > & pframea, ::memory_pointer pmemory)
   {

      fimemory mem(*pmemory);

      if (!mem)
      {

         return false;

      }

      FIMULTIBITMAP * m = nullptr;

      try
      {

         FREE_IMAGE_FORMAT format = mem.get_image_format();

         //if (true)
         {

            m = FreeImage_LoadMultiBitmapFromMemory(format, mem);

            try
            {

               ::collection::count cFrame = FreeImage_GetPageCount(m);

               for (index iFrame = 0; iFrame < cFrame; iFrame++)
               {

                  auto pframe = __new(image_frame);

                  pframea->add(pframe);

                  __øconstruct(pframe->m_pimage);

                  pframe->m_iFrame = iFrame;

                  FIBITMAP * pfi = FreeImage_LockPage(m, (int)iFrame);

                  if (pfi != nullptr)
                  {

                     int w = FreeImage_GetWidth(pfi);

                     int h = FreeImage_GetHeight(pfi);

                     FITAG * ptag;

                     if (iFrame <= 0)
                     {

                        if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "LogicalWidth", &ptag))
                        {

                           if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                           {

                              pframea->m_size.cx() = *((short *)FreeImage_GetTagValue(ptag));

                           }

                        }

                        if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "LogicalHeight", &ptag))
                        {

                           if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                           {

                              pframea->m_size.cy() = *((short *)FreeImage_GetTagValue(ptag));

                           }

                        }

                        if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "GlobalPalette", &ptag))
                        {

                           if (FreeImage_GetTagType(ptag) == FIDT_PALETTE)
                           {

                              cra_from_quada(pframea->m_colorrefa, (RGBQUAD *)FreeImage_GetTagValue(ptag), FreeImage_GetTagCount(ptag));

                           }

                        }

                        if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "Loop", &ptag))
                        {

                           if (FreeImage_GetTagType(ptag) == FIDT_LONG)
                           {

                              pframea->m_countLoop = (unsigned int)*((long *)FreeImage_GetTagValue(ptag));

                           }

                        }

                        pimageCompose->create(pframea->m_size);

                        pimageCompose->fill(0);

                     }

                     pframe->m_rect.left = 0;

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameLeft", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                        {

                           pframe->m_rect.left = *((short *)FreeImage_GetTagValue(ptag));

                        }

                     }
                     
                     pframe->m_rect.right = pframe->m_rect.left + w;

                     pframe->m_rect.top = 0;

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameTop", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                        {

                           pframe->m_rect.top = *((short *)FreeImage_GetTagValue(ptag));

                        }

                     }

                     pframe->m_rect.bottom = pframe->m_rect.top + h;

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "NoLocalPalette", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_BYTE)
                        {

                           pframe->m_bLocalPalette = *((unsigned char *)FreeImage_GetTagValue(ptag)) == 0;

                        }

                     }

                     pframe->m_edisposal = draw2d::disposal_undefined;

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "DisposalMethod", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_BYTE)
                        {

                           auto iDisposal = *((unsigned char *)FreeImage_GetTagValue(ptag));

                           pframe->gif_set_disposal(iDisposal);

                        }

                     }

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameTime", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_LONG)
                        {

                           pframe->m_tick = (unsigned int) * ((long *)FreeImage_GetTagValue(ptag));

                        }

                     }

                     if (!coreimage_load_imagea_frame(pimageCompose, pframea, iFrame, pfi))
                     {

                        output_debug_string("failed to load page image");

                     }

                  }

               }

            }
            catch (...)
            {

            }

            FreeImage_CloseMultiBitmap(m);

         }

      }
      catch (...)
      {
         return false;

      }

      return true;

   }


   bool coreimage_load_imagea_frame(image * pimageCompose, image_frame_array * pframea, index iFrame, FIBITMAP * pfi)
   {

      if (pfi == nullptr)
      {

         return false;

      }

      image_frame * pframe = pframea->element_at(iFrame);

      //BITMAPINFO * pbi = nullptr;

      //void * pdata = nullptr;

      //pbi = FreeImage_GetInfo(pfi);

      //pdata = FreeImage_GetBits(pfi);

      //int w = FreeImage_GetWidth(pfi);

      //int h = FreeImage_GetHeight(pfi);

      image_pointer pimageFrame;

      auto estatus = __øconstruct(pimageFrame);

      if (!estatus || !pimageFrame)
      {

         return false;

      }

      image_from_coreimage(pimageFrame, pfi);

      ::draw2d::e_disposal edisposal = iFrame <= 0 ? ::draw2d::disposal_none : pframea->element_at(iFrame)->m_edisposal;

      pframe->m_edisposal = edisposal;

      pframe->_001Process(pimageCompose, pimageFrame, pframea);


//      int transparentIndex = FreeImage_GetTransparentIndex(pfi);
//
//      bool bIsTransparent = FreeImage_IsTransparent(pfi) != 0;
//
//      if (!bIsTransparent)
//      {
//
//         transparentIndex = -1;
//
//      }
//
//      RGBQUAD quad;
//
//      if (FreeImage_GetBackgroundColor(pfi, &quad))
//      {
//
//         output_debug_string("has background color");
//
//      }
//
//      int iScan = FreeImage_GetPitch(pfi);
//
//      if (FreeImage_GetBPP(pfi) == 8)
//      {
//
//         if (pframe->m_bLocalPalette && pbi->bmiHeader.biClrUsed > 0)
//         {
//
//            colorref_array cra;
//
//            cra_from_quada(cra, pbi->bmiColors, pbi->bmiHeader.biClrUsed);
//
//            /*if (!draw2d_gif_load_frame(pimageCompose, pframea, pframe, iFrame, (unsigned char *)pdata, iScan, cra, transparentIndex))
//            {
//
//               return false;
//
//            }*/
//
//         }
//         else
//         {
//
//#if defined(ANDROID) && defined(__arm__)
//
//            color32_t crQuad = argb(255, quad.rgbRed, quad.rgbGreen, quad.rgbBlue);
//
//#else
//
//            //color32_t crQuad = argb(255, quad.rgbBlue, quad.rgbGreen, quad.rgbRed);
//
//#endif
//
//            //if (!draw2d_gif_load_frame(pimageCompose, pframea, pframe, iFrame, (unsigned char *)pdata, iScan, pframea->m_colorrefa, transparentIndex))
//            //{
//
//            //   return false;
//
//            //}
//
//         }
//
//      }
//      else if (FreeImage_GetBPP(pfi) == 32)
//      {
//
//         ::copy_image32(pframe->m_pimage->colorref(), pframe->m_pimage->width(), pframe->m_pimage->height(), pframe->m_pimage->scan_size(), (color32_t *)pdata, iScan);
//
//         return true;
//
//      }
//      else
//      {
//
//         return false;
//
//      }

      return true;

   }


} // namespace coreimage_imaging



