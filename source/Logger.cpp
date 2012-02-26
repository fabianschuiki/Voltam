#include <cassert>
#include <cstdarg>
#include <cstring>
#include <string>

#include "Logger.h"

Logger Logger::shared;

void fputs_padded(FILE * f, const char * str, int padding)
{
	for (const char * s = str; *s != 0; s++) {
		fputc(*s, f);
		if (*s == '\n') {
			for (int i = 0; i < padding; i++)
				fputc(' ', f);
			fputs("| ", f);
		}
	}
}

Logger::Logger()
{
#ifdef BUILD_DEBUG
	level = DEBUG;
#else
	level = IMPORTANT;
#endif
}

Logger::LogLevel Logger::getLevel() const { return level; }
void Logger::setLevel(LogLevel l) { level = l; }

void Logger::log(LogLevel level, const char * file, int line, const char * func, const char * fmt, ...)
{
	//Ignore certain logs that are above the set maximum level.
	if (level > this->level)
		return;
	
	//Format the string.
	va_list args;
	va_start(args, fmt);
	char * str;
	vasprintf(&str, fmt, args);
	va_end(args);
	
	//Fetch the filename.
	const char * filename = strrchr(file, '/');
	if (filename)
		filename += 1;
	else
		filename = file;
	
	//Write to the console.
	log((level == ERROR ? stderr : stdout), false, level, filename, line, func, str);
	
	//Clean up.
	delete str;
}

void Logger::log(FILE * f, bool colored, LogLevel level, const char * filename, int line, const char * func, const char * msg)
{
	size_t pos = ftell(f);
	if (colored) fputs("\e[0;32m", f);
	fputs(filename, f);
	if (colored) fputs("\e[0m", f);
	fprintf(f, ":%i: ", line);
	if (colored) fputs("\e[1;34m", f);
	fputs(func, f);
	if (colored) fputs("\e[0m", f);
	fputs(": ", f);
	if (colored) {
		if (level == ERROR)     fputs("\e[1;31m", f);
		if (level == WARNING)   fputs("\e[1;33m", f);
		if (level == IMPORTANT) fputs("\e[1;35m", f);
	}
	if (level == ERROR) fputs("*** ", f);
	fputs_padded(f, msg, ftell(f) - pos);
	if (colored) fputs("\e[0m", f);
	fputs("\n", f);
}
