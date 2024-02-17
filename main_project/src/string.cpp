#include "../include/string.h"
#include <iostream>
#include"../include/Exception.h"

using Type::String;

char& String::operator[](unsigned int index) const {
	try {
		if (index >= m_size || index < 0) {
			throw Exception::IndexOutOfBound{ "Invalid Access of Index : Accessing index which is not bound with this String\a" };
		}
		return m_buffer0.get()[index];
	}
	catch (Exception::myException& e) {
		std::cout << e.getMessage() << "\n";
	}
	return m_buffer0.get()[m_size];
}

String::String(const String& str)
{
	// std::cout << "Copy Constructor\n";
	m_buffer0 = std::make_unique<char[]>(str.m_size + 1);
	m_size = str.m_size;
	memcpy(m_buffer0.get(), str.m_buffer0.get(), m_size + 1);
}


String& String::operator=(const String& other)
{
	// std::cout << "Copy Assignment \n";
	if(*this==other){
		return *this;
	}
	m_size = other.m_size;
	m_buffer0 = std::make_unique<char[]>(m_size + 1);
	memcpy(m_buffer0.get(), other.m_buffer0.get(), m_size);
	m_buffer0[m_size] = '\0';
	return *this;
}


String::String(String&& other) noexcept {
	// std::cout << "Move Constructor\n";
	m_size = other.m_size;
	m_buffer0 = std::move(other.m_buffer0);
}


String& String::operator=(String&& other) noexcept {

	// std::cout << "Move Assignment\n";
	m_size = other.m_size;
	m_buffer0 = std::move(other.m_buffer0);
	return *this;
}

String Type::operator+(const String& other, const String& other1)
{
	auto newBuffer = std::make_unique<char[]>(other.m_size + other1.m_size + 1);
	memcpy(newBuffer.get(), other.m_buffer0.get(), other.m_size);
	memcpy(newBuffer.get() + other.m_size, other1.m_buffer0.get(), other1.m_size + 1);
	auto newSize = other.m_size + other1.m_size;
	String newString(newBuffer.get());
	newString.m_size = newSize;
	return newString;
}

String& String::append(const String& other) {
	auto newSize = m_size + other.m_size;
	auto tempBuffer = std::make_unique<char[]>(newSize + 1);
	memcpy(tempBuffer.get(), m_buffer0.get(), m_size);
	memcpy(tempBuffer.get() + m_size, other.m_buffer0.get(), other.m_size + 1);
	m_size = newSize;
	m_buffer0 = std::move(tempBuffer);
	return *this;
}

std::ostream& Type::operator<<(std::ostream& stream, const String& string) {
	stream << string.m_buffer0.get();
	return stream;
}

bool Type::operator==(const String& other, const String& other1) {

	if (other.m_size != other1.m_size) return false;

	for (auto i = 0U; i < other.m_size; i++) {
		if (other[i] != other1[i]) {
			return false;
		}
	}
	return true;
}
bool Type::operator!=(const String& other, const String& other1) {

	if (other.m_size != other1.m_size) return true;

	for (auto i = 0U; i < other.m_size; i++) {
		if (other[i] != other1[i]) {
			return true;
		}
	}
	return false;
}

String& String::toLowerCase() {
	for (auto i = 0U; i < m_size; i++) {
		if (m_buffer0[i] >= 65 && m_buffer0[i] <= 90) {
			m_buffer0[i] += 32;
		}
	}
	return *this;
}

String& String::toUpperCase() {
	for (auto i = 0U; i < m_size; i++) {
		if (m_buffer0[i] >= 97 && m_buffer0[i] <= 122) {
			m_buffer0[i] -= 32;
		}
	}
	return *this;
}

String Type::String::toString(int num)
{
	auto isNegativeNumber = (num < 0);
	std::unique_ptr<char[]> tempString;
	auto temp = num;
	auto m_size = 0U;

	while (temp != 0) {
		temp /= 10;
		m_size++;
	}

	if (isNegativeNumber) {
		m_size++;
		temp = (-1) * num;
	}
	else {
		temp = num;
	}

	tempString = std::make_unique<char[]>(m_size + 1);
	tempString[m_size] = '\0';

	if (isNegativeNumber) {
		tempString[0] = '-';
	}

	for (auto i = m_size - 1; i >= 0 && temp != 0; i--) {
		auto digit = temp % 10;
		temp /= 10;
		tempString[i] = digit + '0';
	}

	return { String(tempString.get()) };
}
