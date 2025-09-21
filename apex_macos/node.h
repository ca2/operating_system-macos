//
// Created by camilo on 19/01/2021. <33TBS!!
//
//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2021-05-14 02:20 PM BRT <3ThomasBorregaardSørensen!!
//
#pragma once


#include "apex_apple/node.h"
#include "acme_macos/node.h"


namespace apex_macos
{


   class CLASS_DECL_APEX_MACOS node :
      virtual public ::apex_apple::node,
      virtual public ::acme_macos::node
   {
   public:


      node();
      ~node() override;
      
      
      virtual int node_init_check(int * pi, char *** ppz) override;


      
      string app_id_to_executable_name(const ::scoped_string & scopedstrAppId) override;

      
      string get_command_line() override;

      void reboot() override;

      void shutdown(bool bPowerOff) override;

      virtual void terminate_processes_by_title(const ::scoped_string & scopedstrName) override;
      //virtual string get_module_path(HMODULE hmodule);

      ::process_identifier_array  module_path_processes_identifiers(const ::scoped_string & scopedstrName) override;
      ::process_identifier_array title_processes_identifiers(const ::scoped_string & scopedstrName) override;
      //::process_identifier_array processes_identifiers() override;
      ::file::path process_identifier_module_path(::process_identifier dwPid) override;

      ::payload connection_settings_get_auto_detect() override;
      ::payload connection_settings_get_auto_config_url() override;


      virtual bool local_machine_set_run(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand);
      virtual bool local_machine_set_run_once(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand);
      virtual bool current_user_set_run(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand);
      virtual bool current_user_set_run_once(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand);
      virtual void defer_register_ca2_plugin_for_mozilla() override;


      void file_extension_get_open_with_list_keys(string_array_base & straKey, const ::scoped_string & scopedstrExtension) override;

      void file_extension_get_open_with_list_commands(string_array_base   & straCommand, const ::scoped_string & scopedstrExtension) override;

      void file_association_set_default_icon(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass, const ::file::path & pathIcon) override;

      void file_association_set_shell_open_command(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass,  const ::file::path & pathExecutable, const ::scoped_string & scopedstrParam) override;

      void file_association_get_shell_open_command(const ::scoped_string & scopedstrExtension, string & strExtensionNamingClass, string & strCommand, string & strParam) override;

      virtual bool open_in_ie(const ::string & pcsz);

      void enable_service() override;

      void disable_service() override;

      void start_service() override;

      void stop_service() override;
      
      //bool dark_mode() const override;
      //void set_dark_mode(bool bDark) override;

      //bool resolve_link(::file::path & pathTarget, const ::scoped_string & scopedstrSource, string * pstrFolder = nullptr, string * pstrParams = nullptr, string * pstrIconLocation = nullptr, int * piIcon = nullptr) override;

      
      void raise_exception( unsigned int dwExceptionCode, unsigned int dwExceptionFlags);

      virtual bool is_remote_session() override;

      //virtual void post_to_all_threads(const ::id & id, WPARAM wParam, LPARAM lParam);

      virtual ::process_identifier current_process_identifier() override;

      void initialize_wallpaper_fileset(::file::set * pfileset, bool bAddSearch) override;

      void get_default_browser(string & strId, ::file::path & path, string & strParam) override;

      void set_default_browser() override;

      ::file::path get_app_path(const ::scoped_string & scopedstrApp) override;

      void on_process_request(::request * prequest) override;

      void file_open(const ::file::path & path, const ::scoped_string & strParams = "", const ::file::path & pathFolder = "") override;
      
      void open_internet_link(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrTarget) override;

//      void set_file_status(const ::string & lpszFileName, const ::file::file_status& status) override;

      //void browse_folder(property_set &set) override;
      //void browse_file_open(property_set &set) override;
      
      
      void set_this_application_as_default_for_file_extension(const ::scoped_string & scopedstrExtension) override;

      void register_user_auto_start(::platform::application * papplication, const ::scoped_string & scopedstrArguments,
                                    bool bRegister) override;

      bool is_user_auto_start(const ::scoped_string & scopedstrAppId) override;

    
   };


} // namespace apex_macos



