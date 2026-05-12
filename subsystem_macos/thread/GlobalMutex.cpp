// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
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
#include "framework.h"
#include "GlobalMutex.h"
#include "subsystem/node/SystemException.h"
//#include <Aclapi.h>


namespace subsystem_macos
{

GlobalMutex::GlobalMutex() :
    m_bNamed(false),
    m_psem(nullptr)
{

}


GlobalMutex::~GlobalMutex()
{
    if (m_bNamed)
    {
        if (m_psem != SEM_FAILED && m_psem != nullptr)
        {
            sem_close(m_psem);

            // Optional:
            // sem_unlink(m_strName.c_str());
        }
    }
    else
    {
        pthread_mutex_destroy(&m_mutex);
    }
}


void GlobalMutex::initialize_global_mutex(
    const ::scoped_string & scopedstrName,
    bool interProcess,
    bool throwIfExist)
{
    m_bNamed = interProcess;

    if (interProcess)
    {

        //
        // POSIX named semaphores REQUIRE leading '/'
        //
        m_strName = "/";
        m_strName += scopedstrName;

        int flags = O_CREAT;

        if (throwIfExist)
        {
            flags |= O_EXCL;
        }

        //
        // Initial value = 1 (mutex behavior)
        //
        m_psem = sem_open(
            m_strName.c_str(),
            flags,
            0666,
            1);

        if (m_psem == SEM_FAILED)
        {
            throw ::subsystem::SystemException();
        }

    }
    else
    {

        pthread_mutexattr_t attr;

        if (pthread_mutexattr_init(&attr) != 0)
        {
            throw ::subsystem::SystemException();
        }

        //
        // Recursive mutex behaves more like Windows mutex
        //
        pthread_mutexattr_settype(
            &attr,
            PTHREAD_MUTEX_RECURSIVE);

        if (pthread_mutex_init(&m_mutex, &attr) != 0)
        {
            pthread_mutexattr_destroy(&attr);

            throw ::subsystem::SystemException();
        }

        pthread_mutexattr_destroy(&attr);

    }
}


::e_status GlobalMutex::lock()
{
    if (m_bNamed)
    {

        if (sem_wait(m_psem) == 0)
        {
            return ::success;
        }

    }
    else
    {

        if (pthread_mutex_lock(&m_mutex) == 0)
        {
            return ::success;
        }

    }

    return error_failed;
}


void GlobalMutex::unlock()
{
    if (m_bNamed)
    {
        sem_post(m_psem);
    }
    else
    {
        pthread_mutex_unlock(&m_mutex);
    }
}

} // namespace subsystem_macos


