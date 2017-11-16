/* This file is part of the KDE project
   Copyright (C) 2003-2005 Jaroslaw Staniek <staniek@kde.org>
   Copyright (C) 2005 Christian Ehrlicher <Ch.Ehrlicher@gmx.de>
   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
   You should have received a copy of the GNU Library General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

// dkimitsa: thanks https://github.com/KDE/kdewin

#ifndef __CCTOOLS_PORT_SYS_TIME_H__
#define __CCTOOLS_PORT_SYS_TIME_H__

#include_next <sys/time.h>

#if (defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__)

/*errno==EACCES on read-only devices */
extern int utimes(const char *filename, const struct timeval times[2]);

#endif // WIN32

#endif // __CCTOOLS_PORT_SYS_TIME_H__
