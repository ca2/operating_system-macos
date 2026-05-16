// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once

#include "subsystem/thread/Thread.h"
#include "subsystem_macos/_common_header.h"
//#include "critical_section.h"
//#include "DesktopSelector.h"
//#pragma once

#include <pthread.h>
#include <atomic>

namespace subsystem_macos
{

class Thread :
virtual public Implementation<::subsystem::ThreadCallback>

{
public:

    Thread();
    ~Thread() override;

    ::e_status wait() override;

    bool suspend() override;
    bool resume() override;

    void terminate() override;

   bool isActive() const override;

    ::iptr getThreadId() const override;

    bool setPriority(
        ::subsystem::THREAD_PRIORITY value) override;

    void sleep(
        const class ::time& time) override;

    void yield() override;

    bool isTerminating() override;

protected:

    virtual void initByDerived() override;
    virtual void onTerminate() override;
    virtual void execute() override;

private:

    static void* threadProc(void* pThread);

    void waitIfSuspended();

protected:

    pthread_t m_thread {};

    pthread_mutex_t m_suspendMutex {};
    pthread_cond_t  m_suspendCond {};

    std::atomic<bool> m_terminated { false };
    std::atomic<bool> m_active { false };
    std::atomic<bool> m_suspended { true };

    ::iptr m_threadID {};

    // your callback object
    //decltype(m_pthreadCallback) m_pthreadCallback;
   //::procedure m_procedureCallback;
};

} //namespace subsystem_macos


