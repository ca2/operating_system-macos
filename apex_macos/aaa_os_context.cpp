#include "framework.h"
//#include "os_context.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/acme.h"
#include "acme/platform/node.h"
#include "acme/handler/request.h"
#include "apex/filesystem/file/set.h"
#include "apex/platform/system.h"
#if defined(MACOS)
#include <sys/stat.h>
#endif
#include <dispatch/dispatch.h>
int macos_launch_on_login();
void macos_set_launch_on_login(int launchOnLogin);


void ns_main_post(dispatch_block_t block);


void ns_set_dark_mode(bool bDark);

void setMyselfAsDefaultApplicationForFileExtension(const char * pszExtension);


void ns_fork(const ::procedure & procedure)
{
   
   __block auto routineHold = procedure;
   
   routineHold->increment_reference_count();
 
   ns_main_post(^
                 {
      
      routineHold();
      
      routineHold->release();
      
   }
                 );
   
}


#undef USERNAME_LENGTH // mysql one

bool ns_open_file(const char * );
void ns_main_post(dispatch_block_t block);
void ns_create_alias(const char * pszTarget, const char * pszSource);
//::string & ns_get_default_browser_path();
void ns_set_this_process_binary_default_browser();

//string apple_browse_folder(class ::platform::system * psystem, ::operating_system_folder_dialog * pdialog);
//string_array apple_browse_file_open(class ::platform::system * psystem, const char ** pszStartDir, bool bAllowsMultipleSelection);



bool ns_open_url(const char * psz);


namespace apex_macos
{

//   ::file::path get_default_browser_path()
//   {
//
//      string strPath;
//
//      ::string & psz = ns_get_default_browser_path();
//
//      strPath = psz;
//
//      ::str::case_insensitive_begins_eat(strPath, "file://");
//
//      free(psz);
//
//      ::file::path path;
//
//      path = strPath;
//
//      return path;
//
//   }


   os_context::os_context()
   {
   }


   os_context::~os_context()
   {
   }


   string os_context::get_command_line()
   {
      
      ::string strCommandLine;
      
      for(int i = 0; i < ::system()->m_argc; i++)
      {
         
         auto psz = ::system()->m_argv[i];
         
         ::string strArg(psz);
         
         if(::found(strArg.find_first_whitespace()))
         {
            
            strArg = "\"" + strArg + "\"";
            
         }
         
         if(strCommandLine.has_character())
         {
            
            strCommandLine += " ";
            
         }
         
         strCommandLine += strArg;
         
      }
      
      return strCommandLine;

   }


   void os_context::shutdown(bool bIfPowerOff)
   {
      /*      bool retval = true;
       HANDLE hToken;
       TOKEN_PRIVILEGES tkp;
       if (!OpenProcessToken(GetCurrentProcess(),
       TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
       return false;
       LookupPrivilegeValue(nullptr, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
       tkp.PrivilegeCount = 1;
       tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
       AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES) nullptr, 0);
       if (bIfPowerOff)
       retval = ExitWindowsEx(EWX_POWEROFF, 0) != false;
       else
       retval = ExitWindowsEx(EWX_SHUTDOWN, 0) != false;

       //reset the previlages
       tkp.Privileges[0].Attributes = 0;
       AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES) nullptr, 0);
       return retval;*/

      //  throw ::exception(error_not_implemented);;
      //return false;

   }


