#pragma once
#include <string>
#include <sstream>
#include <filesystem>

class CAlgorithms
{
public:
	static std::wstring ConvertStringToWideChar(const std::string& str);
	static std::string ConvertWideCharToString(const std::wstring& wstr);
    static std::filesystem::path GetExecutableDirectory();

    template<typename ... Args>
    static std::string StringFormat(const std::string& format, Args ... args)
    {
        int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
        if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
        auto size = static_cast<size_t>(size_s);
        std::unique_ptr<char[]> buf(new char[size]);
        std::snprintf(buf.get(), size, format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
    }
};

