﻿#include "framework.h"


namespace coreimage_imaging
{


   bool image_from_coreimage(::image * pimage, FIBITMAP * pfibitmap)
   {

      if (pfibitmap == nullptr)
      {

         return false;

      }

      FIBITMAP * image32 = FreeImage_ConvertTo32Bits(pfibitmap);

      if (image32 == nullptr)
      {

         return false;

      }

      int w = FreeImage_GetWidth(image32);

      int h = FreeImage_GetHeight(image32);

      if (!pimage->create({ w, h}))
      {

         return false;

      }

      void * pdata = FreeImage_GetBits(image32);

      int iSrcScan = FreeImage_GetPitch(image32);

      int iLineSize = w * sizeof(color32_t);

      pimage->map();

#if defined(ANDROID)

      for (index y = 0; y < pimage->height(); y++)
      {

         unsigned char * pbDst = ((unsigned char *)pimage->get_data()) + ((pimage->height() - y - 1) * pimage->scan_size());

         unsigned char * pbSrc = (unsigned char *)pdata + (y * iSrcScan);

         for (index x = 0; x < pimage->width(); x++)
         {

            pbDst[0] = pbSrc[2];

            pbDst[1] = pbSrc[1];

            pbDst[2] = pbSrc[0];

            pbDst[3] = pbSrc[3];

            pbDst += 4;

            pbSrc += 4;

         }

      }

#elif defined(APPLEOS)

      unsigned char * pbDst = (unsigned char *)pimage->get_data();

      unsigned char * pbSrc = (unsigned char *)pdata;

      ::collection::count c = (count)pimage->area();

      while (c-- > 0)
      {

         pbDst[0] = pbSrc[2];

         pbDst[1] = pbSrc[1];

         pbDst[2] = pbSrc[0];

         pbDst[3] = pbSrc[3];

         pbDst += 4;

         pbSrc += 4;

      }


#else

      for (int i = 0; i < pimage->height(); i++)
      {

         ::memcpy_dup(
            &((unsigned char *)pimage->get_data())[pimage->scan_size() * (h - i - 1)],
            &((unsigned char *)pdata)[iSrcScan * i],
            iLineSize);

      }

#endif

      pimage->mult_alpha_fast();

      FreeImage_Unload(image32);

      return true;

   }





   namespace draw2d
   {


      void free_FreeImage(FIBITMAP * pfibitmap)
      {

#ifdef _UWP

         throw ::exception(todo);;

#else
         FreeImage_Unload(pfibitmap);
#endif
      }


   }



   /*FIBITMAP * imaging::LoadImageFile(CArchive & ar)
   {
   ASSERT(!ar.IsStoring());

   return LoadImageFile(ar.GetFile());

   }
   */
   /*HBITMAP imaging::LoadBitmap(
   const char * pszType,

   const char * pszId)

   {
   ::exception::throw_not_implemented();

   ::memory_file file(this);

   ::aura::Resource resource;

   if(!resource.ReadResource(*file.get_memory(), (unsigned int) MAKEINTRESOURCE(pszId), pszType))

   return false;

   file.seek_to_begin();

   file_pointer  pfile = &file;

   FreeImageIO io;
   io.read_proc   = ___Ex1File__ReadProc;
   io.seek_proc   = ___Ex1File__SeekProc;
   io.tell_proc   = ___Ex1File__TellProc;
   io.write_proc  = ___Ex1File__WriteProc;

   FREE_IMAGE_FORMAT format;
   format = FreeImage_GetFileTypeFromHandle(&io, pfile ,16);
   FIBITMAP *pfi = nullptr;
   if(true)
   {
   pfi = FreeImage_LoadFromHandle(format, &io, pfile);
   }

   if(pfi == nullptr)
   return nullptr;

   BITMAPINFO * pbi = FreeImage_GetInfo(pfi);
   void * pData = FreeImage_GetBits(pfi);


   HDC hdcSource = CreateDC(
   "DISPLAY",
   nullptr,
   nullptr,
   nullptr);

   HBITMAP hBitmapSource = ::CreateCompatibleBitmap(
   hdcSource,
   pbi->bmiHeader.biWidth,
   pbi->bmiHeader.biHeight);

   if(pbi->bmiHeader.biHeight != SetDIBits(
   hdcSource,
   hBitmapSource,
   0,
   pbi->bmiHeader.biHeight,
   pData,
   pbi,
   DIB_RGB_COLORS))
   {
   FreeImage_Unload(pfi);
   DeleteDC(hdcSource);
   delete_object(hBitmapSource);
   return nullptr;
   }

   FreeImage_Unload(pfi);
   DeleteDC(hdcSource);

   return hBitmapSource;
   */
   //}
   //*/


   //#endif // WINDOWS_DESKTOP





