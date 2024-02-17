#include "../include/date.h"
#include "../include/string.h"
#include"../include/Exception.h"
#include <iostream>

using Utility::Date;
using Type::String;
using Exception::myException;

bool Date::isLeapYear(unsigned int year) const {
	if ((year % 4 == 0 && year % 100 == 0) || year % 400 == 0) return true;
	else return false;
}

unsigned int Date::DaysInMonth(unsigned int month, unsigned  int year) const {
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10:case 12: return 31;
	case 4: case 6: case 9: case 11: return 30;


	case 2:  return ((isLeapYear(year)) ? 29 : 28);

	default: return 0;
	}
}

void Date::setDay(unsigned int dd)try {
	(dd < 1 || dd > DaysInMonth(m_month, m_year)) ? (throw Exception::InvalidDate{ "Please Enter a valid day input which is in range " }) : (m_day = dd) ;
}
catch (Exception::myException& e) {
	std::cout << e.getMessage() << '\n';
}

void Date::setMonth(unsigned int mm)try {
	(mm < 1 || mm > 12) ? (throw Exception::InvalidDate{ "Please Enter a valid Month input which is in range " }) : (m_month = mm);
}
catch (Exception::myException& e) {
	std::cout << e.getMessage() << '\n';
}
void Date::setYear(unsigned int yy)try {
	(yy < 1) ? (throw Exception::InvalidDate{ "Please Enter a valid Year input " }) : (m_year = yy);
}
catch (Exception::myException& e) {
	std::cout << e.getMessage() << '\n';
}

Date::Date(unsigned dd, unsigned int mm, unsigned int yy) : m_day{ dd }, m_month{ mm }, m_year{ yy } {
	updateCache();
	try {
		if (mm <= 12 && mm > 0) {
			if (dd <= DaysInMonth(mm, yy)) {
				m_day = dd;
				m_month = mm;
				m_year = yy;
			}
			else {
				throw Exception::InvalidDate{ "Please Enter a Valid Day Input" };
			}
		}
		else {
			throw Exception::InvalidDate{ "Please Enter a Valid Month Input" };
		}
	}
	catch (Exception::myException& e) {
		std::cout << e.getMessage() << "\n";
	}
}

void Date::setDate(unsigned int dd, unsigned int mm, unsigned int yy)
{
	try {
		if (mm <= 12 && mm > 0) {
			if (dd <= DaysInMonth(mm, yy)) {
				m_day = dd;
				m_month = mm;
				m_year = yy;
			}
			else {
				throw Exception::InvalidDate{ "Please Enter a Valid Day Input" };
			}
		}
		else {
			throw Exception::InvalidDate{ "Please Enter a Valid Month Input" };
		}
	}
	catch (Exception::myException& e) {
		std::cout << e.getMessage() << "\n";
	}
}

Date& Date::addDay(unsigned int days)
{
	while (days != 0) {
		auto dayinMonth = DaysInMonth(m_month, m_year);
		if (days > dayinMonth) {
			days = days - (dayinMonth - m_day + 1);
			if (m_month == 12) {
				m_month = 1;
				m_year++;
				m_day = 1;
			}
			else {
				m_month++;
				m_day = 1;
			}
		}
		else {
			if ((m_day + days) > dayinMonth) {
				m_day = ((m_day + days) - dayinMonth);
				if (m_month == 12) {
					m_month = 1;
					m_year++;
					days = 0;
				}
				else {
					m_month++;
					days = 0;
				}
			}
			else {
				m_day = m_day + days;
				days = 0;
			}

		}
	}

	isCacheValid = false;
	return *this;
}

Date& Date::addMonth(unsigned int month)
{
	if (month > 12) {
		m_year = m_year + (month / 12);
		month = month % 12;
	}
	if (m_month + month > 12) {
		m_month = (m_month + month) - 12;
		m_year += 1;
		auto DIM = DaysInMonth(m_month, m_year);
		if (DIM < m_day) {
			auto temp = m_day - DIM;
			m_month++;
			m_day = temp;
		}
	}

	else {
		m_month++;
		auto DIM = DaysInMonth(m_month, m_year);
		if (DIM < m_day) {
			auto temp = m_day - DIM;
			m_month++;
			m_day = temp;
		}
	}

	isCacheValid = false;
	return *this;
}


Date& Date::addYear(unsigned int year)
{

	m_year += year;
	isCacheValid = false;
	return *this;

}

void Date::DisplayDate() const
{
	std::cout << "date is: " << m_day << " / " << m_month << " / " << m_year << "\n";
}

void Date::updateCache() const {
	cache = "";
	cache.append(String::toString(m_day)).append("/");
	cache.append(String::toString(m_month)).append("/");
	cache.append(String::toString(m_year));
	isCacheValid = true;
}

String Date::getStrDate() {
	if (!isCacheValid) {
		updateCache();
	}
	return cache;
}