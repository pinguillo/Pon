#pragma once
#include <iostream>
#include <sstream>

#define PIN_ERROR(message)\
{\
	std::stringstream m;\
	m << "<><><> Error: " << message << std::endl;\
	throw std::runtime_error(m.str());\
}

#define PIN_WARNING(message)\
std::wclog << "<><> Warning: " << message << std::endl;

#define PIN_INFO(message)\
std::wclog << "<> Info: " << message << std::endl;