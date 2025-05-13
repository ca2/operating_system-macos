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


      
      string app_id_to_executable_name(const string & strAppId) override;

      
      string get_command_line() override;

      void reboot() override;

      void shutdown(bool bPowerOff) override;

      virtual void terminate_processes_by_title(const ::string & pszName) override;
      //virtual string get_module_path(HMODULE hmodule);

      ::process_identifier_array  module_path_processes_identifiers(const ::scoped_string & scopedstrName) override;
      ::process_identifier_array title_processes_identifiers(const ::scoped_string & scopedstrName) override;
      //::process_identifier_array processes_identifiers() override;
      ::file::path process_identifier_module_path(::process_identifier dwPid) override;

      ::payload connection_settings_get_auto_detect() override;
      ::payload connection_settings_get_auto_config_url() override;


      virtual bool local_machine_set_run(const ::string & pszKey, const ::string & pszCommand);
      virtual bool local_machine_set_run_once(const ::string & pszKey, const ::string & pszCommand);
      virtual bool current_user_set_run(const ::string & pszKey, const ::string & pszCommand);
      virtual bool current_user_set_run_once(const ::string & pszKey, const ::string & pszCommand);
      virtual void defer_register_ca2_plugin_for_mozilla() override;


      void file_extension_get_open_with_list_keys(string_array & straKey, const ::string & pszExtension) override;

      void file_extension_get_open_with_list_commands(string_array & straCommand, const ::string & pszExtension) override;

      void file_association_set_default_icon(const ::string & pszExtension, const ::string & pszExtensionNamingClass, const ::string & pszIconPath) override;

      void file_association_set_shell_open_command(const ::string & pszExtension, const ::string & pszExtensionNamingClass,  const ::string & pszCommand, const ::string & pszParam) override;

      void file_association_get_shell_open_command(const ::string & pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam) override;

      virtual bool open_in_ie(const ::string & pcsz);

      void enable_service() override;

      void disable_service() override;

      void start_service() override;

      void stop_service() override;
      
      //bool dark_mode() const override;
      //void set_dark_mode(bool bDark) override;

      //bool resolve_link(::file::path & pathTarget, const string & strSource, string * pstrFolder = nullptr, string * pstrParams = nullptr, string * pstrIconLocation = nullptr, int * piIcon = nullptr) override;

      
      void raise_exception( unsigned int dwExceptionCode, unsigned int dwExceptionFlags);

      virtual bool is_remote_session() override;

      //virtual void post_to_all_threads(const ::id & id, WPARAM wParam, LPARAM lParam);

      virtual ::process_identifier current_process_identifier() override;

      void initialize_wallpaper_fileset(::file::set * pfileset, bool bAddSearch) override;

      void get_default_browser(string & strId, ::file::path & path, string & strParam) override;

      void set_default_browser() override;

      ::file::path get_app_path(const string & strApp) override;

      void on_process_request(::request * prequest) override;

      void file_open(const ::file::path & path, const ::string & strParams = "", const ::file::path & pathFolder = "") override;
      
      void open_internet_link(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrTarget) override;

//      void set_file_status(const ::string & lpszFileName, const ::file::file_status& status) override;

      //void browse_folder(property_set &set) override;
      //void browse_file_open(property_set &set) override;
      
      
      void set_this_application_as_default_for_file_extension(const ::string& strExtension) override;

      void register_user_auto_start(::platform::application * papplication, const string & strArguments,
                                    bool bRegister) override;

      bool is_user_auto_start(const string & strAppId) override;

    
   };


} // namespace apex_macos



