#pragma once
#include "BaseLogger.hpp"

class ConsoleLogger : public virtual BaseLogger{
public:
	ConsoleLogger() {};
	void log(const string& message) override {
		std::cout << prefix << " " << message << std::endl;
	}
};