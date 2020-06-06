#pragma once
#include"Core.h"
#include "LayerStack.h"
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

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& getWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;
		static Application* s_Instance;

	};

	Application* CreateApplication();
}

