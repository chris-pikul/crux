#pragma once

#include <atomic>

#include <crux-common/types.h>
#include <crux-common/optional.h>

namespace crux {
	/**
	 * @brief A platform-independant "window" abstract interface.
	 * 
	 * The platform-specific implementations are based off of this abstract interface.
	 * For general usage, this should be the symbol you use, only casting to the
	 * underlying implementation if absolutely needed.
	*/
	class Window;

	/**
	 * @brief Smart-pointer for a window.
	 * 
	 * Type-alias of std::shared_ptr wrapping a Window object
	*/
	typedef std::shared_ptr<Window> WinPtr;

	/**
	 * @brief Basic properties of a window.
	 * 
	 * These properties are held separately from the main class body for
	 * ease of serialization and passing as parameter objects.
	*/
	struct WindowProperties {
		/**
		 * @brief Constant expression for when a position is undefined.
		 * In this case, the window will be centered along this axis
		 * if the WindowProperties::positionCentered flag is true.
		 * If that flag is false, then the OS will decide.
		*/
		static const int POSITION_UNDEFINED = -1;

		// Vector 2D of integers, both of which are POSITION_UNDEFINED
		static const vec2i POSITION_UNDEFINED_VEC;

		// Given std::string title for the window, shown in the platform UI.
		std::string title = "Unknown";

		// The width (X axis), in pixels, of the given window
		uint width = 0;

		// The height (Y axis), in pixels, of the given window
		uint height = 0;

		// The position on the horizontal X-axis, in screen pixels, 
		// of the given window.
		// If the value is negative, it is treated as un-important and a 
		// OS decision.
		int positionX = POSITION_UNDEFINED;

		// The position on the vertical Y-axis, in screen pixels, 
		// of the given window.
		// If the value is negative, it is treated as un-important and a 
		// OS decision.
		int positionY = POSITION_UNDEFINED;

		// An optional boolean that is used when one of the positional
		// properties is negative, to indicate automatic centering on the screen.
		bool positionCentered = true;

		WindowProperties() = default;

		/**
		 * @brief Construct a new WindowProperties object.
		 * @param title		The title of the window
		 * @param w			The width of the window in pixels.
		 * @param h			The height of the window in pixels.
		 * @param x			The position on the X-axis of the window, or undefined if -1 (POSITION_UNDEFINED)
		 * @param y			The position on the Y-axis of the window, or undefined if -1 (POSITION_UNDEFINED)
		 * @param centered  If true, the positions will be center-screen if they are negative (POSITION_UNDEFINED)
		*/
		WindowProperties(const std::string& title, uint w, uint h, int x= POSITION_UNDEFINED, int y= POSITION_UNDEFINED, bool centered=true)
			: title(title), width(w), height(h), positionX(x), positionY(y), positionCentered(centered) { }

		/**
		 * @brief Construct a new WindowProperties object.
		 * @param title		The title of the window
		 * @param size		The size of the window, as a vector-2D.
		 * @param position  The position of the window, as a vector-2D. Defaults to undefined (meaning either centered, or OS-specified).
		 * @param centered  If true, the positions will be center-screen if they are negative (POSITION_UNDEFINED)
		*/
		WindowProperties(const std::string& title, const vec2u& size, const vec2i& position = POSITION_UNDEFINED_VEC, bool centered=true)
			: title(title), width(size.x), height(size.y), positionX(position.x), positionY(position.y), positionCentered(centered) { }

		// @return The size as a Vector-2D of unsigned-integers
		vec2u GetSize() { return vec2u(width, height); }

		// @return The position of the window as a Vector-2D of integers
		vec2i GetPosition() { return vec2i(positionX, positionY); }
	};

	/**
	 * @brief A platform-independant "window" abstract interface.
	 *
	 * The platform-specific implementations are based off of this abstract interface.
	 * For general usage, this should be the symbol you use, only casting to the
	 * underlying implementation if absolutely needed.
	*/
	class Window {
	public:
		/**
		 * @brief Factory function to create a new Window
		 * 
		 * This static function is the prefered way of creating a new window
		 * so that platform-specific checks can be made. Additionally, by
		 * using this factory the returned optional can help eleviate
		 * error checking issues.
		 * 
		 * @param[in] props The properties of the window to set for creation
		 * @return A crux::optional object resulting in a WinPtr object if successfully created
		*/
		static crux::optional<WinPtr> Create(const WindowProperties& props);
	
		Window(const Window&) = delete; //copy ctor
		Window& operator=(const Window&) = delete; //assignment

		/**
		 * @brief Returns the current title of the Window.
		 * @return The Window title as a string
		*/
		inline std::string GetTitle() const { return title; }

		/**
		 * @brief Set's the Window's title.
		 * This additionally sets the the OS's version for UI display.
		 * NOTE: This is implemented by the platform-specific classes.
		 * @param newTitle The new string value for the title
		*/
		virtual void SetTitle(const std::string& newTitle) = 0;

