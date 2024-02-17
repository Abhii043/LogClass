#ifndef string0
#define string0

#include<cstring>
#include<iostream>


namespace Type {
	class String {
	private:
		std::unique_ptr<char[]> m_buffer0;
		unsigned int m_size;


	public:
	
		String(const char* str ="") {
			// std::cout << "Default constructor "<<"\n";
			m_size = static_cast<int>(strlen(str));
			m_buffer0 = std::make_unique<char[]>(m_size + 1);
			memcpy(m_buffer0.get(), str, m_size + 1);
		}


		int length() const
		{
			return m_size;
		}

		char& operator[](unsigned int index) const;

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
