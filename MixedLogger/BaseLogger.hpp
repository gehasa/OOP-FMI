#pragma once
#include "ILogger.hpp"

class BaseLogger : public virtual ILogger{
public:
	BaseLogger(const string& prefix = "[Log]") : prefix(prefix) {}
	virtual ~BaseLogger() = default;
protected:
	string prefix;
};