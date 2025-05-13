#pragma once
#include <iostream>
#include <stdexcept>
#include <exception>
using namespace std;

class ILogger {
public:
	virtual void log(const string& message) = 0;
	virtual ~ILogger() = default;
};