		/**
		 * @brief Set's the Window's title.
		 * This additionally sets the the OS's version for UI display.
		 * NOTE: This is implemented by the platform-specific classes.
		 * @param newTitle The new string value for the title
		*/
		virtual void SetTitle(const char* newTitle) {
			SetTitle(string(newTitle));
		}

		/**
		 * @brief Returns the current position in pixels, on-screen,
		 * of the Window.
		 * @return Vector 2D (signed) of the screen position
		*/
		inline const vec2i& GetPosition() const { return position; }

		/**
		 * @brief Returns the current horizontal (X axis) position 
		 * in pixels, on-screen, of the Window.
		 * @return Integer of the horizontal screen position
		*/
		inline int GetPositionX() const { return position.x; }

		/**
		 * @brief Returns the current vertical (Y axis) position
		 * in pixels, on-screen, of the Window.
		 * @return Integer of the vertical screen position
		*/
		inline int GetPositionY() const { return position.y; }

		// Set the window position, using a vector-2D of integers
		virtual void SetPosition(const vec2i& pos) = 0;

		// Set the window position, using a vector-2D of unsigned-integers
		virtual void SetPosition(const vec2u& pos) { SetPosition(vec2i(pos.x, pos.y)); }

		// Set the window position, using integers
		virtual void SetPosition(int x, int y) { SetPosition(vec2i(x,y)); }

		// Set the window position, using unsigned integers
		virtual void SetPosition(uint x, uint y) { SetPosition(vec2i(x, y)); }

		// Set the window horizontal (X-axis) position, using an integer
		virtual void SetPositionX(int x) { SetPosition(vec2i(x, position.y)); }

		// Set the window horizontal (X-axis) position, using an unsigned-integer
		virtual void SetPositionX(uint x) { SetPosition(vec2i(x, position.y)); }

		// Set the window vertical (Y-axis) position, using an integer
		virtual void SetPositionY(int y) { SetPosition(vec2i(position.x, y)); }

		// Set the window vertical (Y-axis) position, using an unsigned-integer
		virtual void SetPositionY(uint y) { SetPosition(vec2i(position.x, y)); }

		/**
		 * @brief Returns the size of the Window, in screen pixels.
		 * @return Vector 2D of unsigned-integers
		*/
		inline const vec2u& GetSize() const { return size; }

		/**
		 * @brief Returns the horizontal (X axis) size of the Window, in screen pixels.
		 * @return Unsigned-integer of the width
		*/
		inline uint GetWidth() const { return size.x; }

		/**
		 * @brief Returns the vertical (Y axis) size of the Window, in screen pixels.
		 * @return Unsigned-integer of the height
		*/
		inline uint GetHeight() const { return size.y; }

		// Set the window size, using a vector-2D of unsigned-integers
		virtual void SetSize(const vec2u& pos) = 0;

		// Set the window size, using integers
		virtual void SetSize(int x, int y) { SetSize(vec2u(x, y)); }

		// Set the window size, using unsigned-integers
		virtual void SetSize(uint x, uint y) { SetSize(vec2u(x, y)); }
		
		// Set the window width (X-axis), using an integer
		virtual void SetWidth(int x) { SetSize(vec2u(x, size.y)); }

		// Set the window width (X-axis), using an unsigned-integer
		virtual void SetWidth(uint x) { SetSize(vec2u(x, size.y)); }

		// Set the window height (Y-axis), using an integer
		virtual void SetHeight(int y) { SetSize(vec2u(size.x, y)); }

		// Set the window height (Y-axis), using an unsigned-integer
		virtual void SetHeight(uint y) { SetSize(vec2u(size.x, y)); }

		/**
		 * @brief Gets the windows properties and fills a WindowProperties object 
		 * with the values as the Window currently stands.
		 * @return WindowProperties struct containing info about the Window.
		*/
		virtual WindowProperties GetProperties();

		/**
		 * @brief Checks if the OS window wants to close the Window.
		 * For most application, this marks the end of the application lifecycle
		 * and cleanup should be performed.
		 * NOTE: This is atomic under the hood.
		 * @return True, if the OS reports a window wanting to close
		*/
		inline bool WantsToClose() const { return wantsToClose; }

		/**
		 * @brief Sets the internal variable for a window wanting to close.
		 * This should not be used to clear the flag in most applications, 
		 * it is provided here mostly to simulate the closing event by
		 * some other means. Ex. Clicking a UI button for "Quit".
		 * NOTE: This is atomic under the hood.
		 * @param close The new boolean value for if the window should close.
		*/
		virtual void SetWantsToClose(bool close) { wantsToClose = close; }

		/**
		 * @brief Returns an optional void-pointer value of the underlying
		 * platform-specific OS handle of the window.
		 * - Win32: This is the native HWND value.
		 * @return An optional resulting in a void-pointer if a platform handle exists
		*/
		virtual crux::optional<void*> GetPlatformHandle() { return {}; }
		
	protected:
		Window(const WindowProperties& props);
		virtual ~Window() = default;

	private:
		// Current title of the window
		std::string title;

		// The position of the window, on screen.
		vec2i position;

		// The size of the window, in screen pixels.
		vec2u size;

		// Does the window want to close?
		std::atomic_bool wantsToClose;
	};
}