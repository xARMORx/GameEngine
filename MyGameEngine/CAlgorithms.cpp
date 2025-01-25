#include "CAlgorithms.h"
#include <Windows.h>

std::wstring CAlgorithms::ConvertStringToWideChar(const std::string& str)
{
    const int bufferSize = MultiByteToWideChar(1251, 0, str.c_str(), -1, nullptr, 0);
    if (bufferSize == 0) {
        return L"NULL";
    }

    wchar_t* buffer = new wchar_t[bufferSize];
    if (!MultiByteToWideChar(1251, 0, str.c_str(), -1, buffer, bufferSize)) {
        delete[] buffer;
        return L"NULL";
    }
    std::wstring retn{};
    retn.assign(buffer);
    delete[] buffer;
    return retn;
}

std::string CAlgorithms::ConvertWideCharToString(const std::wstring& wstr)
{
    const int bufferSize = WideCharToMultiByte(1251, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (bufferSize == 0) {
        return "NULL";
    }

    char* buffer = new char[bufferSize];
    if (!WideCharToMultiByte(1251, 0, wstr.c_str(), -1, buffer, bufferSize, nullptr, nullptr)) {
        delete[] buffer;
        return "NULL";
    }

    std::string retn(buffer);
    delete[] buffer;
    return retn;
}