#pragma once
#include <string>

class CAlgorithms
{
public:
	static std::wstring ConvertStringToWideChar(const std::string& str);
	static std::string ConvertWideCharToString(const std::wstring& wstr);
};

