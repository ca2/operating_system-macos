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


#include "subsystem_macos/_common_header.h"


#include <sys/time.h>

namespace subsystem_macos
{

class WinTimeMillis
{
public:

    WinTimeMillis()
    {
        update();
    }

    virtual ~WinTimeMillis() = default;

    bool update()
    {
        return setToCurrentTime();
    }

    int diffFrom(const WinTimeMillis* older) const
    {
        time_t sec =
            m_time.tv_sec - older->m_time.tv_sec;

        suseconds_t usec =
            m_time.tv_usec - older->m_time.tv_usec;

        return (int)((sec * 1000) + (usec / 1000));
    }

protected:

    bool setToCurrentTime()
    {
        return gettimeofday(&m_time, nullptr) == 0;
    }

    const timeval* getTime() const
    {
        return &m_time;
    }

    timeval m_time;
};

}
