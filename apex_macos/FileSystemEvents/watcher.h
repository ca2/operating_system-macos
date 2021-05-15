#pragma once


namespace FileSystemEvents
{
   
   
   class CLASS_DECL_APEX watch :
      virtual public ::file::watch
   {
   public:


      FSEventStreamRef m_stream;


      watch();
      virtual ~watch();


      virtual bool open(const ::file::path & pathFolder, bool bRecursive) override;

      //void handle_action(::file::action * paction) override;


      static void myCallbackFunction(
      ConstFSEventStreamRef streamRef,
      void *clientCallBackInfo,
      size_t numEvents,
      void *eventPaths,
      const FSEventStreamEventFlags eventFlags[],
      const FSEventStreamEventId eventIds[]);
      
      void addAll();
      void eraseAll();

      ::e_status step() override;
      

   };
   

   class CLASS_DECL_APEX watcher :
      virtual public ::file::watcher
   {
   public:


      watcher();
      virtual ~watcher();

      
      ::e_status step() override;
      

   };


} // namespace FileSystemEvents