   void os_context::reboot()
   {
      /*      HANDLE hToken;
       TOKEN_PRIVILEGES tkp;
       if (!OpenProcessToken(GetCurrentProcess(),
       TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
       return false;
       if(!LookupPrivilegeValue(nullptr, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
       {
       TRACELASTERROR();
       return false;
       }
       tkp.PrivilegeCount = 1;
       tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
       if(!AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES) nullptr, 0))
       {
       TRACELASTERROR();
       return false;
       }
       if (get_last_error() == ERROR_NOT_ALL_ASSIGNED)
       {
       return false;
       }
       if(!LookupPrivilegeValue(nullptr, SE_REMOTE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
       {
       TRACELASTERROR();
       return false;
       }
       tkp.PrivilegeCount = 1;
       tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
       if(!AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES) nullptr, 0))
       {
       TRACELASTERROR();
       return false;
       }
       if (get_last_error() == ERROR_NOT_ALL_ASSIGNED)
       {
       return false;
       }


       if(!WTSShutdownSystem(WTS_CURRENT_SERVER_HANDLE, WTS_WSD_REBOOT))
       {
       TRACELASTERROR();
       return false;
       }
       if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE,
       SHTDN_REASON_MAJOR_SOFTWARE | SHTDN_REASON_MINOR_INSTALLATION))
       {
       unsigned int dwLastError = ::get_last_error();
       return false;
       }*/
      //reset the previlages
      /*    tkp.Privileges[0].Attributes = 0;
       AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES) nullptr, 0);
       return true;*/
      //    throw ::exception(error_not_implemented);;
      //return false;

   }

   void os_context::terminate_processes_by_title(const ::string & pszName)
   {
//      throw ::exception(error_not_implemented);;
      return;

      /*      unsigned int dwPid;
       while(get_pid_by_title(pszName, dwPid))
       {
       HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
       PROCESS_VM_READ,
       false, dwPid );
       TerminateProcess(hProcess, (unsigned int) -1);
       CloseHandle(hProcess);
       ::EnumWindows((WNDENUMPROC)
       CKillProcessHelper::TerminateAppEnum,
       (LPARAM) dwId);
       // Wait on the handle. If it signals, great.

       //If it times out, then you kill it.

       if(WaitForSingleObject(hProcess, 5000)
       !=WAIT_OBJECT_0)
       bResult = TerminateProcess(hProcess,0);
       else
       bResult = true;
       CloseHandle(hProcess);
       return bResult == true;*/

      //  }
   }

   
   ::process_identifier_array os_context::module_path_processes_identifiers(const ::scoped_string & pszName)
   {

      auto dwa = processes_identifiers();
   
      ::process_identifier_array processidentifiera;
   
      for(int i = 0; i < dwa.get_count(); i++)
      {
         
         if(process_identifier_module_path(dwa[i]).case_insensitive_equals(pszName))
         {
            
            processidentifiera.add(dwa[i]);
            
         }
         
      }
   
      return processidentifiera;
   
   }


   ::process_identifier_array os_context::title_processes_identifiers(const ::scoped_string & pszName)
   {

      auto dwa = processes_identifiers();
   
      ::process_identifier_array processidentifiera;
      
      for(int i = 0; i < dwa.get_count(); i++)
      {
         
         if(process_identifier_module_path(dwa[i]).title().case_insensitive_equals(pszName))
         {
            
            processidentifiera.add(dwa[i]);
            
         }
         
      }
      
      return processidentifiera;
      
   }


   ::file::path os_context::process_identifier_module_path(::process_identifier processidentifier)
   {
      
      return node()->process_identifier_module_path(processidentifier);

   }

   
//   ::process_identifier_array os_context::processes_identifiers()
//   {
//
//      return acmenode()->processes_identifiers();
//
//   }


   ::payload os_context::connection_settings_get_auto_detect()
   {
//      throw ::exception(error_not_implemented);;
      return false;

      /*
       registry::Key key1;

       key1.OpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Connections", false);

       memory mem;

       key1.QueryValue("DefaultConnectionSettings", mem);

       bool bAutoDetect = (((unsigned char *) mem.get_data())[8] & 0x08) != 0;

       return bAutoDetect;
       */
   }



   ::payload os_context::connection_settings_get_auto_config_url()
   {

//      throw ::exception(error_not_implemented);;
      return "";
      /*
       registry::Key key;

       key.OpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings", false);

       string strUrl;

       key.QueryValue("AutoConfigURL", strUrl);

       return strUrl;
       */
   }

