#pragma once

#include <stdio.h>
#include <iostream>
#include <string>

#if CRUX_WIN32
	#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN 1
	#endif
	#include <windows.h>
	#include <stringapiset.h>
#endif
