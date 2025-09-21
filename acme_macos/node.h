//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "acme/parallelization/manual_reset_happening.h"
#include "acme_apple/node.h"


namespace acme_macos
{


   class CLASS_DECL_ACME node :
      virtual public ::acme_apple::node
   {
   public:

      
      //__creatable_from_library(node, ::platform::node, "acme_macos");
      
      
       
      //gpointer m_pGtkSettingsDefault;
      string m_strTheme;

      ::pointer < manual_reset_happening > m_phappeningReadyToTerminateApp;

      node();
      ~node() override;

      
      ::string get_file_type_identifier(const ::file::path & path) override;
      
      
      void call_async(const ::scoped_string & pszPath, const ::scoped_string & pszParam, const ::scoped_string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr) override;
      void call_sync(const ::scoped_string & pszPath, const ::scoped_string & pszParam, const ::scoped_string & pszDir, ::e_display edisplay, const class ::time & durationTimeout, ::property_set & set, int * piExitCode) override;

      //virtual ::color::color get_system_color(enum_system_color esystemcolor) override;
      
      virtual bool _os_calc_system_dark_mode();
     

      virtual int node_init_check(int * pi, char *** ppz) override;
      
      
      bool defer_consume_main_arguments(int argc, char ** argv, int & iArgument) override;


      //virtual ::e_status start_node();

      //override;

      void initialize(::particle * pparticle) override;
      
      //void on_start_system() override;
      
      //void user_post_quit() override;
      
      void install_sigchld_handler() override;

      void _launch_macos_app(const ::scoped_string & scopedstrAppFolder) override;

      void _launch_macos_app_args(const ::scoped_string & scopedstrAppFolder, const ::scoped_string & scopedstrArgs) override;

      void launch_app(const ::scoped_string & scopedstr, const char ** argv, int iFlags) override;
      
      
      virtual int _create_process2(const char * _cmd_line, unsigned int * pprocessId);
      
      ::process_identifier create_process(const ::scoped_string & scopedstrCommandLine) override;
      
      ::file::path_array_base process_identifier_modules_paths(::process_identifier processID) override;

      bool load_modules_diff(string_array_base& straOld, string_array_base& straNew, const ::scoped_string & scopedstrExceptDir) override;

      ::process_identifier_array processes_identifiers() override;
      
      ::process_identifier_array module_path_processes_identifiers(const ::scoped_string & scopedstrModulePath, bool bModuleNameIsPropertyFormatted = false) override;
      
      ::file::path process_identifier_module_path(::process_identifier pid) override;
      
      string process_identifier_command_line(::process_identifier pid) override;
//
//      bool is_shared_library_busy(::process_identifier processid, const string_array& stra) override;
//
//      bool is_shared_library_busy(const string_array& stra) override;
      
      bool process_contains_module(string& strImage, ::process_identifier processID, const ::scoped_string & scopedstrLibrary) override;

      ::process_identifier_array shared_library_process(string_array_base& straProcesses, const ::scoped_string & scopedstrLibrary) override;

//         int_bool is_process_running(unsigned int pid) override;
      
      string get_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable) override;
      
      string expand_environment_variables(const ::scoped_string & scopedstr) override;

      array <::serial::port_info> list_serial_ports() override;
      
      virtual bool _launch_command(const char * const pszCommand);

      void shell_open(const ::file::path & pathFile, const ::scoped_string & strParams = "", const ::file::path & pathFolder = "") override;
      
      //void implement(::pointer < ::platform::node > & pnode, __pointer(class ::system) & psystem);
      
//      void acme_application_main(class ::platform::system * psystem) override;
      
      
//      ::pointer < ::particle > create_quit_particle(::pointer < ::platform::node > & pnode, ::pointer < ::platform::system > & psystem) override;
  

//      void implement(::pointer < ::platform::node > & pnode, __pointer(class ::system) & psystem) override;


      void _will_finish_launching() override;
      void _did_finish_launching() override;

      void _node_file_dialog(::file::file_dialog * pdialog) override;
      void _node_folder_dialog(::file::folder_dialog * pdialog) override;
      
      ::pointer < ::operating_system::application > application_predicate(const ::function < bool(::operating_system::application * papplication) > & function) override;
      
      
      void integration_factory() override;
      
      bool is_application_running_good_effort(const ::scoped_string & scopedstrRepos, const ::scoped_string & scopedstrApp) override;


      virtual bool __ns_is_application_running(const ::scoped_string & scopedstrRepos, const ::scoped_string & scopedstrApp);
      
      ::enum_id key_command(::user::enum_key ekey, ::user::key_state* pkeystate) override;

//
//      ::process_identifier_array processes_identifiers() override;

      int posix_shell_command(const ::scoped_string& scopedstrCommand, enum_posix_shell eposixshell = e_posix_shell_system_default, const trace_function& tracefunction = nullptr) override;

      
      virtual int zsh(const ::scoped_string &scopedstr, const trace_function & tracefunction = nullptr);

      ::file::path get_default_base_integration_folder() override;


   };


} // namespace acme_macos



