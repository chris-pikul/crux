#pragma once

#include "platform.h"

#if CRUX_WIN32

#include <string>
#include <vector>
namespace crux::internal::win32 {
	/**
	 * @brief Converts an std::string into a std::wstring for use with Win32 API
	 * @param input string to convert
	 * @return Converted wide string
	*/
	std::wstring StringToWideString(const std::string&);

	/**
	 * @brief Converts an std::wstring into a std::string for use with Win32 API
	 * @param input wide string to convert
	 * @return Converted string
	*/
	std::string WideStringToString(const std::wstring&);

	/**
	 * @brief Wraps the Win32 API GetLastError() function to include
	 * the appropriate FormatMessage code to return a string version.
	 * @return String of the last Win32 API error to occure
	*/
	std::string GetLastErrorString();

	/**
	 * @brief Checks if the given Windows library has been loaded
	 * @param name Library name (OS specific)
	 * @return True if the library has been loaded
	*/
	bool HasWinLibrary(const std::string& name);

	/**
	 * @brief Attempts to load a Windows library.
	 * If successful, the library name will be kept in an internal map for
	 * handle retrieval and cleanup purposes.
	 * If the library was already loaded, the existing process is returned.
	 * @param name Library name (OS specific)
	 * @return Pointer to the library process
	*/
	void* LoadWinLibrary(const std::string& name);

	/**
	 * @brief Attempts to load Windows libraries.
	 * If successful, the library name will be kept in an internal map for
	 * handle retrieval and cleanup purposes.
	 * @param names Vector of library names (OS specific)
	 * @return Vector of names successfully loaded (including existing libraries)
	*/
	const std::vector<std::string> LoadWinLibraries(const std::vector<std::string>& names);

	/**
	 * @brief Gets a pointer to the library process matching the given name.
	 * If the library has not been loaded, then nullptr is returned instead.
	 * @param name Library name (OS specific)
	 * @return Pointer to the library process
	*/
	void* GetWinLibrary(const std::string& name);

	/**
	 * @brief Releases the library processes from this application based
	 * on the provided name. If the library was not loaded, this will
	 * silently return.
	 * @param name Library name (OS specific)
	*/
	void FreeWinLibrary(const std::string& name);

	/**
	 * @brief Releases all library processes loaded.
	*/
	void FreeAllWinLibraries();
}

#endif // CRUX_WIN32
