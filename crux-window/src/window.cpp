#include "window.h"

#include <crux-common/platform.h>

#if CRUX_WIN32
#include "window.win32.h"
#endif

namespace crux {
	const vec2i WindowProperties::POSITION_UNDEFINED_VEC = vec2i{
		WindowProperties::POSITION_UNDEFINED, 
		WindowProperties::POSITION_UNDEFINED 
	};

	optional<WinPtr> Window::Create(const WindowProperties& props) {
#if CRUX_WIN32
		return {
			std::make_shared<internal::win32::WindowWin32>(props)
		};
#endif
		
		return {};
	}

	Window::Window(const WindowProperties& props) {
		title = props.title;
		size = vec2u(props.width, props.height);
		position = vec2i(props.positionX, props.positionY);
	}

	WindowProperties Window::GetProperties() {
		WindowProperties props{
			title,
			size,
			position,
		};

		return props;
	}
}