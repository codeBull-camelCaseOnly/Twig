#pragma once

#ifdef TWIG_PLATFORM_WINDOWS
	#ifdef TWIG_BUILD_DLL
		#define TWIG_API __declspec(dllexport)
	#else
		#define TWIG_API __declspec(dllimport)
	#endif
#else
	#error TWIG SUPPORTS WINDOWS ONLY
#endif

#define BIT(x) (1 << x)