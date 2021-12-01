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

         
         class element_quit :
         virtual public ::element
         {
         public:
            
             __transport(::acme::node) & m_pnode;
             __transport(class ::system) & m_psystem;
            
             element_quit(__transport(::acme::node) & pnode,__transport(class ::system) & psystem
                          
                          ) :
             m_pnode(pnode),m_psystem(psystem)
            {
               
            }
            
            ::e_status run() override;
            
            
         };
          
          element_quit * m_pelementquit;

         //gpointer m_pGtkSettingsDefault;
         string m_strTheme;

         __pointer(manual_reset_event) m_peventReadyToTerminateApp;

         node();
         ~node() override;

         
         ::string get_file_type_identifier(const char * path) override;
         
         
         ::e_status call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr) override;
         ::e_status call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set) override;

         //virtual ::color::color get_system_color(enum_system_color esystemcolor) override;
         
         virtual bool _os_calc_system_dark_mode();
        

         virtual int node_init_check(int * pi, char *** ppz) override;

         //virtual ::e_status start_node();

         //override;

         virtual ::e_status initialize(::object * pobject) override;
         
         void node_quit() override;
         
         ::e_status implement(__transport(::acme::node) & pnode, __transport(class ::system) & psystem) override;


   //      virtual ::e_status get_system_time(system_time_t * psystemtime)
   //
   //      override;
   //
   //      virtual double get_time_zone();
   //
   //      virtual ::e_status system_time_to_time(time_t * ptime, const system_time_t * psystime, i32 nDST = -1)
   //
   //      override;
   //
   //      virtual ::e_status file_time_to_time(time_t * ptime, const filetime_t * pfiletime, i32 nDST = -1)
   //
   //      override;
   //
   //      virtual ::e_status time_to_system_time(system_time_t * psystemtime, const time_t * ptime)
   //
   //      override;
   //
   //      virtual ::e_status get_system_time_as_file_time(filetime_t * pfiletime)
   //
   //      override;
   //
   //      virtual ::e_status system_time_to_tm(tm * ptm, const system_time_t * psystemtime);
   //
   //      virtual ::e_status tm_to_system_time(system_time_t * psystemtime, const tm * ptm);
   //
   //      virtual ::e_status system_time_to_file_time(filetime_t * pfiletime, const system_time_t * psystemtime)
   //
   //      override;
   //
   //      virtual ::e_status file_time_to_system_time(system_time_t * psystemtime, const filetime_t * pfiletime)
   //
   //      override;
   //
   //      virtual ::e_status file_time_to_local_file_time(filetime_t * pfiletimeLocal, const filetime_t * pfiletime)
   //
   //      override;
   //
   //      virtual ::e_status is_valid_filetime(const filetime_t * pfiletime)
   //
   //      override;
   //
   //      virtual filetime get_filetime_now();


         virtual ::e_status install_sigchld_handler() override;

         ::e_status _launch_macos_app(const ::string & pszAppFolder) override;

         ::e_status _launch_macos_app_args(const ::string & pszAppFolder, const ::string & pszArgs) override;

         ::e_status launch_app(const ::string & psz, const char ** argv, int iFlags) override;
         
         
         virtual int _create_process2(const char * _cmd_line, u32 * pprocessId);
         
         ::e_status create_process(const ::string & pszCommandLine, u32 * pprocessId) override;
         
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

         virtual bool shell_execute_sync(const ::string & pszFile, const ::string & pszParams, ::duration durationTimeout );
         
      };


   } // namespace apple


} // namespace acme



