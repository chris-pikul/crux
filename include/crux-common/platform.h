#pragma once

/*
 * Defines useful macros for usage with the rest of crux systems,
 * as well as an enum for switching and a global constant keeping the derived platform
 */

//Macro variables for switching code later
#ifndef CRUX_PLATFORM
	#ifdef CRUX_WIN32
		#define CRUX_PLATFORM "Win32"
	#elif defined(WIN32) || defined(__WIN32__) || defined(__MINGW32__)
		#define CRUX_WIN32 1
		#define CRUX_PLATFORM "Win32"
	#endif
#endif

namespace crux {
	/// Defines the platform by name
	enum class Platform {
		NONE = 0,

		WINDOWS,
		MAC,
		LINUX,
	};

	/// Define the platform using the macro definitions for global usage
#if CRUX_WIN32
	const Platform TargetPlatform = Platform::WINDOWS;
#else
	const Platform TargetPlatform = Platform::NONE;
#endif
}

#if CRUX_WIN32
#include "platform.win32.h"
#endif