   bool os_context::local_machine_set_run(const ::string & pszKey, const ::string & pszCommand)
   {

//     throw ::exception(error_not_implemented);;
      return false;

      /*
       registry::Key keyKar(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);


       keyKar.SetValue(pszKey, pszCommand);


       return true;
       */
   }


   bool os_context::local_machine_set_run_once(const ::string & pszKey, const ::string & pszCommand)
   {


//     throw ::exception(error_not_implemented);;
      return false;
      /*    registry::Key keyKar(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", true);


       keyKar.SetValue(pszKey, pszCommand);
       */

      return false;

   }

   bool os_context::current_user_set_run(const ::string & pszKey, const ::string & pszCommand)
   {

      //   throw ::exception(error_not_implemented);;
      return false;

      /*
       registry::Key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);


       keyKar.SetValue(pszKey, pszCommand);
       */

      return false;

   }

   bool os_context::current_user_set_run_once(const ::string & pszKey, const ::string & pszCommand)
   {

//    throw ::exception(error_not_implemented);;
      return false;

      /*
       registry::Key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", true);


       keyKar.SetValue(pszKey, pszCommand);

       */
      return false;

   }


   void os_context::defer_register_ca2_plugin_for_mozilla()
   {
      //    throw ::exception(error_not_implemented);;
      return;

      /*
       registry::Key keyPlugins;

       if(keyPlugins.OpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\MozillaPlugins", true))
       {

       registry::Key keyPlugin;

       if(keyPlugin.OpenKey(keyPlugins, "@ca2.software/npca2", true))
       {

       keyPlugin.SetValue("Description", "ca2 plugin for NPAPI");
       keyPlugin.SetValue("Path", ::apex::get_system()->m_strCa2Module("npca2.dll"));
       keyPlugin.SetValue("ProductName", "ca2 plugin for NPAPI");
       keyPlugin.SetValue("Vendor", "ca2 Desenvolvimento de Software Ltda.");
       keyPlugin.SetValue("Version", get_application()->file_as_string(papplication->dir().ca2("appdata/x86/ca2_build.txt")));

       registry::Key keyApplicationCa2;

       if(keyApplicationCa2.OpenKey(keyPlugin, "application/ca2", true))
       {

       keyApplicationCa2.SetValue("Description", "ca2 Document");

       }

       }

       }

       return true;
       */
   }

   
   void os_context::file_extension_get_open_with_list_keys(string_array & straKey, const ::string & pszExtension)
   {
      //   throw ::exception(error_not_implemented);;
      return;

      /*
       string strExt;

       strExt = ".";
       strExt += pszExtension;

       string strOpenWithKey;
       strOpenWithKey = strExt + "\\OpenWithList";

       registry::Key key;

       key.OpenKey(HKEY_CLASSES_ROOT, strOpenWithKey, false);

       key.EnumKey(straKey);

       return true;
       */
   }


   void os_context::file_extension_get_open_with_list_commands(string_array & straCommand, const ::string & pszExtension)
   {

      string_array straKey;

      file_extension_get_open_with_list_keys(straKey, pszExtension);

   }


   void os_context::file_association_set_default_icon(const ::string & pszExtension, const ::string & pszExtensionNamingClass, const ::string & pszIconPath)
   {

      //    throw ::exception(error_not_implemented);;
      //return false;

      /*
       string strExtensionNamingClass(pszExtensionNamingClass);

       registry::Key keyLink3(HKEY_CLASSES_ROOT, strExtensionNamingClass, true);
       keyLink3.SetValue("DefaultIcon", pszIconPath);


       return false;
       */
   }


