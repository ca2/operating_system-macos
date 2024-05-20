// From apex-linux/integration_context.h by camilo on 2023-02-17 20:48 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme_posix/integration_context.h"


namespace acme_macos
{

   namespace integration
   {


      class CLASS_DECL_ACME context :
         virtual public ::acme_posix::integration::context
   {
      public:


//      bool m_bMsys;
//
//
//      ::file::path m_pathProjectFolder;
//
//
//      ::string m_strVs;
//      ::file::path m_pathOperatingSystemIncludeFolder;
//      ::file::path m_pathOperatingSystemStorageFolder;
//      ::file::path m_pathDownloadURL;
//      ::string_array m_straOutput;
//      ::file::path m_pathFolder;
//      ::file::path m_path;
//      ::file::path m_pathSource2;
//      ::file::path m_pathPrefix;
//      ::string m_strRelease;
//      //::string          m_strContext;
//      //::string          m_strSdk1;
//      //::string          m_strStagePlatform;
//      ::string m_strStagePlatform;
//      ::string m_strPlatform;
//      //::string          m_strPlatform2;
//      ::string m_strConfiguration;
//      ::string m_strName;
//
//
//      ::pointer<::particle> m_pmutexLines;
//

      context();

      ~

      context()

      override;


      void initialize(::particle *pparticle)

      override;


      void prepare(const ::scoped_string & scopedstrOperatingSystem) override;

      void change_to_source_directory(const ::scoped_string & scopedstrRelative) override;

      void prepare_compile_and_link_environment() override;

      void prepare_compilation_script(::string &str) override;

      void prepare_linking_script(::string &str) override;

      ::i32 command_system(const ::scoped_string &scopedstr, const class ::time & timeout, const ::file::path & pathWorkingDirectory = {}, ::e_display edisplay = e_display_none) override;

      void clean() override;

      void download_and_uncompress() override;

      void git_clone() override;

      ::i32 bash(const ::scoped_string &scopedstr, const class ::time & timeTimeout) override;
      
      ::i32 zsh(const ::scoped_string &scopedstr, const class ::time & timeTimeout) override;

      ::string prepare_path(const ::file::path &path) override;


   };


} // namespace integration



} // namespace acme_macos



