#include "../include/string.h"
#include"../include/Exception.h"

#ifndef Date0
#define Date0

namespace Utility {

	class Date {

	private:
		unsigned int m_day;
		unsigned int m_month;
		unsigned int m_year;

		bool isLeapYear(unsigned int year) const;
		unsigned int DaysInMonth(unsigned int month, unsigned  int year) const;

		mutable bool isCacheValid;
		mutable Type::String cache;


	public:
		Date(unsigned dd, unsigned int mm, unsigned int yy);
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