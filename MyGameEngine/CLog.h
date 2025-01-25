#pragma once
#ifndef _CLOG_H_
#define _CLOG_H_
#include <iostream>

enum eLogType {
	DEBUG_MESSAGE,
	ERROR_MESSAGE
};

class CLog {
public:
	template<typename ... Args>
	static void AddMessage(eLogType nType, std::string szFormat, Args ... args) {
		if (nType == DEBUG_MESSAGE)
			szFormat = "[Debug]: " + szFormat;
		else if (nType == ERROR_MESSAGE)
			szFormat = "[Error]: " + szFormat;
		int size_s = std::snprintf(nullptr, 0, szFormat.c_str(), args ...) + 1;
		if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
		auto size = static_cast<size_t>(size_s);
		std::unique_ptr<char[]> buf(new char[size]);
		std::snprintf(buf.get(), size, szFormat.c_str(), args ...);
		std::string out{};
		out.assign(buf.get(), buf.get() + size - 1);
		std::cout << out << std::endl;
	}
};

#endif