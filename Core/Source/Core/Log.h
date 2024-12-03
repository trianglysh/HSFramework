#pragma once

#include "Core/Base.h"
#include "Core/Misc/MessageDialog.h"

#define SPDLOG_LEVEL_NAMES { "trace", "debug", "info", "warn", "error", "fatal", "off" }
#define SPDLOG_SHORT_LEVEL_NAMES { "T", "D", "I", "W", "E", "F", "O" }

#define SPDLOG_FMT_EXTERNAL
#define FMT_HEADER_ONLY

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> // For ostream<< formatting
#pragma warning(pop)

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/glm.hpp>

namespace HSFramework
{
	class Log
	{
	public:
		static void Init();
		static void Shutdown();

		template <typename... Args>
		static void RtDialog(spdlog::logger& logger, bool isFatal, std::string_view fmt, Args&&... args)
		{
			std::string message = fmt::vformat(fmt, fmt::make_format_args(args...));
			if (isFatal)
			{
				message += "\n\nThe application will be aborted due to that.";
			}
			Scope<MessageDialog> dialog = MessageDialog::New(isFatal ? "Fatal error!" : "Runtime error!", message, DialogControls::Ok, DialogIcon::Error);
			dialog->Create();
		}

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetRuntimeLogger() { return s_RuntimeLogger; }
		static std::shared_ptr<spdlog::logger>& GetEditorLogger() { return s_EditorLogger; }
	private:
		inline static std::shared_ptr<spdlog::logger> s_CoreLogger;
		inline static std::shared_ptr<spdlog::logger> s_RuntimeLogger;
		inline static std::shared_ptr<spdlog::logger> s_EditorLogger;
	};
}

template <typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& stream, const glm::vec<L, T, Q>& vector)
{
	return stream << glm::to_string(vector);
}

template <typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& stream, const glm::mat<C, R, T, Q>& matrix)
{
	return stream << glm::to_string(matrix);
}

template <typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& stream, const glm::qua<T, Q>& quaternion)
{
	return stream << glm::to_string(vector);
}

#define HS_LOGGER_TRACE(logger, ...) { ::HSFramework::Log::Get##logger##Logger()->trace(__VA_ARGS__); }
#define HS_LOGGER_INFO(logger, ...)  { ::HSFramework::Log::Get##logger##Logger()->info(__VA_ARGS__); }
#define HS_LOGGER_WARN(logger, ...)  { ::HSFramework::Log::Get##logger##Logger()->warn(__VA_ARGS__); }

#ifndef HS_SHIPPING
	#define HS_LOGGER_ERROR(logger, ...) { ::HSFramework::Log::Get##logger##Logger()->error(__VA_ARGS__); }
	#define HS_LOGGER_FATAL(logger, ...) { ::HSFramework::Log::Get##logger##Logger()->critical(__VA_ARGS__); ::std::exit(1); }
#else
	#define HS_LOGGER_ERROR(logger, ...) { ::HSFramework::Log::Get##logger##Logger()->error(__VA_ARGS__); ::HSFramework::Log::RtDialog(*::HSFramework::Log::Get##logger##Logger(), false, __VA_ARGS__); }
	#define HS_LOGGER_FATAL(logger, ...) { ::HSFramework::Log::Get##logger##Logger()->critical(__VA_ARGS__); ::HSFramework::Log::RtDialog(*::HSFramework::Log::Get##logger##Logger(), true, __VA_ARGS__); ::std::exit(1); }
#endif

#define HS_CORE_TRACE(...)    HS_LOGGER_TRACE(Core, __VA_ARGS__)
#define HS_CORE_INFO(...)     HS_LOGGER_INFO(Core, __VA_ARGS__)
#define HS_CORE_WARN(...)     HS_LOGGER_WARN(Core, __VA_ARGS__)
#define HS_CORE_ERROR(...)    HS_LOGGER_ERROR(Core, __VA_ARGS__)
#define HS_CORE_FATAL(...)    HS_LOGGER_FATAL(Core, __VA_ARGS__)

#define HS_RUNTIME_TRACE(...) HS_LOGGER_TRACE(Runtime, __VA_ARGS__)
#define HS_RUNTIME_INFO(...)  HS_LOGGER_INFO(Runtime, __VA_ARGS__)
#define HS_RUNTIME_WARN(...)  HS_LOGGER_WARN(Runtime, __VA_ARGS__)
#define HS_RUNTIME_ERROR(...) HS_LOGGER_ERROR(Runtime, __VA_ARGS__)
#define HS_RUNTIME_FATAL(...) HS_LOGGER_FATAL(Runtime, __VA_ARGS__)

#define HS_EDITOR_TRACE(...)  HS_LOGGER_TRACE(Editor, __VA_ARGS__)
#define HS_EDITOR_INFO(...)   HS_LOGGER_INFO(Editor, __VA_ARGS__)
#define HS_EDITOR_WARN(...)   HS_LOGGER_WARN(Editor, __VA_ARGS__)
#define HS_EDITOR_ERROR(...)  HS_LOGGER_ERROR(Editor, __VA_ARGS__)
#define HS_EDITOR_FATAL(...)  HS_LOGGER_FATAL(Editor, __VA_ARGS__)
