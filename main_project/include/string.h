#ifndef string0
#define string0

#include<iostream>

namespace Type {
	class String {
	private:
		std::unique_ptr<char[]> m_buffer;
		unsigned int m_size;


	public:
	
		String(const char* str = "");

		int length() const
		{
			return m_size;
		}

		char& operator[](unsigned int index) const;

		char& at(unsigned int index) const;

		 const char* raw() const;

		String(const String& str);

		String& operator=(const String& other);

		String(String&& other) noexcept;

		String& operator=(String&& other) noexcept;

		friend String operator+(const String&, const String&);

		String& append(const String&);

		friend bool operator==(const String&, const String&);

		friend bool operator!=(const String&, const String&);

		String& toLowerCase();

		String& toUpperCase();

		static String toString(int num);

		friend std::ostream& operator<<(std::ostream& stream, const String& str);
	};
}

#endif
