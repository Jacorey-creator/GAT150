#include "Logger.h"
#include "FileIO.h"
#include <iostream>

namespace afro

{
	Logger g_logger(LogLevel::Info, &std::cout, "log.txt");

	bool Logger::Log(LogLevel loglevel, const std::string filename, int line)
	{
		if(loglevel < m_loglevel) return false;
		switch (loglevel)
		{
		case afro::LogLevel::Info:
			*this << "INFO: ";
			break;
		case afro::LogLevel::Warning:
			*m_ostream << "WARNING: ";

			break;
		case afro::LogLevel::Error:
			*this << "ERROR: ";

			break;
		case afro::LogLevel::Assert:
			*this << "ASSERT: ";
			break;
		default:
			break;
		}

		*this << filename << "(" << line << ") ";
		return true;
	}
}