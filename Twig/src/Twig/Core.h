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

#ifdef TWIG_ENABLE_ASSERTS
	#define TWIG_ASSERT(x, ...) { if(!(x)) { TWIG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define TWIG_CORE_ASSERT(x, ...) { if(!(x)) { TWIG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define TWIG_ASSERT(x, ...)
	#define TWIG_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)