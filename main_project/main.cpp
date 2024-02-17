#include <iostream>
#include "./include/log.h"
#include "./include/date.h"
#include "./include/string.h"
#include "./include/Exception.h"

using systemLog::Log;
using Utility::Date;
using Type::String;
using Exception::myException;


int main()
{
	Log log;
	log.setLogLevel(Log::Level::LevelInfo);

	log.Info("Info" , 2);
	log.Warn("warn" , "Abhi");
	log.Error("error" , 'A');

}
