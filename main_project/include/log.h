#include <iostream>
#include "../include/date.h"
#include "../include/string.h"

#ifndef log0
#define log0 

using Type::String;

namespace systemLog {

	class Log
	{

	public:
		enum class Level
		{
			LevelError = 10,
			LevelWarning,
			LevelInfo
		};

		Log() {
			m_LogLevel = Level::LevelInfo;
		}

		Log(Level l) {
			m_LogLevel = Level::LevelInfo;
		}

		void setLogLevel(const Level& level)
		{
			m_LogLevel = level;
		}

		Level getLogLevel() {
			return m_LogLevel;
		}


		template <typename ...Args >
		void Warn(const String& message, Args ...args)
		{
			if (m_LogLevel >= Level::LevelWarning)
				std::cout << date.getStrDate() << " " << "[Warning]: " << message << " ";
			Print(args...);
		}

		template <typename ...Args>
		void Error(const String& message, Args ...args)
		{
			if (m_LogLevel >= Level::LevelError)
				std::cout << date.getStrDate() << " " << "[Error]: " << message << " ";
			Print(args...);
		}

		template <typename ...Args>
		void Info(const String& message, Args ...args)
		{
			if (m_LogLevel >= Level::LevelInfo)
				std::cout << date.getStrDate() << " " << "[Info]: " << message << " ";
			Print(args...);
		}

	private:
		Level m_LogLevel;

		Utility::Date date{ 31,01,2024 };

		void Print() { std::cout << '\n'; };

		template<typename T, typename ...Args>
		void Print(T value, Args ...args) {
			std::cout << value << std::endl;
			Print(args...);
		}
	};
}

#endif 