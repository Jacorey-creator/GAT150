#pragma once
#include "Framework/Singleton.h"
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>

#ifdef _DEBUG
#define INFO_LOG(message) { if(afro::Logger::Instance().Log(afro::LogLevel::Info, __FILE__,__LINE__)) { afro::Logger::Instance() << message << "\n"; } }
#define WARNING_LOG(message) { if(afro::Logger::Instance().Log(afro::LogLevel::Warning, __FILE__,__LINE__)) { afro::Logger::Instance() << message << "\n";} }
#define ERROR_LOG(message) { if(afro::Logger::Instance().Log(afro::LogLevel::Error, __FILE__,__LINE__)) { afro::Logger::Instance() << message << "\n";} }
#define ASSERT_LOG(condition, message) { if (!condition && afro::Logger::Instance().Log(afro::LogLevel::Assert, __FILE__,__LINE__)) { afro::Logger::Instance() << message << "\n";} assert(condition); }
#else
#define INFO_LOG(message) {}
#define WARNING_LOG(message) {}
#define ERROR_LOG(message) {}
#define ASSERT_LOG(condition, message) {}
#endif

namespace afro
{
	enum class LogLevel
	{
		Info,
		Warning,
		Error,
		Assert
	};

	class Logger : public Singleton<Logger>
	{
	public:

		Logger(LogLevel loglevel = LogLevel::Info, std::ostream* ostream = &std::cout, const std::string& filename = "log.txt") :
			m_ostream{ ostream },
			m_loglevel{ loglevel } 
		{
			if (!filename.empty()) m_fstream.open(filename);
		}

		bool Log(LogLevel loglevel, const std::string filename, int line);
		
		template<typename T>
		Logger& operator << (T v);


	private:
		LogLevel m_loglevel;
		std::ostream* m_ostream = nullptr;
		std::ofstream m_fstream;
	};

	//extern Logger g_logger;
	template<typename T>
	inline Logger& Logger::operator << (T value)
	{
		if (m_ostream) *m_ostream << value;
		if (m_fstream.is_open()) 
		{
			m_fstream << value;
			m_fstream.flush();
		}
		return *this;
	}
}