   void os_context::file_association_set_shell_open_command(const ::string & pszExtension, const ::string & pszExtensionNamingClass,  const ::string & pszCommand, const ::string & pszParam)
   {
      //   throw ::exception(error_not_implemented);;
      return;

      /*
       string strExt;

       strExt = ".";
       strExt += pszExtension;

       string strExtensionNamingClass(pszExtensionNamingClass);

       registry::Key key(HKEY_CLASSES_ROOT, strExt, true);
       key.SetValue(nullptr, strExtensionNamingClass);

       registry::Key keyLink3(HKEY_CLASSES_ROOT, strExtensionNamingClass + "\\shell", true);
       keyLink3.SetValue(nullptr, "open");

       registry::Key keyLink2(keyLink3, "open", true);
       keyLink2.SetValue(nullptr, "&Abrir");

       registry::Key keyLink1(keyLink2, "command", true);

       string strFormat;
       strFormat.Format("\"%s\" \"%%L\" %s", pszCommand, pszParam);
       keyLink1.SetValue(nullptr, strFormat);

       return true;
       */
   }


   void os_context::file_association_get_shell_open_command(const ::string & pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam)
   {
      //    throw ::exception(error_not_implemented);;
      return;

      /*
       string strExt;

       strExt = ".";
       strExt += pszExtension;

       registry::Key key(HKEY_CLASSES_ROOT, strExt, false);
       if(!key.QueryValue(nullptr, strExtensionNamingClass))
       return false;

       registry::Key keyLink(HKEY_CLASSES_ROOT, strExtensionNamingClass + "\\shell\\open\\command", false);

       string strFormat;
       if(keyLink.QueryValue(nullptr, strFormat))
       {

       const ::string & psz = strFormat;

       try
       {

       strCommand = ::str::consume_quoted_value(psz);
       ::str::consume_spaces(psz);
       ::str::consume(psz, "\"%L\"");
       strParam = psz;

       }
       catch(...)
       {
       }


       }

       return true;
       */
   }

   bool os_context::open_in_ie(const ::string & pcsz)
   {

      //    throw ::exception(error_not_implemented);;
      return false;

      /*    registry reg;
       string str;
       string str2;
       string strCommand;
       registry::Key key;
       if(key.OpenKey(HKEY_CLASSES_ROOT, ".html", false))
       {
       if(reg.RegQueryValue(key.m_hkey, "", str))
       {
       if(key.OpenKey(HKEY_CLASSES_ROOT, ".html\\shell\\opennew\\command", false))
       {
       string str;
       if(reg.RegQueryValue(HKEY_CLASSES_ROOT, str, str2))
       {
       string strCommand(str2);
       strCommand.replace("%1", pcsz);
       WinExec(strCommand,e_display_normal);
       }
       }
       else
       {
       if(key.OpenKey(HKEY_CLASSES_ROOT, str, false))
       {
       str += "\\shell\\opennew\\command";
       if(key.OpenKey(HKEY_CLASSES_ROOT, str, false))
       {
       if(reg.RegQueryValue(key.m_hkey, "", str2))
       {
       string strCommand(str2);
       strCommand.replace("%1", pcsz);
       WinExec(strCommand,e_display_normal);
       }
       }
       }
       }
       }
       }

       return true;
       */

   }


   void os_context::enable_service()
   {

      //    throw ::exception(error_not_implemented);;
      return;

      /*
       if(papp->m_strAppName.is_empty()
       || papp->m_strAppName.compare_ci("bergedge") == 0
       || !papp->is_serviceable())
       return false;

       SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);

       string strCalling = papp->m_strModulePath + " : app=" + papp->m_XstrAppId + " service usehostlogin";

       if(hdlSCM == 0)
       {
       //::get_last_error()
       return false;
       }

       SC_HANDLE hdlServ = ::CreateService(
       hdlSCM,                    // SCManager database
       "apex-" + papp->m_strAppName,               // name of service
       "ccwarehouse ca2 account " + papp->m_strAppName,        // service name to display
       STANDARD_RIGHTS_REQUIRED,  // desired access
       SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, // service type
       SERVICE_AUTO_START,      // start type
       SERVICE_ERROR_NORMAL,      // error control type
       strCalling,                   // service's binary Path name
       0,                      // no load ordering group
       0,                      // no tag identifier
       0,                      // no dependencies
       0,                      // LocalSystem account
       0);                     // no password

       if (!hdlServ)
       {
       CloseServiceHandle(hdlSCM);
       //Ret = ::get_last_error();
       return false;
       }

       CloseServiceHandle(hdlServ);
       CloseServiceHandle(hdlSCM);

       return true;
       */

   }


