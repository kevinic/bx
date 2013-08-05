/*
 * Copyright 2010-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __BX_MUTEX_H__
#define __BX_MUTEX_H__

#include "bx.h"
#include "cpu.h"
#include "sem.h"

#if BX_PLATFORM_NACL || BX_PLATFORM_LINUX || BX_PLATFORM_ANDROID || BX_PLATFORM_OSX
#	include <pthread.h>
#elif BX_PLATFORM_WINDOWS || BX_PLATFORM_XBOX360
#	include <errno.h>
#endif // BX_PLATFORM_

namespace bx
{
#if BX_PLATFORM_WINDOWS || BX_PLATFORM_XBOX360
	typedef CRITICAL_SECTION pthread_mutex_t;
	typedef unsigned pthread_mutexattr_t;

	inline int pthread_mutex_lock(pthread_mutex_t* _mutex)
	{
		EnterCriticalSection(_mutex);
		return 0;
	}

	inline int pthread_mutex_unlock(pthread_mutex_t* _mutex)
	{
		LeaveCriticalSection(_mutex);
		return 0;
	}

	inline int pthread_mutex_trylock(pthread_mutex_t* _mutex)
	{
		return TryEnterCriticalSection(_mutex) ? 0 : EBUSY;
	}

	inline int pthread_mutex_init(pthread_mutex_t* _mutex, pthread_mutexattr_t* /*_attr*/)
	{
		InitializeCriticalSection(_mutex);
		return 0;
	}

	inline int pthread_mutex_destroy(pthread_mutex_t* _mutex)
	{
		DeleteCriticalSection(_mutex);
		return 0;
	}
#endif // BX_PLATFORM_

	class Mutex
	{
	public:
		Mutex()
		{
			pthread_mutex_init(&m_handle, NULL);
		}

		~Mutex()
		{
			pthread_mutex_destroy(&m_handle);
		}

		void lock()
		{
			pthread_mutex_lock(&m_handle);
		}

		void unlock()
		{
			pthread_mutex_unlock(&m_handle);
		}

	private:
		Mutex(const Mutex& _rhs); // no copy constructor
		Mutex& operator=(const Mutex& _rhs); // no assignment operator

		pthread_mutex_t m_handle;
	};

	class MutexScope
	{
	public:
		MutexScope(Mutex& _mutex)
			: m_mutex(_mutex)
		{
			m_mutex.lock();
		}

		~MutexScope()
		{
			m_mutex.unlock();
		}

	private:
		MutexScope(); // no default constructor
		MutexScope(const MutexScope& _rhs); // no copy constructor
		MutexScope& operator=(const MutexScope& _rhs); // no assignment operator

		Mutex& m_mutex;
	};

#if 1
	typedef Mutex LwMutex;
#else
	class LwMutex
	{
	public:
		LwMutex()
			: m_count(0)
		{
		}

		~LwMutex()
		{
		}

		void lock()
		{
			if (atomicIncr(&m_count) > 1)
			{
				m_sem.wait();
			}
		}

		void unlock()
		{
			if (atomicDecr(&m_count) > 0)
			{
				m_sem.post();
			}
		}

	private:
		LwMutex(const LwMutex& _rhs); // no copy constructor
		LwMutex& operator=(const LwMutex& _rhs); // no assignment operator

		Semaphore m_sem;
		volatile int32_t m_count;
	};
#endif // 0

	class LwMutexScope
	{
	public:
		LwMutexScope(LwMutex& _mutex)
			: m_mutex(_mutex)
		{
			m_mutex.lock();
		}

		~LwMutexScope()
		{
			m_mutex.unlock();
		}

	private:
		LwMutexScope(); // no default constructor
		LwMutexScope(const LwMutexScope& _rhs); // no copy constructor
		LwMutexScope& operator=(const LwMutexScope& _rhs); // no assignment operator

		LwMutex& m_mutex;
	};

} // namespace bx

#endif // __BX_MUTEX_H__
