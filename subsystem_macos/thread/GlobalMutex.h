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

#pragma once


#include "subsystem/platform/Exception.h"
#include "subsystem/thread/GlobalMutex.h"
#include "subsystem_macos/_common_header.h"

#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
namespace subsystem_macos
{


class GlobalMutex :
virtual public ::subsystem::GlobalMutex
{
public:

    GlobalMutex();
    ~GlobalMutex() override;

    void initialize_global_mutex(
        const ::scoped_string & scopedstrName,
        bool interProcess,
        bool throwIfExist);

    ::e_status lock();
    void unlock();

//protected:

    bool                m_bNamed;
    pthread_mutex_t     m_mutex;
    sem_t *             m_psem;
    ::string            m_strName;

};


   //// __GLOBALMUTEX_H__
} // namespace subsystem_macos
