#pragma once
#if CRUX_WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>

#include "window.h"

namespace crux::internal::win32{
	class WindowWin32 : public Window {
		friend class Window;
	public:
		WindowWin32(const WindowProperties& props);
		virtual ~WindowWin32() = default;

		virtual void SetTitle(const string& newTitle) override;
		virtual void SetPosition(const vec2i& pos) override;
		virtual void SetSize(const vec2u& size) override;
		virtual void SetWantsToClose(bool close) override;

		virtual optional<void*> GetPlatformHandle() { return { &handle }; }

	protected:
		LRESULT CALLBACK MessageHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
		void WindowPaint(HWND handle);

	private:
		HWND handle;
	};
}

#endif //CRUX_WIN32