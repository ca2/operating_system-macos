//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace acme
{


   namespace macos
   {


      class CLASS_DECL_ACME node :
         virtual public ::acme::apple::node
      {
      public:

         
         //__creatable_from_library(node, ::acme::node, "acme_macos");
         
         
         class element_quit :
         virtual public ::element
         {
         public:
            
             __pointer(::acme::node) & m_pnode;
             __pointer(class ::system) & m_psystem;
            
             element_quit(__pointer(::acme::node) & pnode,__pointer(class ::system) & psystem
                          
                          ) :
             m_pnode(pnode),m_psystem(psystem)
            {
               
            }
            
            void run() override;
            
            
         };
          
         element_quit * m_pelementquit;

         //gpointer m_pGtkSettingsDefault;
         string m_strTheme;

         __pointer(manual_reset_event) m_peventReadyToTerminateApp;

         node();
         ~node() override;

         
         ::string get_file_type_identifier(const char * path) override;
         
         
         void call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr) override;
         void call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set) override;

         //virtual ::color::color get_system_color(enum_system_color esystemcolor) override;
         
         virtual bool _os_calc_system_dark_mode();
        

         virtual int node_init_check(int * pi, char *** ppz) override;

         //virtual ::e_status start_node();

         //override;

         void initialize(::object * pobject) override;
         
         void node_quit() override;
         
         void implement(__pointer(::acme::node) & pnode, __pointer(class ::system) & psystem) override;


   

         void install_sigchld_handler() override;

         void _launch_macos_app(const ::string & pszAppFolder) override;

         void _launch_macos_app_args(const ::string & pszAppFolder, const ::string & pszArgs) override;

         void launch_app(const ::string & psz, const char ** argv, int iFlags) override;
         
         
         virtual int _create_process2(const char * _cmd_line, u32 * pprocessId);
         
         void create_process(const ::string & pszCommandLine, u32 * pprocessId) override;
         
         bool process_modules(string_array& stra, u32 processID) override;

         bool load_modules_diff(string_array& straOld, string_array& straNew, const ::string & pszExceptDir) override;

         id_array get_pids() override;
         
         id_array module_path_get_pid(const ::string & pszModulePath, bool bModuleNameIsPropertyFormatted = false) override;
         
         string module_path_from_pid(u32 pid) override;
         
         string command_line_from_pid(u32 pid) override;

         bool is_shared_library_busy(u32 processid, const string_array& stra) override;

         bool is_shared_library_busy(const string_array& stra) override;
         
         bool process_contains_module(string& strImage, ::u32 processID, const ::string & pszLibrary) override;

         void shared_library_process(dword_array& dwa, string_array& straProcesses, const ::string & pszLibrary) override;

//         int_bool is_process_running(::u32 pid) override;
         
         string get_environment_variable(const ::string & pszEnvironmentVariable) override;
         
         string expand_environment_variables(const ::string & str) override;

         array <::serial::port_info> list_serial_ports() override;
         
         virtual bool _launch_command(const char * const pszCommand);

         void shell_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout) override;
         
         
      };


   } // namespace apple


} // namespace acme



