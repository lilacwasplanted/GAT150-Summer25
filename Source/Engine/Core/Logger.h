#pragma once
#include <string>
#include <iostream>
#include <format>

namespace viper {

	enum class LogLevel : uint8_t {
		None	= 0,
		Info	= 1 << 0,
		Warning = 1 << 1,
		Error	= 1 << 2,
		Debug	= 1 << 3,
		All = Info | Warning | Error | Debug
	};

	inline LogLevel operator | (LogLevel a, LogLevel b) {
		return static_cast<LogLevel>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
	}

	inline LogLevel operator & (LogLevel a, LogLevel b) {
		return static_cast<LogLevel>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
	}

	class Logger {
	public:
		static void SetEnabledLevels(LogLevel levels) {
			s_enabledLevels = levels;
		}

		static void Log(LogLevel level, const string& message) {

			if ((s_enabledLevels & level) == LogLevel::None) return;

			 string prefix;
			 string color;

			switch (level) {
			case LogLevel::Info:
				prefix = "[INFO] "; 
				color = "\033[35m"; // Magenta
				break;
			case LogLevel::Warning: 
				prefix = "[WARNING] ";
				color = "\033[33m"; // Yellow
				break;
			case LogLevel::Error:  
				prefix = "[ERROR] ";
				color = "\033[31m"; // Red
				break;
			case LogLevel::Debug:  
				prefix = "[DEBUG] ";
				color = "\033[36m"; // Cyan
				break;
			default:        
				prefix = "[UNKNOWN] "; 
				color = "\033[0m"; // Reset
				break;
			}

			
			const string reset = "\033[0m";
			 string output = color + prefix + message + reset + "\n";

			 cerr << output;
		}

		template<typename... Args>
		static void Info( format_string<Args...> fmt, Args&&... args) {
			Log(LogLevel::Info, format(fmt, forward<Args>(args)...));
		}

		template<typename... Args>
		static void Error( format_string<Args...> fmt, Args&&... args) {
			Log(LogLevel::Error, format(fmt, forward<Args>(args)...));
		}

		template<typename... Args>
		static void Warning( format_string<Args...> fmt, Args&&... args) {
			Log(LogLevel::Warning, format(fmt, forward<Args>(args)...));
		}

		template<typename... Args>
		static void Debug( format_string<Args...> fmt, Args&&... args) {
			Log(LogLevel::Debug, format(fmt, forward<Args>(args)...));
		}

	private:
		inline static LogLevel s_enabledLevels = LogLevel::All;
	};
}
