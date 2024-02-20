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
	void Log::log(const Level& l, const std::string& msg, Args ...args) {
		if (l >= m_LogLevel)
		{
			std::cout << " "<< localTime()<<" [ " << defaultLogger()->m_name << " ] "<< stringLevel(l) << " : " << msg << " ";
			Print(args...);
		}
		if (dumpInFile)
		{
			count++;
			m_buffer.append(localTime()).append(" [ ").append(defaultLogger()->m_name).append(" ] ").append(stringFLevel(l)).append(" : ").append(msg).append(" ");
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
	void Warn(const std::string& message, Args ...args)
	{
		defaultLogger()->log(Log::LevelWarning, message, args...);
	}

	template <typename ...Args>
	void Error(const std::string& message, Args ...args)
	{
		defaultLogger()->log(Log::LevelError, message, args...);
	}

	template <typename ...Args>
	void Info(const std::string& message, Args ...args)
	{
		defaultLogger()->log(Log::LevelInfo, message, args...);

	}
	template <typename ...Args>
	void Critical(const std::string& message, Args ...args)
	{
		defaultLogger()->log(Log::LevelCritical, message, args...);

	}
	template <typename ...Args>
	void Debug(const std::string& message, Args ...args)
	{
		defaultLogger()->log(Log::LevelDebug, message, args...);

	}
}

#endif 