   void os_context::disable_service()
   {
      //   throw ::exception(error_not_implemented);;
      return;

      /*
       if(papp->m_strAppName.is_empty()
       || papp->m_strAppName.compare_ci("bergedge") == 0
       || !papp->is_serviceable())
       return false;

       SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

       if(hdlSCM == 0)
       {
       //::get_last_error();
       return false;
       }

       SC_HANDLE hdlServ = ::OpenService(
       hdlSCM,                    // SCManager database
       "apex-" + papp->m_strAppName,               // name of service
       DELETE);                     // no password

       if (!hdlServ)
       {
       // Ret = ::get_last_error();
       CloseServiceHandle(hdlSCM);
       return false;
       }

       ::DeleteService(hdlServ);

       CloseServiceHandle(hdlServ);

       CloseServiceHandle(hdlSCM);

       return false;
       */
   }


   void os_context::start_service()
   {
      //  throw ::exception(error_not_implemented);;
      return;

      /*
       if(papp->m_strAppName.is_empty()
       || papp->m_strAppName.compare_ci("bergedge") == 0
       || !papp->is_serviceable())
       return false;

       SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

       if(hdlSCM == 0)
       {
       //::get_last_error();
       return false;
       }

       SC_HANDLE hdlServ = ::OpenService(
       hdlSCM,                    // SCManager database
       "apex-" + papp->m_strAppName,               // name of service
       SERVICE_START);                     // no password


       if (!hdlServ)
       {
       CloseServiceHandle(hdlSCM);
       //Ret = ::get_last_error();
       return false;
       }

       bool bOk = StartService(hdlServ, 0, nullptr) != false;

       CloseServiceHandle(hdlServ);
       CloseServiceHandle(hdlSCM);

       return bOk != false;
       */
   }


   void os_context::stop_service()
   {
      //    throw ::exception(error_not_implemented);;
      return;

      /*
       if(papp->m_strAppName.is_empty()
       || papp->m_strAppName.compare_ci("bergedge") == 0
       || !papp->is_serviceable())
       return false;

       SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

       if(hdlSCM == 0)
       {
       //::get_last_error();
       return false;
       }

       SC_HANDLE hdlServ = ::OpenService(
       hdlSCM,                    // SCManager database
       "apex-" + papp->m_strAppName,               // name of service
       SERVICE_STOP);                     // no password

       if (!hdlServ)
       {
       // Ret = ::get_last_error();
       CloseServiceHandle(hdlSCM);
       return false;
       }

       SERVICE_STATUS ss;

       __memset(&ss, 0, sizeof(ss));

       bool bOk = ::ControlService(hdlServ, SERVICE_CONTROL_STOP, &ss) != false;

       ::DeleteService(hdlServ);

       CloseServiceHandle(hdlServ);

       CloseServiceHandle(hdlSCM);

       return bOk != false;
       */
   }

void os_context::set_dark_mode(bool bDark)
{
   
   ns_set_dark_mode(bDark);
   
}

//   bool os_context::resolve_link(::file::path & pathTarget, const string & strSource, string * pstrFolder, string * pstrParams, string * pstrIconLocation, int * piIcon)
//   {
//
//      auto pcontext = m_pcontext->m_papexcontext;
//
//      pathTarget = pcontext->defer_process_path(strSource);
//
//      pathTarget = acmesystem()->m_pacmepath->_final(pathTarget);
//
//      while(pcontext->os_resolve_alias(pathTarget, pathTarget))
//      {
//
//         pathTarget = acmesystem()->m_pacmepath->_final(pathTarget);
//
//      }
//
//      return true;
//
//   }


//   ::pointer < ::file::link > os_context::resolve_link(const ::file::path & path, ::file::e_link elink)
//   {
//
//      auto plink = apex_darwin::os_context::resolve_link(path, elink);
//      
//      return plink;
//
//   }


