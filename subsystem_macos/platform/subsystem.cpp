//
// Created by camilo on 2026-04-05 03:04 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"
#include "subsystem/platform/CommandLineArguments.h"
#include "node/File.h"
#include "node/OperatingSystem.h"
#include "node/Shell.h"
#include "node/WTS.h"
#include "node/PipeServer.h"
//#include <wincrypt.h>
//#include <shellapi.h>
//#pragma comment (lib, "Crypt32.lib")




namespace subsystem_macos
{

   static ::subsystem_macos::subsystem *            g_p;
   static critical_section g_criticalsectionResolveIp4;

   //::subsystem_macos::subsystem * subsystem::s_p = nullptr;

   subsystem::subsystem()
   {

      g_p = this;
      m_i_LOADER_CLOSE_CODE = -1;
      m_i_SPEC_IPC_CODE = -1;

   }


   subsystem::~subsystem()
   {


   }
//
//    ::subsystem_macos::WTS &subsystem::WTS()
//   {
//
//       if (!m_pwts)
//       {
//
//           construct_newø(m_pwts);
//
//          m_pwts->initialize_wts(::system());
//
//       }
//
//       return *m_pwts;
//
//
//   }
//

    PipeServer * subsystem::pipe_server()
   {

       if (!m_ppipeserver)
       {

           constructø(m_ppipeserver);

       }

       return m_ppipeserver;


   }

static ::string_array_base
parse_windows_command_line(const ::string& cmdline)
{
    ::string_array_base args;

    ::string current;
    bool inQuotes = false;

    ::collection::index i = 0;

    while (i < cmdline.size())
    {
        char c = cmdline[i];

        // whitespace outside quotes
        if (!inQuotes && ::character_isspace((char)c))
        {
            if (current.has_character())
            {
                args.add(current);
                current.clear();
            }

            ++i;
            continue;
        }

        // quote handling
        if (c == '"')
        {
            ::collection::index backslashCount = 0;

           ::collection::index j = i;

            while (j > 0 && cmdline[j - 1] == '\\')
            {
                ++backslashCount;
                --j;
            }

            // odd number of backslashes => escaped quote
            if (backslashCount % 2 == 1)
            {
                current.erase_end(1);
                current += '"';
            }
            else
            {
                inQuotes = !inQuotes;
            }

            ++i;
            continue;
        }

        current += c;
        ++i;
    }

    if (current.has_character())
    {
        args.add(current);
    }

    return args;
}

void subsystem::_parse_macos_command_line_arguments(
    ::subsystem::CommandLineArguments* pcommandlinearguments,
    const scoped_string& scopedstrCommandLineInWindowsFormat)
{
    ::string strCommandLine(scopedstrCommandLineInWindowsFormat);

    auto args =
        parse_windows_command_line(strCommandLine);

    for (auto& arg : args)
    {
        if (arg.has_character())
        {
            pcommandlinearguments->m_args.add(arg);
        }
    }
}



   pointer<::subsystem::CommandLineArguments> subsystem::getCurrentProcessCommandLineArguments()
   {

      ::string strCommandLine;

      //strCommandLine = ::GetCommandLineW();

      strCommandLine =::system()->command_line();

      auto pcommandlinearguments = getCommandLineArguments(strCommandLine);

      return pcommandlinearguments;

   }


   pointer<::subsystem::CommandLineArguments> subsystem::getCommandLineArguments(const scoped_string &scopedstrCommandLineInWindowsFormat)
   {

       auto pcommandlinearguments = create_newø<::subsystem::CommandLineArguments>();

       ::string strCommandLine;

       strCommandLine = scopedstrCommandLineInWindowsFormat;

       _parse_windows_command_line_arguments(pcommandlinearguments, strCommandLine);

       return pcommandlinearguments;

   }


   bool subsystem::EncryptData(const ::string& input, ::memory & output)
   {

   DATA_BLOB inBlob;
   DATA_BLOB outBlob;

   inBlob.pbData = (unsigned char*)input.data();
   inBlob.cbData = (DWORD)input.size();

   if (!CryptProtectData(&inBlob, nullptr, nullptr, nullptr, nullptr, 0, &outBlob))
      return false;

   output.assign(outBlob.pbData, outBlob.cbData);
   LocalFree(outBlob.pbData);
   return true;
}

