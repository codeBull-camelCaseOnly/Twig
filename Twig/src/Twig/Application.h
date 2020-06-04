#pragma once
#include"Core.h"
#include"Window.h"
#include "Twig/Events/ApplicationEvent.h"

namespace Twig {

	class TWIG_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void onEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application* CreateApplication();
}

