#pragma once
#include"Application.h"

#ifdef TWIG_PLATFORM_WINDOWS

extern Twig::Application* Twig::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Twig::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif