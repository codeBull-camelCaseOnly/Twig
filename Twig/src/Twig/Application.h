#pragma once
#include"Core.h"

namespace Twig {

	class TWIG_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}