   ::e_status imaging::_load_image(::handler_context * pcontext, ::image * pimage, const ::payload & varFile, bool bSync, bool bCreateHelperMaps)
   {

      auto pmemory = create_memory();

      {

         auto tmp = varFile.get_file_path();

         if (tmp.case_insensitive_ends(".gif"))
         {

            output_debug_string("GIF!!");

         }

      }

      papplication->file().as_memory(varFile, *pmemory);

      const char * psz = (const char *)pmemory->get_data();

      if (::is_null(psz))
      {

         return pimage->m_estatus;

      }

      if (::is_null(pimage))
      {

         return false;

      }

      if (pmemory->is_empty())
      {

         return false;

      }

      auto estatus = psystem->imaging().load_svg(pimage, pmemory);

      if (::succeeded(estatus))
      {

         return estatus;

      }

      if (pmemory->get_size() > 3 && strnicmp(psz, "gif", 3) == 0)
      {

         if (!pimage->_defer_load_multi_frame_image_(pmemory))
         {

            pimage->set_nok();

            return pimage->m_estatus;

         }

         pimage->on_load_image();

         pimage->set_ok();

         pimage->m_estatus = ::success;

         return pimage->m_estatus;

      }

      FIMEMORY * pmem = FreeImage_OpenMemory(pmemory->get_data(), (unsigned int) pmemory->get_size());

      if (pmem == nullptr)
      {

         return false;

      }

      FIBITMAP * pfibitmap = nullptr;

      try
      {


         FREE_IMAGE_FORMAT format;

         format = FreeImage_GetFileTypeFromMemory(pmem);

         pfibitmap = FreeImage_LoadFromMemory(format, pmem);

      }
      catch (...)
      {

      }

      if (pfibitmap == nullptr)
      {

         FreeImage_CloseMemory(pmem);

         return false;

      }

      int iExifOrientation = -1;

      bool bOrientation = false;

      FITAG * tag = nullptr;

      FIMETADATA * mdhandle = FreeImage_FindFirstMetadata(FIMD_EXIF_MAIN, pfibitmap, &tag);

      if (mdhandle)
      {

         do
         {

            if (!_stricmp(FreeImage_GetTagKey(tag), "orientation"))
            {

               bOrientation = true;

               auto type = FreeImage_GetTagType(tag);

               if (type == FIDT_SHORT)
               {

                  auto value = FreeImage_GetTagValue(tag);

                  iExifOrientation = *((unsigned short *)value);

                  pimage->m_iExifOrientation = iExifOrientation;

               }

            }

            if (bOrientation)
            {

               break;

            }

         }

         while (FreeImage_FindNextMetadata(mdhandle, &tag));

         FreeImage_FindCloseMetadata(mdhandle);

      }

      if (!image_from_coreimage(pimage, pfibitmap))
      {

         FreeImage_Unload(pfibitmap);

         FreeImage_CloseMemory(pmem);

         return false;

      }

      FreeImage_Unload(pfibitmap);

      FreeImage_CloseMemory(pmem);


      //   if (iExifOrientation >= 0)
      //   {
      //
      //      ::image_pointer pimage2;
      //
      //      //double dPiQuarter = ::atan(1.0);
      //
      //      //double dPi = dPiQuarter * 4.0;
      //
      //      // http://sylvana.net/jpegcrop/exif_orientation.html
      //      //1) transform = "";;
      //      //2) transform = "-flip horizontal";;
      //      //3) transform = "-rotate 180";;
      //      //4) transform = "-flip vertical";;
      //      //5) transform = "-transpose";;
      //      //6) transform = "-rotate 90";;
      //      //7) transform = "-transverse";;
      //      //8) transform = "-rotate 270";;
      //      //*) transform = "";;
      //      switch (iExifOrientation)
      //      {
      //      case 2:
      //         pimage2->flip_horizontal(pimage);
      //         pimage->from(pimage2);
      //         break;
      //      case 3:
      //         pimage2->rotate(pimage, 180.0);
      //         pimage->from(pimage2);
      //         break;
      //      case 4:
      //         pimage2->flip_vertical(pimage);
      //         pimage->from(pimage2);
      //         break;
      //      case 5:
      //         pimage2->flip_horizontal(pimage);
      //         pimage->rotate(pimage2, -270.0);
      //         break;
      //      case 6:
      //         pimage2->rotate(pimage, -90.0);
      //         pimage->from(pimage2);
      //         break;
      //      case 7:
      //         pimage2->flip_horizontal(pimage);
      //         pimage->rotate(pimage2, -90.0);
      //         break;
      //      case 8:
      //         pimage2->rotate(pimage, -270.0);
      //         pimage->from(pimage2);
      //         break;
      //      case 1:
      //      default:
      //         break;
      //
      //      }
      //
      //   }

      pimage->on_load_image();

      pimage->set_ok();

      pimage->m_estatus = ::success;

      return pimage->m_estatus;

   }


} // namespace coreimage_imaging





   //bool os_init_imaging()
   //{

   //   FreeImage_Initialise(false);

   //   return true;
   //}


   //void os_term_imaging()
   //{

   //   FreeImage_DeInitialise();


   //}
