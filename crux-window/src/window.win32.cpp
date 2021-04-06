#if CRUX_WIN32
#include "window.win32.h"

#include <crux-common/platform.win32.h>

namespace crux::internal::win32 {
	WindowWin32::WindowWin32(const WindowProperties& props) : Window(props) {
		handle = nullptr;
	}

	void WindowWin32::SetTitle(const string& newTitle) {

	}

	void WindowWin32::SetPosition(const vec2i& newPos) {

	}

	void WindowWin32::SetSize(const vec2u& newSize) {

	}

	void WindowWin32::SetWantsToClose(bool close) {

	}


}

#endif