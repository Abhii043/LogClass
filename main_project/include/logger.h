#ifndef logger
#define logger 

#include"../include/log.h"
#include"../include/fileDump.h"
#include<iostream>

using systemLog::Log;

namespace systemLog
{
	auto myLogger = std::make_shared<Log>("Abhi");

	std::shared_ptr<Log> defaultLogger() {
		return myLogger ;
	}

	void setLogger(std::shared_ptr<Log> pointer) {
		myLogger = pointer;
	}

	template <typename ...Args>
	void Log::log(const Level& l, const String& msg, Args ...args) {
		if (l >= m_LogLevel)
		{
			std::cout << date.getStrDate() << " " << "[ " << defaultLogger()->m_name << " ]" << " " << stringLevel(l) << " : " << msg << " ";
			Print(args...);
		}
		if (dumpInFile)
		{
			count++;
			m_buffer.append(date.getStrDate()).append(" ").append( "[ ").append( defaultLogger()->m_name).append(" ]").append(" ").append(stringLevel(l)).append(" : ").append(msg).append(" ") ;
			bufferAppend(args...);
			if(count >= 5){
				fileDump f;
				f.flush1(m_buffer);
				m_buffer = "";
				count = 0;
			}
			
		}
		

	}

	template <typename ...Args >
	void Warn(const String& message, Args ...args)
	{
		defaultLogger()->log(Log::LevelWarning, message, args...);
	}

	template <typename ...Args>
	void Error(const String& message, Args ...args)
	{
		defaultLogger()->log(Log::LevelError, message, args...);
	}

	template <typename ...Args>
	void Info(const String& message, Args ...args)
	{
		defaultLogger()->log(Log::LevelInfo, message, args...);

	}
	template <typename ...Args>
	void Critical(const String& message, Args ...args)
	{
		defaultLogger()->log(Log::LevelCritical, message, args...);

	}
	template <typename ...Args>
	void Debug(const String& message, Args ...args)
	{
		defaultLogger()->log(Log::LevelDebug, message, args...);

	}
}

#endif 
