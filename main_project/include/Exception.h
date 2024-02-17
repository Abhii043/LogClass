#ifndef Exception00
#define Exception00

#include "../include/string.h"

using Type::String;

namespace Exception {

	class myException {
	private:
		String m_Message;
	public:
		myException() : m_Message{ "Something went wrong" } {}

		myException(const String& msg) : m_Message{ msg } {}

		virtual String getMessage() {
			return m_Message;
		}
	};
	class InvalidDate : public myException {
	private:
		String m_Message;
	public:
		InvalidDate() : m_Message{ "Invalid Date Input\n" } {}

		InvalidDate(const String& msg) : m_Message{ msg } {}

		String getMessage() {
			return m_Message;
		}
	};
	class IndexOutOfBound : public myException {
	private:
		String m_Message;
	public:
		IndexOutOfBound() : m_Message{ "Trying to aceess out Of bound index\n" } {}

		IndexOutOfBound(const String& msg) : m_Message{ msg } {}

		String getMessage() {
			return m_Message;
		}
	};
}


#endif 