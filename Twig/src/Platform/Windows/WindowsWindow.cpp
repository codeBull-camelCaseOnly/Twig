#include "twigpch.h"
#include "WindowsWindow.h"

#include "Twig/Events/ApplicationEvent.h"
#include "Twig/Events/KeyEvent.h"
#include "Twig/Events/MouseEvent.h"

#include<glad/glad.h>

namespace Twig {
	
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* desc)
	{
		TWIG_CORE_ERROR("GLFW ERROR ({0}) : {1}", error, desc);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		TWIG_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			TWIG_CORE_ASSERT(success, "Could not intialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TWIG_CORE_ASSERT(status, "FAILED TO INITIALIZE GLAD");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//Set GLFW Callbacks

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) 
			{
				WindowData m_Data = *(WindowData*)glfwGetWindowUserPointer(window);
				m_Data.Width = width;
				m_Data.Height = height;

				WindowResizeEvent event(width, height);
				m_Data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) 
			{
				WindowData m_Data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;

				m_Data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
			{
				WindowData m_Data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				switch(action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						m_Data.EventCallback(event);
						break;
					}	
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						m_Data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						m_Data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) 
			{
				WindowData m_Data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch(action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						m_Data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						m_Data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) 
			{
				WindowData m_Data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				m_Data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) 
			{
				WindowData m_Data = *(WindowData*)glfwGetWindowUserPointer(window);
	
				MouseMovedEvent event((float)xPos, (float)yPos);
				m_Data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}
