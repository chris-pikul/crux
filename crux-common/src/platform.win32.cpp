#if CRUX_WIN32
#include "platform.win32.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>
#include <stringapiset.h>
#include <map>
#include <mutex>

namespace crux::internal::win32 {
	std::mutex LibraryLock;
	std::map<std::string, void*> LoadedLibraries;

	std::wstring StringToWideString(const std::string& s) {
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}

	std::string WideStringToString(const std::wstring& ws) {
		std::string strTo;
		char* szTo = new char[ws.length() + 1];
		szTo[ws.size()] = '\0';
		WideCharToMultiByte(CP_ACP, 0, ws.c_str(), -1, szTo, (int)ws.length(), NULL, NULL);
		strTo = szTo;
		delete[] szTo;
		return strTo;
	}

	std::string GetLastErrorString() {
		DWORD errorCode = GetLastError();

		//If no error, return empty
		if (!errorCode) return "";

		//Use the Win32 API to get the error message
		LPWSTR buffer = nullptr;
		DWORD size = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			errorCode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPWSTR)&buffer,
			0,
			nullptr
		);

		//Convert to string
		if (size) {
			//Format the message
			std::wstring message(buffer, size);

			//Free the buffer
			LocalFree(buffer);

			return WideStringToString(message);
		}

		//Buffer was empty
		return "";
	}

	bool HasWinLibrary(const std::string& name) {
		std::lock_guard<std::mutex> Lock(LibraryLock);
		return LoadedLibraries.find(name) != LoadedLibraries.end();
	}

	void* LoadWinLibrary(const std::string& name) {
		std::lock_guard<std::mutex> Lock(LibraryLock);
		auto exists = LoadedLibraries.find(name);
		if (exists != LoadedLibraries.end()) {
			return exists->second;
		}

		auto proc = LoadLibrary(StringToWideString(name).c_str());
		if (proc != nullptr) {
			LoadedLibraries.emplace(name, proc);
			return proc;
		}

		return nullptr;
	}

	const std::vector<std::string> LoadWinLibraries(const std::vector<std::string>& names) {
		std::lock_guard<std::mutex> Lock(LibraryLock);

		std::vector<std::string> loaded;

		for (auto name : names) {
			auto exists = LoadedLibraries.find(name);
			if (exists != LoadedLibraries.end())
				continue;

			auto proc = LoadLibrary(StringToWideString(name).c_str());
			if (proc != nullptr) {
				LoadedLibraries.emplace(name, proc);
				loaded.emplace_back(name);
			}
		}

		return loaded;
	}

	void* GetWinLibrary(const std::string& name) {
		std::lock_guard<std::mutex> Lock(LibraryLock);
		auto proc = LoadedLibraries.find(name);
		if (proc != LoadedLibraries.end())
			return proc->second;
		return nullptr;
	}

	void FreeWinLibrary(const std::string& name) {
		std::lock_guard<std::mutex> Lock(LibraryLock);
		auto proc = LoadedLibraries.find(name);
		if (proc != LoadedLibraries.end())
			LoadedLibraries.erase(proc);
	}

	void FreeAllWinLibraries() {
		std::lock_guard<std::mutex> Lock(LibraryLock);

		for (const auto& [key, value] : LoadedLibraries) {
			if (value != nullptr) {
				FreeLibrary((HMODULE)value);
			}
		}
		LoadedLibraries.clear();
	}
}

#endif // CRUX_WIN32