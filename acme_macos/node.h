//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "acme/parallelization/manual_reset_event.h"
#include "acme_apple/node.h"


namespace acme_macos
{

   class CLASS_DECL_ACME node :
      virtual public ::acme_apple::node
   {
   public:

      
      //__creatable_from_library(node, ::acme::node, "acme_macos");
      
      
       
      //gpointer m_pGtkSettingsDefault;
      string m_strTheme;

      ::pointer < manual_reset_event > m_peventReadyToTerminateApp;

      node();
      ~node() override;

      
      ::string get_file_type_identifier(const ::file::path & path) override;
      
      
      void call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr) override;
      void call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const class ::time & durationTimeout, ::property_set & set, ::i32 * piExitCode) override;

      //virtual ::color::color get_system_color(enum_system_color esystemcolor) override;
      
      virtual bool _os_calc_system_dark_mode();
     

      virtual int node_init_check(int * pi, char *** ppz) override;

      //virtual ::e_status start_node();

      //override;

      void initialize(::particle * pparticle) override;
      
      void user_post_quit() override;
      
      void install_sigchld_handler() override;

      void _launch_macos_app(const ::string & pszAppFolder) override;

      void _launch_macos_app_args(const ::string & pszAppFolder, const ::string & pszArgs) override;

      void launch_app(const ::string & psz, const char ** argv, int iFlags) override;
      
      
      virtual int _create_process2(const char * _cmd_line, u32 * pprocessId);
      
      ::process_identifier create_process(const ::string & pszCommandLine) override;
      
      ::file::path_array process_identifier_modules_paths(::process_identifier processID) override;

      bool load_modules_diff(string_array& straOld, string_array& straNew, const ::string & pszExceptDir) override;

      ::process_identifier_array processes_identifiers() override;
      
      ::process_identifier_array module_path_processes_identifiers(const ::string & pszModulePath, bool bModuleNameIsPropertyFormatted = false) override;
      
      string process_identifier_module_path(::process_identifier pid) override;
      
      string process_identifier_command_line(::process_identifier pid) override;
//
//      bool is_shared_library_busy(::process_identifier processid, const string_array& stra) override;
//
//      bool is_shared_library_busy(const string_array& stra) override;
      
      bool process_contains_module(string& strImage, ::process_identifier processID, const ::string & pszLibrary) override;

      ::process_identifier_array shared_library_process(string_array& straProcesses, const ::string & pszLibrary) override;

//         int_bool is_process_running(::u32 pid) override;
      
      string get_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable) override;
      
      string expand_environment_variables(const ::scoped_string & scopedstr) override;

      array <::serial::port_info> list_serial_ports() override;
      
      virtual bool _launch_command(const char * const pszCommand);

      void shell_open(const ::file::path & pathFile, const ::string & strParams = "", const ::file::path & pathFolder = "") override;
      
      //void implement(::pointer < ::acme::node > & pnode, __pointer(class ::system) & psystem);
      
      void acme_application_main(class ::acme::system * psystem) override;
      
      
//      ::pointer < ::particle > create_quit_particle(::pointer < ::acme::node > & pnode, ::pointer < ::acme::system > & psystem) override;
  

//      void implement(::pointer < ::acme::node > & pnode, __pointer(class ::system) & psystem) override;


      void _will_finish_launching() override;

      void _node_file_dialog(::file::file_dialog * pdialog) override;
      void _node_folder_dialog(::file::folder_dialog * pdialog) override;
      
      ::pointer < ::operating_system::application > application_predicate(const ::function < bool(::operating_system::application * papplication) > & function) override;
      
      
      void integration_factory() override;
      
      bool is_application_running_good_effort(const ::scoped_string & scopedstrRepos, const ::scoped_string & scopedstrApp) override;


      virtual bool __ns_is_application_running(const ::scoped_string & scopedstrRepos, const ::scoped_string & scopedstrApp);
      
      
   };


} // namespace acme_macos



