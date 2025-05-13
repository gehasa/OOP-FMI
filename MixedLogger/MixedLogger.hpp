#pragma once
#include "FileLogger.hpp"
#include "ConsoleLogger.hpp"

class MixedLogger : public virtual FileLogger, public virtual ConsoleLogger{
public:
	MixedLogger(const string& file, const string& prefix = "[Mixed]") : BaseLogger(prefix), FileLogger(file), ConsoleLogger(){}
	void log(const string& message) override {
		FileLogger::log(message);
		ConsoleLogger::log(message);
	}
	virtual ~MixedLogger() = default;
};