   void os_context::raise_exception( unsigned int dwExceptionCode, unsigned int dwExceptionFlags)
   {

      throw ::exception(error_not_implemented);;
      return;
      /*
       RaiseException( dwExceptionCode, dwExceptionFlags, 0, nullptr );
       */
   }

   bool os_context::is_remote_session()
   {

//      throw ::exception(error_not_implemented);;
      return false;
      /*
       return GetSystemMetrics(SM_REMOTESESSION) != false;
       */
   }

   
   ::process_identifier os_context::current_process_identifier()
   {

      return node()->current_process_identifier();

   }


//   void os_context::post_to_all_threads(const ::id & id, wparam wparam, lparam lparam)
//   {
//
////      throw ::exception(error_not_implemented);;
//      return;
//
//   }


   void os_context::initialize_wallpaper_fileset(::file::set * pfileset, bool bAddSearch)
   {

      if (bAddSearch)
      {

         //string strDir;
         //strDir = papplication->dir().path(getenv("HOME"), "Pictures");
         //imagefileset.add_search(strDir);
         string strDir;
         strDir = "/Library/Desktop Pictures";
         pfileset->add_search(strDir, true);

      }

      //return true;

   }


   void os_context::get_default_browser(string & strId, ::file::path & path, string & strParam)
   {

//      path = ::apex_macos::get_default_browser_path();
//
//      if(path.find_ci("chrome") >= 0)
//      {
//
//         strId = "chrome";
//
//      }
//      else if(path.find_ci("firefox") >= 0)
//      {
//
//         strId = "firefox";
//
//      }
//      else if(path.find_ci("commander") >= 0)
//      {
//
//         strId = "commander";
//
//      }
//      else
//      {
//
//         strId = "default";
//
//      }

      //return true;

   }


   void os_context::set_default_browser()
   {

      ns_set_this_process_binary_default_browser();

      //return false;

   }


   ::file::path os_context::get_app_path(const string & strApp)
   {

      if(strApp.is_empty())
      {

         return "";

      }

      if(strApp.case_insensitive_begins("/Applications/"))
      {

         return strApp;

      }

      string strAppReturn;

      if(strApp.case_insensitive_equals("chrome"))
      {

         strAppReturn = "Google Chrome";

      }
      else
      {

         strAppReturn = strApp;

      }

      strAppReturn.set_at(0, ansi_toupper(strAppReturn[0]));

      strAppReturn = "/Applications/" + strAppReturn;

      if(!strAppReturn.case_insensitive_ends(".app"))
      {

         strAppReturn += ".app";

      }
      
      auto papplication = application();

      if(pcontext->dir()->is(strAppReturn))
      {

         return strAppReturn;

      }

      strAppReturn = strApp;

      strAppReturn = "/Applications/" + strAppReturn;

      if(!strAppReturn.case_insensitive_ends(".app"))
      {

         strAppReturn += ".app";

      }

      return strAppReturn;

   }


