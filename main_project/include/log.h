#ifndef log0
#define log0 

#include <iostream>
#include<string>
#include "../include/fileDump.h"
#include<fstream>
#include<chrono>

namespace systemLog {

	class Log
	{
	public:
		enum  Level
		{
			LevelDebug,
			LevelInfo,
			LevelWarning,
			LevelError,
			LevelCritical
		};


		Log(const std::string& name = "Logger" ) : m_LogLevel{LevelInfo}, m_name{name} {}
		Log(const std::string& name, Level l) : m_name{ name } , m_LogLevel{ l } {}
		Log(const std::string& name, Level l, const std::string& File ) : m_name{ name }, m_LogLevel{ l },m_fileName{(File)} { dumpInFile = true;}

		~Log() {
			if (dumpInFile && count < 5) {
				fileDump f(m_fileName);
				f.flush1(m_buffer);
				m_buffer = "";
				count = 0;
			}
		}
		void setLogLevel(const Level& level)
		{
			m_LogLevel = level;
		}

		Level getLogLevel() {
			return m_LogLevel;
		}

		template <typename ...Args >
		void log(const Level& l, const std::string& msg, Args ...args);

		bool dumpInFile = false;

	private:
		std::string m_name;
		Level m_LogLevel;
		short int count{0};
		std::string m_buffer = "";
		std::string m_fileName = "log.txt";

		std::string localTime() {
			auto now = std::chrono::system_clock::now();
			std::time_t time = std::chrono::system_clock::to_time_t(now);

			std::tm tmLocal;
			localtime_s(&tmLocal, &time);

			char buffer[20];
			std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &tmLocal);

			return std::string(buffer);
		}

		const std::string red { "\033[0;31m" };
		const std::string darkRed{ "\033[1;31m" };
		const std::string yellow{ "\033[1;33m" };
		const std::string cyan{ "\033[0;36m" };
		const std::string magenta{ "\033[0;35m" };
		const std::string reset{ "\033[0m" };

		std::string stringLevel(const Level& l) {
			switch (l) {
		    case LevelCritical:
			return  red + "[ CRITICAL ]" + reset;
			case LevelWarning:
				return darkRed + "[ WARNING ]" + reset;
			case LevelError :
				return yellow + "[ ERROR ]" + reset;
			case LevelInfo :
				return cyan + "[ INFO ]" + reset;
			case LevelDebug:
				return magenta + "[ DEBUG ]" + reset;
			}
			return "";
		}
		std::string stringFLevel(const Level& l) {
			switch (l) {
			case LevelCritical:
				return  "[ CRITICAL ]";
			case LevelWarning:
				return "[ WARNING ]";
			case LevelError:
				return "[ ERROR ]";
			case LevelInfo:
				return "[ INFO ]";
			case LevelDebug:
				return "[ DEBUG ]";
			}
			return "";
		}

		void Print() { std::cout << '\n'; };

		template<typename T, typename ...Args>
		void Print(T value, Args ...args) {
			std::cout << value << " ";
			Print(args...);
		}

		void bufferAppend() { m_buffer.append("\n"); }
		template<typename T, typename ...Args>
		void bufferAppend(T value , Args ...args) {
			m_buffer.append(value).append(" ");
			bufferAppend(args...);
		}
	public:
		template <typename ...Args >
		void Debug(const std::string& message, Args ...args);
		template <typename ...Args >
		void Info(const std::string& message, Args ...args);
		template <typename ...Args >
		void Error(const std::string& message, Args ...args);
		template <typename ...Args >
		void Warn(const std::string& message, Args ...args);
		template <typename ...Args >
		void Critical(const std::string& message, Args ...args);
	};
	template <typename ...Args>
	void Log::Critical(const std::string& message, Args ...args)
	{
		log(Log::LevelCritical, message, args...);

	}
	template <typename ...Args >
	void Log::Warn(const std::string& message, Args ...args)
	{
		log(LevelWarning, message, args...);
	}

	template <typename ...Args>
	void Log::Error(const std::string& message, Args ...args)
	{
		log(Log::LevelError, message, args...);
	}

	template <typename ...Args>
	void Log::Info(const std::string& message, Args ...args)
	{
		log(Log::LevelInfo, message, args...);

	}
	template <typename ...Args>
	void Log::Debug(const std::string& message, Args ...args)
	{
		log(Log::LevelDebug, message, args...);

	}

}

#endif 