#pragma once


namespace macos
{


   class CLASS_DECL_BASE print_job :
      virtual public ::user::print_task
   {
   public:


      print_job();
      virtual ~print_job();


      virtual void     run() override;


   };


} // namespace macos




