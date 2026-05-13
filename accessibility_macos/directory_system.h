// Create on 2021-03-21 20:00 <3ThomasBS_ // at Linux(quest.)
// Recreated on 2021-05-16 15:06 <3ThomasBS_ // for macOS
#pragma once


#include "acme_apple/directory_system.h"


namespace acme_macos
{


   class CLASS_DECL_ACME_MACOS directory_system :
      virtual public ::acme_apple::directory_system
   {
   public:


       ::file::path            m_strTimeFolder;
       ::file::path            m_strNetSeedFolder;

       ::file::path            m_strCommonAppData;
       ::file::path            m_strAppData;
       ::file::path            m_strPrograms;
       ::file::path            m_strCommonPrograms;

       
      //__creatable_from_library(directory_system, ::directory_system, "acme_macos");
      

      directory_system();
      ~directory_system() override;


      void initialize(::particle * pparticle) override;

      void init_system() override;
       

      virtual ::file::path install() override;
      virtual ::file::path default_install() override;
      virtual ::file::path beforeca2() override;
      virtual ::file::path module() override;
      virtual ::file::path relative(::file::path path) override;
      //virtual ::string appid() override;
      virtual ::file::path appdata() override; // appdata
      virtual ::file::path archive() override;
      virtual ::file::path tool() override;
      //virtual ::file::path public_system() override;
      virtual ::file::path userconfig() override;
      virtual ::file::path config() override;
      virtual ::file::path local() override;
      virtual ::file::path sensitive() override;
      virtual ::file::path localconfig() override; // #vcs C:\\Users\\user\\AppData\\Roaming\\ca2\\localconfig
      virtual ::file::path ca2roaming() override; // writable root (non-bin, non-exe)
      virtual ::file::path ca2appdata() override; // writable root (non-bin, non-exe)
      virtual ::file::path roaming() override;
      virtual ::file::path program_data() override;
      virtual ::file::path public_root() override; // writable common root (non-bin, non-exe)
      virtual ::file::path bookmark() override;
      virtual ::file::path home() override;
      virtual ::file::path pathfind(const ::scoped_string & scopedstrEnv, const ::scoped_string & scopedstrTopic, const ::scoped_string & scopedstrMode) override;
      virtual ::file::path program_files_x86() override;
      virtual ::file::path program_files() override;
      //virtual ::file::path program_data() override;
      virtual ::file::path stage(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration) override;
      virtual ::file::path sys_temp() override;
      virtual ::string dir_root() override;
      //virtual ::file::path home() override;
      //virtual ::file::path program_data() override;
      //virtual ::file::path roaming() override;
      virtual ::file::path get_memory_map_base_folder_path() override;
      //virtual ::file::path ca2appdata() override;
      //virtual ::file::path ca2roaming() override;
      //virtual ::file::path localconfig() override;
      virtual string system_short_name() override;


      //::file::path inplace_install(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration) override;
      //virtual ::file::path inplace_install(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration) override;
      virtual ::file::path inplace_install(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration) override;
      virtual ::file::path inplace_matter_install(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration) override;


      virtual void set_path_install_folder(const ::scoped_string & scopedstrPath) override;

      //virtual  bool        _shell_get_special_folder_path(HWND hwnd, ::file::path& str, int csidl, bool fCreate);
      //virtual ::file::path _shell_get_special_folder_path(int csidl, bool fCreate = true, ::windowing::window* pwindow = nullptr);
      //virtual ::file::path _get_known_folder(REFKNOWNFOLDERID kfid);

      //virtual ::file::path pathfind(const ::scoped_string & scopedstrEnv, const ::scoped_string & scopedstrTopic, const ::scoped_string & scopedstrMode) override;

      virtual ::file::path user_appdata_local() override;

   };


} // namespace acme_macos



