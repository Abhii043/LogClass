#ifndef _dump_
#define _dump_

#include<iostream>
#include<fstream>
#include"../include/string.h"

namespace systemLog {
	class fileDump {
	private:
		std::ofstream writeFile{};
	public:
		fileDump() : writeFile{ "log.txt" , std::ios::app } {}
		fileDump(const Type::String& fileName) : writeFile{ fileName.raw() , std::ios::app} {}
		~fileDump() = default;

		void flush1(const Type::String& buffer) {
			writeFile << buffer;
			writeFile.flush();
		}
	};
}

#endif