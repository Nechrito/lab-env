#pragma once
//------------------------------------------------------------------------------
/**
	Manages the opening and closing of a window.
	
	(C) 2015-2018 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <nanovg.h>
#include <string>

namespace Display
{
	class Window
	{
	public:
		/// constructor
		Window();
		/// destructor
		~Window();
	
		/// set size of window
		void SetSize(int32 width, int32 height);
		/// get size of windows
		void GetSize(int32 & width, int32 & height) const;
		float GetHeight() const;
		float GetWidth() const;
		/// set title of window
		void SetTitle(const std::string& title);
	
		/// open window
		bool Open();
		/// close window
		void Close();
		/// returns true if window is open
		bool IsOpen() const;
	
		/// make this window current, meaning all draws will direct to this window context
		void MakeCurrent() const;
	
		/// update a tick
		void Update();
		/// swap buffers at end of frame
		void SwapBuffers();

		/// sets the position of the cursor
		void SetCursorPosition(double x, double  y) const;

		/// toggles the cursor from being visible
		void HideCursor(bool value) const;
	
		/// set key press function callback
		void SetKeyPressFunction(const std::function<void(int32, int32, int32, int32)>& func);
		/// set mouse press function callback
		void SetMousePressFunction(const std::function<void(int32, int32, int32)>& func);
		/// set mouse move function callback
		void SetMouseMoveFunction(const std::function<void(float64, float64)>& func);
		/// set mouse enter leave function callback
		void SetMouseEnterLeaveFunction(const std::function<void(bool)>& func);
		/// set mouse scroll function callback
		void SetMouseScrollFunction(const std::function<void(float64, float64)>& func);
	
		/// set optional UI render function
		void SetUiRender(const std::function<void()>& func);
		
		/// set optional nanovg render function
		void SetNanoVGRender(const std::function<void(NVGcontext *)> & func);
	
	private:
	
		/// static key press callback
		static void StaticKeyPressCallback(GLFWwindow* win, int32 key, int32 scancode, int32 action, int32 mods);
		/// static mouse press callback
		static void StaticMousePressCallback(GLFWwindow* win, int32 button, int32 action, int32 mods);
		/// static mouse move callback
		static void StaticMouseMoveCallback(GLFWwindow* win, float64 x, float64 y);
		/// static mouse enter/leave callback
		static void StaticMouseEnterLeaveCallback(GLFWwindow* win, int32 mode);
		/// static mouse scroll callback
		static void StaticMouseScrollCallback(GLFWwindow* win, float64 x, float64 y);
	
		/// resize update
		void Resize() const;
		
		/// title rename update
		void Retitle() const; 
	
		static int32 WindowCount;
	
		/// function for key press callbacks
		std::function<void(int32, int32, int32, int32)> keyPressCallback;
		/// function for mouse press callbacks
		std::function<void(int32, int32, int32)> mousePressCallback;
		/// function for mouse move callbacks
		std::function<void(float64, float64)> mouseMoveCallback;
		/// function for mouse enter/leave callbacks
		std::function<void(bool)> mouseLeaveEnterCallback;
		/// function for mouse scroll callbacks
		std::function<void(float64, float64)> mouseScrollCallback;
		/// function for ui rendering callback
		std::function<void()> uiFunc;
		/// function for nanovg rendering callback
		std::function<void(NVGcontext *)> nanoFunc;
	
	
		int32 width;
		int32 height;
		std::string title;
		GLFWwindow* window;
		NVGcontext * vg;
	};
	
	inline void Window::SetSize(int32 width, int32 height)
	{
		this->width = width;
		this->height = height;
		if (nullptr != this->window) 
			this->Resize();
	}
	
	inline void Window::GetSize(int32 & width, int32 & height) const
	{
		width = this->width;
		height = this->height;
	}
	
	inline float Window::GetHeight() const { return this->height; }
	inline float Window::GetWidth() const { return this->width; }
	
	inline void Window::SetTitle(const std::string& title)
	{
		this->title = title;
		if (nullptr != this->window) 
			this->Retitle();
	}
	
	inline bool Window::IsOpen() const
	{
		return nullptr != this->window;
	}
	
	inline void Window::SetKeyPressFunction(const std::function<void(int32, int32, int32, int32)>& func)
	{
		this->keyPressCallback = func;
	}
	
	inline void Window::SetMousePressFunction(const std::function<void(int32, int32, int32)>& func)
	{
		this->mousePressCallback = func;
	}
	
	inline void Window::SetMouseMoveFunction(const std::function<void(float64, float64)>& func)
	{
		this->mouseMoveCallback = func;
	}
	
	inline void Window::SetMouseEnterLeaveFunction(const std::function<void(bool)>& func)
	{
		this->mouseLeaveEnterCallback = func;
	}
	
	inline void Window::SetMouseScrollFunction(const std::function<void(float64, float64)>& func)
	{
		this->mouseScrollCallback = func;
	}
	
	inline void Window::SetUiRender(const std::function<void()>& func)
	{
		this->uiFunc = func;
	}
	
	inline void Window::SetNanoVGRender(const std::function<void(NVGcontext *)> & func)
	{
		this->nanoFunc = func;
	}
} 