   void os_context::on_process_request(::request * prequest)
   {

//      ::pointer < ::handler > phandler = ::apex::get_system()->handler();

      if(prequest->m_strExe[0] == '/')
      {

         ::file::path p;
         
         auto psystem = system();
         
         auto pdirectorysystem = psystem->directory_system();

         p = pdirectorysystem->ca2roaming();

         p /= "mypath" / prequest->payload("app").as_string() + ".txt";

         psystem->file_system()->put_contents(p, prequest->m_strExe);

         string strApp = prequest->m_strExe;

         character_count iFind = strApp.case_insensitive_find_index(".app/");

         if(iFind > 0)
         {

            p = pdirectorysystem->ca2roaming();

            p /= "mypath" / prequest->payload("app").as_string() + "-app";

            ::file::path p2;

            p2 = pdirectorysystem->ca2roaming();

            p2 /= "mypath" / ::file::path(prequest->payload("app").as_string()).folder()/ ::file::path(strApp(0, iFind + strlen(".app"))).name();

            ns_create_alias(p2, strApp(0, iFind + strlen(".app")));

            if(pdirectorysystem->is(pdirectorysystem->localconfig() / "monitor-0/desk/2desk"))
            {

               ::file::path p3;

               p3 = pdirectorysystem->localconfig() / "monitor-0/desk/2desk" / ::file::path(strApp(0, iFind + strlen(".app"))).name();

               ns_create_alias(p3, strApp(0, iFind + strlen(".app")));

            }

            file_system()->put_contents(p, "open -a \""+strApp(0, iFind + strlen(".app")) + "\"");

            chmod(p, 0777);

         }

      }

   }

//   void os_context::set_file_status(const ::string & lpszFileName, const ::file::file_status& status)
//   {
//
//
////      unsigned int wAttr;
////      FILETIME creationTime;
////      FILETIME lastAccessTime;
////      FILETIME lastWriteTime;
////      LPFILETIME lpCreationTime = nullptr;
////      LPFILETIME lpLastAccessTime = nullptr;
////      LPFILETIME lpLastWriteTime = nullptr;
////
////      wstring wstr(lpszFileName);
////
////      if((wAttr = windows_get_file_attributes(wstr)) == (unsigned int)-1L)
////      {
////
////         ::windows::file_exception::throw_os_error( (int)get_last_error());
////
////      }
////
////      if ((unsigned int)status.m_attribute != wAttr && (wAttr & ::windows::file::readOnly))
////      {
////
////         // set file attribute, only if currently readonly.
////         // This way we will be able to modify the time assuming the
////         // caller changed the file from readonly.
////
////         if (!SetFileAttributesW(wstr, (unsigned int)status.m_attribute))
////         {
////
////            ::windows::file_exception::throw_os_error( (int)get_last_error());
////
////         }
////
////      }
////
////      // last modification time
////      if (status.m_mtime.get_time() != 0)
////      {
////
////         ::windows::TimeToFileTime(get_application(), status.m_mtime, &lastWriteTime);
////
////         lpLastWriteTime = &lastWriteTime;
////
////      }
////
////      // last access time
////      if (status.m_atime.get_time() != 0)
////      {
////
////         ::windows::TimeToFileTime(get_application(),status.m_atime, &lastAccessTime);
////
////         lpLastAccessTime = &lastAccessTime;
////
////      }
////
////      // create time
////      if (status.m_ctime.get_time() != 0)
////      {
////
////         ::windows::TimeToFileTime(get_application(),status.m_ctime, &creationTime);
////
////         lpCreationTime = &creationTime;
////
////      }
////
////      HANDLE hFile = ::CreateFileW(wstr, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
////
////      if(hFile == INVALID_HANDLE_VALUE)
////      {
////
////         ::windows::file_exception::throw_os_error( (int)::get_last_error());
////
////      }
////
////      if(!SetFileTime((HANDLE)hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime))
////      {
////
////         ::windows::file_exception::throw_os_error( (int)::get_last_error());
////
////      }
////
////      if(!::CloseHandle(hFile))
////      {
////
////         ::windows::file_exception::throw_os_error( (int)::get_last_error());
////
////      }
////
////      if ((unsigned int)status.m_attribute != wAttr && !(wAttr & ::windows::file::readOnly))
////      {
////
////         if (!::SetFileAttributesW(wstr, (unsigned int)status.m_attribute))
////         {
////
////            ::windows::file_exception::throw_os_error( (int)get_last_error());
////
////         }
////
////      }
//
//   }


