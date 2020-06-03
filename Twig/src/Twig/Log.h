#pragma once

#include"Core.h"
#include"spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Twig {

	class TWIG_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> m_CoreLogger;
		static std::shared_ptr<spdlog::logger> m_ClientLogger;
	};

}

//Core Log Macros
#define TWIG_CORE_TRACE(...)	::Twig::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TWIG_CORE_INFO(...)		::Twig::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TWIG_CORE_WARN(...)		::Twig::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TWIG_CORE_ERROR(...)	::Twig::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TWIG_CORE_FATAL(...)	::Twig::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log Macros
#define TWIG_TRACE(...)			::Twig::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TWIG_INFO(...)			::Twig::Log::GetClientLogger()->info(__VA_ARGS__)
#define TWIG_WARN(...)			::Twig::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TWIG_ERROR(...)			::Twig::Log::GetClientLogger()->error(__VA_ARGS__)
#define TWIG_FATAL(...)			::Twig::Log::GetClientLogger()->fatal(__VA_ARGS__)