   bool subsystem::DecryptData(const memory & input, ::string& output)
{
   DATA_BLOB inBlob;
   DATA_BLOB outBlob;

   inBlob.pbData = (unsigned char*)input.data();
   inBlob.cbData = (DWORD)input.size();

   if (!CryptUnprotectData(&inBlob, nullptr, nullptr, nullptr, nullptr, 0, &outBlob))
      return false;

   output.assign((char*)outBlob.pbData, outBlob.cbData);
   LocalFree(outBlob.pbData);
   return true;
}


   //int subsystem::get_last_socket_error()
   //{

   //   return WSAGetLastError();

   //}


   //string subsystem::get_socket_error_message_text(int iError)
   //{

   //   if (iError <= 0)
   //   {

   //      return {};

   //   }

   //   LPWSTR buffer = nullptr;

   //   DWORD size = FormatMessageW(
   //       FORMAT_MESSAGE_FROM_SYSTEM |
   //       FORMAT_MESSAGE_ALLOCATE_BUFFER |
   //       FORMAT_MESSAGE_IGNORE_INSERTS,
   //       nullptr,
   //       iError,
   //       MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
   //       (LPWSTR)&buffer,
   //       0,
   //       nullptr
   //   );

   //   ::wstring wstr;

   //   if (size && buffer)
   //   {

   //      wstr.assign(buffer, size);

   //   }

   //   LocalFree(buffer);  // always safe (even if buffer == nullptr)

   //   return wstr;

   //}

      pointer<::subsystem::FileInterface> subsystem::fileFrom_HANDLE(void *pHANDLE)
{

   auto pfile = create_newø<::subsystem_macos::File>();

   pfile->m_handle = (HANDLE)pHANDLE;

   return pfile;
}


   memsize subsystem::getCurrentMemoryUsage()
   {
   
      if (!OperatingSystem().isVistaOrLater())
      {
      
         return 0;

      }

      PROCESS_MEMORY_COUNTERS pmc;

      GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

      return pmc.WorkingSetSize;

    }


   void subsystem::toString(::string & str, const ::earth::time & time)
   {

      auto systemTime = as_SYSTEMTIME(time);

      toLocal_SYSTEMTIME(systemTime);

      const size_t dateStringMaxLength = 255;

      TCHAR dateString[dateStringMaxLength + 1];

      if (GetDateFormat(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &systemTime, 0, dateString, dateStringMaxLength) == 0)
      {
         // TODO: Process this error.
      }

      str = dateString;
      str += ' ';

      const size_t timeStringMaxLength = 255;

      TCHAR timeString[timeStringMaxLength + 1];

      if (GetTimeFormat(LOCALE_USER_DEFAULT, 0, &systemTime, 0, timeString, timeStringMaxLength) == 0)
      {
         // TODO: Process this error.
      }

      str += timeString;

   }


   int subsystem::get_LOADER_CLOSE_CODE()
   {

      if (m_i_LOADER_CLOSE_CODE < 0)
      {

         m_i_LOADER_CLOSE_CODE = RegisterWindowMessageW(L"TVN.HOOK.LOADER.CLOSE.CODE");

      }

      return m_i_LOADER_CLOSE_CODE;

   }


   int subsystem::get_SPEC_IPC_CODE()
   {

      if (m_i_SPEC_IPC_CODE < 0)
      {

         m_i_SPEC_IPC_CODE = RegisterWindowMessageW(L"TVN.HOOK.MESSAGE.CODE");

      }

      return m_i_LOADER_CLOSE_CODE;

   }
   

   // RegisterWindowMessage("TVN.HOOK.LOADER.CLOSE.CODE");
   // const unsigned int HookDefinitions::SPEC_IPC_CODE =
   // RegisterWindowMessage("TVN.HOOK.MESSAGE.CODE");


}//namespace subsystem_macos


CLASS_DECL_SUBSYSTEM_MACOS ::subsystem_macos::subsystem & WindowsSubsystem()
{

   if (!::subsystem_macos::g_p)
   {

      MainSubsystem();

   }

   return *::subsystem_macos::g_p;

}

