#pragma once
#include <cstdio>
#include <string>

class Logger
{
public:
	static Logger shared;
	
	typedef enum {
		ERROR,
		WARNING,
		IMPORTANT,
		INFO,
		DEBUG
	} LogLevel;
	
	Logger();
	
	LogLevel getLevel() const;
	void setLevel(LogLevel l);
	
	void log(LogLevel level, const char * file, int line, const char * func, const char * fmt, ...);
	void log(FILE * f, bool colored, LogLevel level, const char * filename, int line, const char * func, const char * msg);
	
private:
	LogLevel level;
};

#define LOG(level, ...) Logger::shared.log(Logger::level, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
