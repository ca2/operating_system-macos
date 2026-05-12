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


#include <Security/Security.h>
#include <CoreFoundation/CoreFoundation.h>

#include <openssl/evp.h>
#include <openssl/rand.h>

#include <vector>
#include <string>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>


#include <mach/mach.h>

namespace subsystem_macos
{

   static ::subsystem_macos::subsystem *            g_p;
   static critical_section g_criticalsectionResolveIp4;

   //::subsystem_macos::subsystem * subsystem::s_p = nullptr;

   subsystem::subsystem()
   {

      g_p = this;
//      m_i_LOADER_CLOSE_CODE = -1;
//      m_i_SPEC_IPC_CODE = -1;

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

       _parse_macos_command_line_arguments(pcommandlinearguments, strCommandLine);

       return pcommandlinearguments;

   }


static const char* kServiceName =
    "MyApplicationEncryption";

static const char* kAccountName =
    "AES256Key";


// =====================================================
// Keychain Helpers
// =====================================================

static bool LoadOrCreateKey(
    memory & key)
{
    key.set_size(32);

    void* data = nullptr;
    UInt32 length = 0;

    OSStatus status =
        SecKeychainFindGenericPassword(
            nullptr,
            (UInt32)strlen(kServiceName),
            kServiceName,
            (UInt32)strlen(kAccountName),
            kAccountName,
            &length,
            &data,
            nullptr);

    if (status == errSecSuccess)
    {
        if (length != 32)
        {
            SecKeychainItemFreeContent(
                nullptr,
                data);

            return false;
        }

        memcpy(key.data(), data, 32);

        SecKeychainItemFreeContent(
            nullptr,
            data);

        return true;
    }

    // Create new key

    if (RAND_bytes(key.data(), 32) != 1)
        return false;

    status =
        SecKeychainAddGenericPassword(
            nullptr,
            (UInt32)strlen(kServiceName),
            kServiceName,
            (UInt32)strlen(kAccountName),
            kAccountName,
            32,
            key.data(),
            nullptr);

    return status == errSecSuccess;
}


// =====================================================
// Encrypt
// =====================================================

bool subsystem::EncryptData(const ::string& input, ::memory & output)
{
    ::memory key;

    if (!LoadOrCreateKey(key))
        return false;

    EVP_CIPHER_CTX* ctx =
        EVP_CIPHER_CTX_new();

    if (!ctx)
        return false;

    const size_t ivSize = 12;
    const size_t tagSize = 16;

    uint8_t iv[ivSize];

    if (RAND_bytes(iv, ivSize) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_EncryptInit_ex(
            ctx,
            EVP_aes_256_gcm(),
            nullptr,
            nullptr,
            nullptr) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_CIPHER_CTX_ctrl(
            ctx,
            EVP_CTRL_GCM_SET_IVLEN,
            ivSize,
            nullptr) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_EncryptInit_ex(
            ctx,
            nullptr,
            nullptr,
            key.data(),
            iv) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

   ::memory ciphertext;
   
   ciphertext.set_size(   input.size());

    int outLen = 0;

    if (EVP_EncryptUpdate(
            ctx,
            ciphertext.data(),
            &outLen,
            (const uint8_t*)input.data(),
            (int)input.size()) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    int finalLen = 0;

    if (EVP_EncryptFinal_ex(
            ctx,
            ciphertext.data() + outLen,
            &finalLen) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    ciphertext.set_size(outLen + finalLen);

    uint8_t tag[tagSize];

    if (EVP_CIPHER_CTX_ctrl(
            ctx,
            EVP_CTRL_GCM_GET_TAG,
            tagSize,
            tag) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    EVP_CIPHER_CTX_free(ctx);

    // Output format:
    // [12-byte IV][16-byte TAG][ciphertext]

    output.clear();

    output.append(
        iv,
                  ivSize);
   
   
   output.append(
        tag,
        tagSize);

    output.append(
        ciphertext.begin(),
        ciphertext.size());

    return true;
}


// =====================================================
// Decrypt
// =====================================================

bool subsystem::DecryptData(const memory & input, ::string& output)
{
    const size_t ivSize = 12;
    const size_t tagSize = 16;

    if (input.size() < ivSize + tagSize)
        return false;

    ::memory key;

    if (!LoadOrCreateKey(key))
        return false;

    const uint8_t* iv =
        input.data();

    const uint8_t* tag =
        input.data() + ivSize;

    const uint8_t* ciphertext =
        input.data() + ivSize + tagSize;

    size_t ciphertextSize =
        input.size() - ivSize - tagSize;

    EVP_CIPHER_CTX* ctx =
        EVP_CIPHER_CTX_new();

    if (!ctx)
        return false;

    if (EVP_DecryptInit_ex(
            ctx,
            EVP_aes_256_gcm(),
            nullptr,
            nullptr,
            nullptr) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_CIPHER_CTX_ctrl(
            ctx,
            EVP_CTRL_GCM_SET_IVLEN,
            ivSize,
            nullptr) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_DecryptInit_ex(
            ctx,
            nullptr,
            nullptr,
            key.data(),
            iv) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

   ::memory plaintext;
   
   plaintext.set_size(
        ciphertextSize);

    int outLen = 0;

    if (EVP_DecryptUpdate(
            ctx,
            plaintext.data(),
            &outLen,
            ciphertext,
            (int)ciphertextSize) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    if (EVP_CIPHER_CTX_ctrl(
            ctx,
            EVP_CTRL_GCM_SET_TAG,
            tagSize,
            (void*)tag) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    int finalLen = 0;

    int ret =
        EVP_DecryptFinal_ex(
            ctx,
            plaintext.data() + outLen,
            &finalLen);

    EVP_CIPHER_CTX_free(ctx);

    if (ret != 1)
    {
        // Authentication failed
        return false;
    }

    plaintext.set_size(outLen + finalLen);

    output.assign(
        (char*)plaintext.data(),
        plaintext.size());

    return true;
}



//   bool subsystem::EncryptData(const ::string& input, ::memory & output)
//   {
//
////   DATA_BLOB inBlob;
////   DATA_BLOB outBlob;
////
////   inBlob.pbData = (unsigned char*)input.data();
////   inBlob.cbData = (DWORD)input.size();
////
////   if (!CryptProtectData(&inBlob, nullptr, nullptr, nullptr, nullptr, 0, &outBlob))
////      return false;
////
////   output.assign(outBlob.pbData, outBlob.cbData);
////   LocalFree(outBlob.pbData);
//   return true;
//}
//
//   bool subsystem::DecryptData(const memory & input, ::string& output)
//{
////   DATA_BLOB inBlob;
////   DATA_BLOB outBlob;
////
////   inBlob.pbData = (unsigned char*)input.data();
////   inBlob.cbData = (DWORD)input.size();
////
////   if (!CryptUnprotectData(&inBlob, nullptr, nullptr, nullptr, nullptr, 0, &outBlob))
////      return false;
////
////   output.assign((char*)outBlob.pbData, outBlob.cbData);
////   LocalFree(outBlob.pbData);
//   return true;
//}


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
         
         throw not_implemented();
         
         return nullptr;

//   auto pfile = create_newø<::subsystem_macos::File>();
//
//   pfile->m_handle = (HANDLE)pHANDLE;
//
//   return pfile;
}

pointer<::subsystem::FileInterface> subsystem::fileFrom_fd(int fd)
{

auto pfile = create_newø<::subsystem_macos::File>();

pfile->m_iFd = fd;

return pfile;
}



memsize subsystem::getCurrentMemoryUsage()
{
    mach_task_basic_info info;
    mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;

    kern_return_t kr = task_info(
        mach_task_self(),
        MACH_TASK_BASIC_INFO,
        reinterpret_cast<task_info_t>(&info),
        &infoCount
    );

    if (kr != KERN_SUCCESS)
    {
        return 0;
    }

    // Resident memory size (similar to WorkingSetSize on Windows)
    return static_cast<memsize>(info.resident_size);
}

void subsystem::toString(::string & str, const ::earth::time & time)
{
    // Assuming ::earth::time can convert to time_t
    time_t rawTime = (time_t)time.m_iSecond;

    // Convert to local time
    struct tm localTime;

#if defined(__APPLE__) || defined(__unix__)
    localtime_r(&rawTime, &localTime);
#else
    localTime = *localtime(&rawTime);
#endif

    // Format using locale-aware date/time representation
    char buffer[256];

    // %x = locale date representation
    // %X = locale time representation
    if (strftime(buffer, sizeof(buffer), "%x %X", &localTime) > 0)
    {
        str = buffer;
    }
    else
    {
        str = "";
    }
}

//   int subsystem::get_LOADER_CLOSE_CODE()
//   {
//
//      if (m_i_LOADER_CLOSE_CODE < 0)
//      {
//
//         m_i_LOADER_CLOSE_CODE = RegisterWindowMessageW(L"TVN.HOOK.LOADER.CLOSE.CODE");
//
//      }
//
//      return m_i_LOADER_CLOSE_CODE;
//
//   }
//
//
//   int subsystem::get_SPEC_IPC_CODE()
//   {
//
//      if (m_i_SPEC_IPC_CODE < 0)
//      {
//
//         m_i_SPEC_IPC_CODE = RegisterWindowMessageW(L"TVN.HOOK.MESSAGE.CODE");
//
//      }
//
//      return m_i_LOADER_CLOSE_CODE;
//
//   }
//   

   // RegisterWindowMessage("TVN.HOOK.LOADER.CLOSE.CODE");
   // const unsigned int HookDefinitions::SPEC_IPC_CODE =
   // RegisterWindowMessage("TVN.HOOK.MESSAGE.CODE");


}//namespace subsystem_macos


CLASS_DECL_SUBSYSTEM_MACOS ::subsystem_macos::subsystem & MacosSubsystem()
{

   if (!::subsystem_macos::g_p)
   {

      MainSubsystem();

   }

   return *::subsystem_macos::g_p;

}

