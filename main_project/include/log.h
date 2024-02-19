#ifndef log0
#define log0 

#include <iostream>
#include "../include/date.h"
#include "../include/string.h"
#include "../include/fileDump.h"
#include<fstream>

using Type::String;

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


		Log(const String& name = "Logger" ) : m_LogLevel{LevelInfo}, m_name{name} {}
		Log(const String& name, Level l) : m_name{ name } , m_LogLevel{ l } {}
		Log(const String& name, Level l, const String& File ) : m_name{ name }, m_LogLevel{ l },m_fileName{(File)} { dumpInFile = true;}

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
		void log(const Level& l, const String& msg, Args ...args);

		bool dumpInFile = false;

	private:
		String m_name;
		Level m_LogLevel;
		short int count;
		String m_buffer = "";
		String m_fileName = "log.txt";
		
		Utility::Date date{ 12 , 31 ,20004 , mdy };

		String stringLevel(const Level& l) {
			switch (l) {
		    case LevelCritical:
			return "[ CRITICAL ]";
			case LevelWarning:
				return "[ WARNING ]";
			case LevelError :
				return "[ ERROR ]";
			case LevelInfo :
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
		void Debug(const String& message, Args ...args); 
		template <typename ...Args >
		void Info(const String& message, Args ...args);
		template <typename ...Args >
		void Error(const String& message, Args ...args);
		template <typename ...Args >
		void Warn(const String& message, Args ...args);
		template <typename ...Args >
		void Critical(const String& message, Args ...args);
	};
	template <typename ...Args>
	void Log::Critical(const String& message, Args ...args)
	{
		log(Log::LevelCritical, message, args...);

	}
	template <typename ...Args >
	void Log::Warn(const String& message, Args ...args)
	{
		log(LevelWarning, message, args...);
	}

	template <typename ...Args>
	void Log::Error(const String& message, Args ...args)
	{
		log(Log::LevelError, message, args...);
	}

	template <typename ...Args>
	void Log::Info(const String& message, Args ...args)
	{
		log(Log::LevelInfo, message, args...);

	}
	template <typename ...Args>
	void Log::Debug(const String& message, Args ...args)
	{
		log(Log::LevelDebug, message, args...);

	}

}

#endif 