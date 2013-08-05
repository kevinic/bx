/*
 * Copyright 2010-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __BX_PLATFORM_H__
#define __BX_PLATFORM_H__

#define BX_COMPILER_CLANG 0
#define BX_COMPILER_GCC 0
#define BX_COMPILER_MSVC 0

#define BX_PLATFORM_ANDROID 0
#define BX_PLATFORM_EMSCRIPTEN 0
#define BX_PLATFORM_IOS 0
#define BX_PLATFORM_LINUX 0
#define BX_PLATFORM_NACL 0
#define BX_PLATFORM_OSX 0
#define BX_PLATFORM_QNX 0
#define BX_PLATFORM_WINDOWS 0
#define BX_PLATFORM_XBOX360 0

#define BX_CPU_ARM 0
#define BX_CPU_PPC 0
#define BX_CPU_X86 0

#define BX_ARCH_32BIT 0
#define BX_ARCH_64BIT 0

#define BX_CPU_ENDIAN_BIG 0
#define BX_CPU_ENDIAN_LITTLE 0

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Compilers
#if defined(_MSC_VER)
#	undef BX_COMPILER_MSVC
#	define BX_COMPILER_MSVC 1
#elif defined(__clang__)
// clang defines __GNUC__
#	undef BX_COMPILER_CLANG
#	define BX_COMPILER_CLANG 1
#elif defined(__GNUC__)
#	undef BX_COMPILER_GCC
#	define BX_COMPILER_GCC 1
#else
#	error "BX_COMPILER_* is not defined!"
#endif //

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Operating_Systems
#if defined(_XBOX_VER)
#	undef BX_PLATFORM_XBOX360
#	define BX_PLATFORM_XBOX360 1
#elif defined(_WIN32) || defined(_WIN64)
#	undef BX_PLATFORM_WINDOWS
#	define BX_PLATFORM_WINDOWS 1
#elif defined(__native_client__)
// NaCl compiler defines __linux__
#	undef BX_PLATFORM_NACL
#	define BX_PLATFORM_NACL 1
#elif defined(__ANDROID__)
// Android compiler defines __linux__
#	undef BX_PLATFORM_ANDROID
#	define BX_PLATFORM_ANDROID 1
#elif defined(__linux__)
#	undef BX_PLATFORM_LINUX
#	define BX_PLATFORM_LINUX 1
#elif defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
#	undef BX_PLATFORM_IOS
#	define BX_PLATFORM_IOS 1
#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
#	undef BX_PLATFORM_OSX
#	define BX_PLATFORM_OSX 1
#elif defined(EMSCRIPTEN)
#	undef BX_PLATFORM_EMSCRIPTEN
#	define BX_PLATFORM_EMSCRIPTEN 1
#elif defined(__QNX__)
#	undef BX_PLATFORM_QNX
#	define BX_PLATFORM_QNX 1
#else
#	error "BX_PLATFORM_* is not defined!"
#endif //

#define BX_PLATFORM_POSIX (BX_PLATFORM_ANDROID \
						|| BX_PLATFORM_EMSCRIPTEN \
						|| BX_PLATFORM_IOS \
						|| BX_PLATFORM_LINUX \
						|| BX_PLATFORM_NACL \
						|| BX_PLATFORM_OSX \
						|| BX_PLATFORM_QNX)

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Architectures
#if defined(__arm__)
#	undef BX_CPU_ARM
#	define BX_CPU_ARM 1
#	define BX_CACHE_LINE_SIZE 64
#elif defined(_M_PPC) || defined(__powerpc__) || defined(__powerpc64__)
#	undef BX_CPU_PPC
#	define BX_CPU_PPC 1
#	define BX_CACHE_LINE_SIZE 128
#elif defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__x86_64__)
#	undef BX_CPU_X86
#	define BX_CPU_X86 1
#	define BX_CACHE_LINE_SIZE 64
#endif // 

#if defined(__x86_64__) || defined(_M_X64) || defined(__64BIT__) || defined(__powerpc64__) || defined(__ppc64__)
#	undef BX_ARCH_64BIT
#	define BX_ARCH_64BIT 1
#else
#	undef BX_ARCH_32BIT
#	define BX_ARCH_32BIT 1
#endif //

#if BX_CPU_PPC
#	undef BX_CPU_ENDIAN_BIG
#	define BX_CPU_ENDIAN_BIG 1
#else
#	undef BX_CPU_ENDIAN_LITTLE
#	define BX_CPU_ENDIAN_LITTLE 1
#endif // BX_PLATFORM_

#ifndef  BX_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS
#	define BX_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS 0
#endif // BX_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS

#if BX_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS && BX_COMPILER_MSVC
#	pragma warning(error:4062) // ENABLE warning C4062: enumerator'...' in switch of enum '...' is not handled
#	pragma warning(error:4121) // ENABLE warning C4121: 'symbol' : alignment of a member was sensitive to packing
#	pragma warning(error:4130) // ENABLE warning C4130: 'operator' : logical operation on address of string constant
#	pragma warning(error:4239) // ENABLE warning C4239: nonstandard extension used : 'argument' : conversion from '*' to '* &' A non-const reference may only be bound to an lvalue
//#	pragma warning(error:4244) // ENABLE warning C4244: 'conversion' conversion from 'type1' to 'type2', possible loss of data
#	pragma warning(error:4263) // ENABLE warning C4263: 'function' : member function does not override any base class virtual member function
#	pragma warning(error:4265) // ENABLE warning C4265: class has virtual functions, but destructor is not virtual
#	pragma warning(error:4431) // ENABLE warning C4431: missing type specifier - int assumed. Note: C no longer supports default-int
#	pragma warning(error:4545) // ENABLE warning C4545: expression before comma evaluates to a function which is missing an argument list
#	pragma warning(error:4549) // ENABLE warning C4549: 'operator' : operator before comma has no effect; did you intend 'operator'?
#	pragma warning(error:4701) // ENABLE warning C4701: potentially uninitialized local variable 'name' used
#	pragma warning(error:4706) // ENABLE warning C4706: assignment within conditional expression
#	pragma warning(error:4100) // ENABLE warning C4100: '' : unreferenced formal parameter
#	pragma warning(error:4189) // ENABLE warning C4189: '' : local variable is initialized but not referenced
#	pragma warning(error:4505) // ENABLE warning C4505: '' : unreferenced local function has been removed
#endif // BX_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS && BX_COMPILER_MSVC

#if BX_PLATFORM_WINDOWS
// http://msdn.microsoft.com/en-us/library/6sehtctf.aspx
#	if !defined(WINVER) && !defined(_WIN32_WINNT)
		// Windows 2000 and above
#		define WINVER 0x0500
#		define _WIN32_WINNT 0x0500
#	endif // !defined(WINVER) && !defined(_WIN32_WINNT)
#endif // BX_PLATFORM_WINDOWS

#endif // __BX_PLATFORM_H__
