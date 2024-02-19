#ifndef Date0
#define Date0

#include "../include/string.h"

enum d_Format {
	dmy , dym , myd , ymd , ydm , mdy 
};

namespace Utility {

	class Date {

	private:
		unsigned int m_day;
		unsigned int m_month;
		unsigned int m_year;
		d_Format m_Format;

		bool isLeapYear(unsigned int year) const;
		unsigned int DaysInMonth(unsigned int month, unsigned  int year) const;

		mutable bool isCacheValid;
		mutable Type::String cache;

		void dateFormater(unsigned int d, unsigned int m, unsigned int y);

	public:
		Date(unsigned a, unsigned int b, unsigned int c , d_Format format);
		void setDate(unsigned int dd, unsigned int mm, unsigned int yy);

		void setDay(unsigned int dd);
		void setMonth(unsigned int mm);
		void setYear(unsigned int yy);
 
		Date& addDay(unsigned int days);
		Date& addMonth(unsigned int month);
		Date& addYear(unsigned int year);
		void DisplayDate() const;

		void updateCache() const;
		Type::String getStrDate();

	};
}
#endif