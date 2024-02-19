#include <iostream>
#include "./include/log.h"
#include "./include/date.h"
#include "./include/string.h"
#include "./include/Exception.h"
#include"./include/logger.h"

using systemLog::Log;
using Utility::Date;
using Type::String;
using Exception::myException;


int main()
{
	std::shared_ptr<Log> logger1 = std::make_shared<Log>( "Abhiiiiiii" , Log::LevelDebug ) ;
	systemLog::setLogger(logger1) ;

	logger1->dumpInFile = true;

	systemLog::Debug("Debug", "Debugging");
	systemLog::Info("Info" , "Information is useful");
	systemLog::Warn("warn" , "Warningggg");
	systemLog::Error("error" , "Erroringgg");
	systemLog::Critical("Critical", "it is very Critical");

}
