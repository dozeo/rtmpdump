#ifndef __RTMP_SHARED_H__
#define __RTMP_SHARED_H__

/*
 *      Copyright (C) 2005-2008 Team XBMC
 *      http://www.xbmc.org
 *      Copyright (C) 2008-2009 Andrej Stepanchuk
 *      Copyright (C) 2009-2010 Howard Chu
 *
 *  This file is part of librtmp.
 *
 *  librtmp is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation; either version 2.1,
 *  or (at your option) any later version.
 *
 *  librtmp is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with librtmp see the file COPYING.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
 *  http://www.gnu.org/copyleft/lgpl.html
 */


#if defined(RTMP_EXPORT_DLL) || defined(RTMP_IMPORT_DLL)
#  if defined(RTMP_EXPORT_DLL)
#    define RTMP_EXPORT __declspec(dllexport)
#  else
#    define RTMP_EXPORT __declspec(dllimport)
#  endif
#else
#  define RTMP_EXPORT
#endif


#endif //__RTMP_SHARED_H__
