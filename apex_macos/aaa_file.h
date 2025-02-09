#pragma once


class FileException;
struct FileStatus;


void CLASS_DECL_APEX vfxGetRoot(const unichar * lpszPath, string& wstrRoot);


namespace macos
{


   class CLASS_DECL_APEX file :
      virtual public ::file::file
   {
   public:

      
      enum Attribute
      {
         
         normal =    0x00,
         readOnly =  0x01,
         hidden =    0x02,
         system =    0x04,
         volume =    0x08,
         directory = 0x10,
         archive =   0x20
         
      };
      

      enum
      {

         hFileNull = -1

      };
      

      enum BufferCommand
      {

         bufferRead,
         bufferWrite,
         bufferCommit,
         bufferCheck

      };

      
      string         m_strFileName;
      int            m_iFile;


      file();
      virtual ~file();


      virtual void assert_ok() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual filesize get_position() const override;


      virtual bool get_status(::file::file_status & status) const override;
      virtual ::file::path get_file_path() const override;
      virtual void set_file_path(const ::file::path & path)override;

      virtual ::extended::status open(const ::file::path & lpszFileName, const ::file::e_open & eopenflags)override;

      //virtual bool PASCAL GetStatus(const char * lpszFileName, ::file::file_status& rStatus);

      //unsigned long long ReadHuge(void * lpBuffer, unsigned long long dwCount);
      //void WriteHuge(const void * lpBuffer, unsigned long long dwCount);

      //virtual ::pointer < ::file::file > Duplicate() const;

      virtual filesize seek(filesize lOff, ::enum_seek nFrom)override;
      virtual void set_size(filesize dwNewLen)override;
      virtual filesize get_size() const override;

      virtual memsize read(void * lpBuf, memsize nCount)override;
      virtual void write(const void * lpBuf, memsize nCount)override;

      virtual void lock(filesize dwPos, filesize dwCount)override;
      virtual void unlock(filesize dwPos, filesize dwCount)override;

      //virtual void Abort();
      virtual void flush() override;
      virtual void close() override;

      virtual bool is_opened() const override;
//      virtual unsigned long long GetBufferPtr(unsigned int nCommand, unsigned long long nCount = 0, void ** ppBufStart = nullptr, void ** ppBufMax = nullptr);


   };


} // namespace macos



