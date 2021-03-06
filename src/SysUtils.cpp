/*
 * ZeroTier SDK - Network Virtualization Everywhere
 * Copyright (C) 2011-2018  ZeroTier, Inc.  https://www.zerotier.com/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * --
 *
 * You can be released from the requirements of the license by purchasing
 * a commercial license. Buying such a license is mandatory as soon as you
 * develop commercial closed-source software that incorporates or links
 * directly against ZeroTier software without disclosing the source code
 * of your own application.
 */

/**
 * @file
 *
 * Platform-specific implementations of common functions
 */

#if defined(STACK_LWIP)
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/ip_addr.h"
#include "lwip/netdb.h"
#include "dns.h"
#endif
#if defined(NO_STACK)
#include <sys/socket.h>
#endif

#if defined(__linux__) || defined(__APPLE__)
#include <sys/socket.h>
#include <pthread.h>
#endif

#include "SysUtils.h"
#include <stdint.h>

#ifdef __linux__
#include <sys/syscall.h>
#include <unistd.h>
#endif

inline unsigned int gettid()
{
#ifdef _WIN32
		//return GetCurrentThreadId();
		return 0;
#elif defined(__linux__)
		return static_cast<unsigned int>(syscall(__NR_gettid));
#elif defined(__APPLE__)
		uint64_t tid64;
		pthread_threadid_np(0, &tid64);
		return static_cast<unsigned int>(tid64);
#endif
}