   void os_context::file_open(const ::file::path & pathParam, const ::string & strParams, const ::file::path & pathFolder)
   {
      
      auto papplication = application();

      auto path = papplication->defer_process_path(pathParam);
      
//      // pretend actually gonna open the file here to trigger
//      // asking for file access permission
//
//      auto psystem = m_psystem->m_papexsystem;
//
//      auto preader = psystem->file().get_reader(path);

      ns_fork([path]()
      {

         ns_open_file(path.c_str());

      });

      //return true;

   }


   void os_context::link_open(const ::string & strUrl, const ::string & strProfile)
   {
      
      string strUrlCopy(strUrl);
      
      string strProfieCopy(strProfile);

      ns_main_post(^
      {

         ns_open_url(strUrlCopy.c_str());

      });

      //return success;

   }


//   void os_context::browse_folder(property_set &set)
//   {
//      
//      
//      throw "use node file::folder_dialog";
//      
////      const char * pszStartDir = nullptr;
////
////      string strStartDir;
////
////      if(set.has_property("folder"))
////      {
////
////         strStartDir = set["folder"].as_file_path();
////
////         pszStartDir = strStartDir;
////
////      }
////
////      auto psystem = acmesystem();
////
////      string strFolder = apple_browse_folder(psystem, pszStartDir, true);
////
////      if(strFolder.is_empty())
////      {
////
////         //return false;
////
////         return;
////
////      }
////
////      set["folder"] = strFolder;
////
////      //return true;
//
//   }
//
//
//   void os_context::browse_file_open(property_set &set)
//   {
//      
//      throw "use node file::folder_dialog";
//
////      const char * pszStartDir = nullptr;
////
////      string strStartDir;
////
////      if(set.has_property("folder"))
////      {
////
////         strStartDir =set["folder"].as_file_path();
////
////         pszStartDir = strStartDir;
////
////      }
////
////      bool bMulti = set["allow_multi_select"];
////      
////      auto psystem = acmesystem();
////
////      string_array straFileName = apple_browse_file_open(psystem, &pszStartDir, bMulti);
////
////      if(pszStartDir != nullptr && pszStartDir != strStartDir.c_str())
////      {
////
////         ::file::path pathFolder = ::file::path(::string_from_strdup((::string &) pszStartDir));
////
////         set["folder"] = pathFolder;
////
////      }
////
////      if(straFileName.is_empty())
////      {
////
////         //return false;
////         
////         return;
////
////      }
////
////
////      if(straFileName.get_count() == 1)
////      {
////
////         set["file_name"] = straFileName[0];
////
////      }
////      else
////      {
////
////         set["file_name"] = straFileName;
////
////      }
////
////      //return true;
//
//   }


   void os_context::set_this_application_as_default_for_file_extension(const ::string& strExtension)
   {
      
      string strFormattedExtension(strExtension);
      
      strFormattedExtension.trim();
      
      strFormattedExtension.trim(".");
      
      strFormattedExtension.trim();
      
      strFormattedExtension.trim(".");
      
      strFormattedExtension = "." + strFormattedExtension;
      
      setMyselfAsDefaultApplicationForFileExtension(strFormattedExtension);
      
   }
void os_context::register_user_auto_start(const string & strAppId, const ::file::path & pathExecutable, const string & strArguments,
                              bool bRegister) 
{

   if(strAppId == application()->m_strAppId)
  
   {
      
      macos_set_launch_on_login(bRegister);
      
   }
   else
   {
      
      apex_posix::os_context::register_user_auto_start(strAppId, pathExecutable, strAppId, bRegister);
      
   }

}

bool os_context::is_user_auto_start(const string & strAppId)
{
   
   if(strAppId == application()->m_strAppId)
  
   {
      
      return macos_launch_on_login();
      
   }
   else
   {
      
      return apex_posix::os_context::is_user_auto_start(strAppId);
      
   }
   
}


} // namespace apex_macos



