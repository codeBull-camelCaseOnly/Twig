#include "twigpch.h"
#include "Application.h"

#include"Twig/Events/Event.h"
#include "Twig/Events/ApplicationEvent.h"
#include "Twig/Log.h"

namespace Twig {
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(800, 600);
		if (e.IsInCategory(EventCategoryApplication))
			TWIG_TRACE(e);
		while (1);
	}
}