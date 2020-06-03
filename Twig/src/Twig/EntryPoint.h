#pragma once
#include"Application.h"

#ifdef TWIG_PLATFORM_WINDOWS

extern Twig::Application* Twig::CreateApplication();

int main(int argc, char** argv)
{
	Twig::Log::Init();
	TWIG_CORE_ERROR("Initialized Log");
	TWIG_WARN("Initialized Log");

	auto app = Twig::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif