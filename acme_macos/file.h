#pragma once


class FileException;
struct FileStatus;


void CLASS_DECL_ACME vfxGetRoot(const unichar * lpszPath, string& wstrRoot);


namespace macos
{


   class CLASS_DECL_ACME file :
      virtual public ::file::file
   {
   public:


      //__creatable_from_library(file, ::file::file, "acme_macos");

      
      // enum Attribute
      // {
         
      //    normal =    0x00,
      //    readOnly =  0x01,
      //    hidden =    0x02,
      //    system =    0x04,
      //    volume =    0x08,
      //    directory = 0x10,
      //    archive =   0x20
         
      // };
      

      // enum
      // {

      //    hFileNull = -1

      // };
      

      // enum BufferCommand
      // {

      //    bufferRead,
      //    bufferWrite,
      //    bufferCommit,
      //    bufferCheck

      // };

      
      string         m_strFileName;
      i32            m_iFile;
      i32            m_iPutCharacterBack;


      file();
      ~file() override;


      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;


      filesize get_position() const override;


      bool get_status(::file::file_status & status) const override;
      ::file::path get_file_path() const override;
      void set_file_path(const ::file::path & path)override;

      void open(const ::file::path & lpszFileName, const ::file::e_open & eopenflags)override;

      filesize translate(filesize offset, ::enum_seek nFrom)override;
      void set_size(filesize dwNewLen)override;
      filesize get_size() const override;

      memsize read(void * lpBuf, memsize nCount)override;
      void write(const void * lpBuf, memsize nCount)override;

      void lock(filesize dwPos, filesize dwCount)override;
      void unlock(filesize dwPos, filesize dwCount)override;

      //virtual void Abort();
      void flush() override;
      void close() override;

      bool is_opened() const override;
//      virtual u64 GetBufferPtr(::u32 nCommand, u64 nCount = 0, void ** ppBufStart = nullptr, void ** ppBufMax = nullptr);

      int put_character_back(int iCharacter) override;
      

   };


} // namespace macos



