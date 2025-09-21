#pragma once


#include "acme/filesystem/filesystem/directory_context.h"


namespace acme_macos
{


   class CLASS_DECL_ACME_MACOS directory_context :
      virtual public ::directory_context
   {
   public:
      

      pointer < ::acme_macos::directory_system >      m_pdirsystem;
      pointer < ::acme_macos::file_system >     m_pfilesystem;

      
      directory_context();
      ~directory_context() override;

      
      void initialize(::particle * pparticle) override;

      void init_system() override;

      // rls fetchs should set a meaningful m_iRelative value at each returned path
      bool enumerate(::file::listing_base & path) override;


      //virtual bool  is(const ::file::path & path) override;
      virtual bool  is_inside(const ::file::path & pathFolder,const ::file::path & path) override;
      virtual bool  is_inside_time(const ::file::path & path) override;
      virtual bool  name_is(const ::file::path & path) override;
      virtual bool  has_subdir(const ::file::path & path) override;

      virtual ::file::listing_base & root_ones(::file::listing_base & listing) override;
      //virtual void create(const ::file::path & path) override;
      //virtual void erase(const ::file::path & path, bool bRecursive = true) override;


      //virtual ::file::path name(const ::file::path & path);

      virtual ::file::path time() override;
      virtual ::file::path stage() override;
      virtual ::file::path stageapp() override;
      virtual ::file::path netseed() override;
      //virtual ::file::path install() override;
//       virtual ::file::path profile();

      virtual ::file::path module() override;
      //virtual ::file::path ca2module() override;
//      virtual ::file::path time_square(const string & strPrefix = nullptr, const string & strSuffix = nullptr);
      //virtual ::file::path time_log();


      virtual ::file::path trash_that_is_not_trash(const ::file::path & path) override;



      virtual ::file::path appdata(const ::scoped_string & scopedstrAppId = "") override;
      virtual ::file::path commonappdata_root() override;
      virtual ::file::path commonappdata() override;

//       virtual ::file::path usersystemappdata(const char * lpcszPrefix);
//       virtual ::file::path userappdata();
//       virtual ::file::path userdata();
//       //virtual ::file::path userfolder();
//       virtual ::file::path default_os_user_path_prefix();
//       virtual ::file::path default_userappdata(::object * pobject,const string & lpcszPrefix,const string & lpcszLogin );
//       virtual ::file::path default_userdata(::object * pobject,const string & lpcszPrefix,const string & lpcszLogin);
//       virtual ::file::path default_userfolder(::object * pobject,const string & lpcszPrefix,const string & lpcszLogin);
      virtual ::file::path userquicklaunch() override;
      virtual ::file::path userprograms() override;

      virtual ::file::path commonprograms() override;

      virtual ::file::path home() override;
      virtual ::file::path desktop() override;
      virtual ::file::path document() override;
      virtual ::file::path download() override;

      virtual ::file::path music() override;
      virtual ::file::path video() override;
      virtual ::file::path image() override;


   };


} // namespace acme_macos



