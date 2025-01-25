#pragma once
#include <Windows.h>
#include <string>

// All methods taken from https://stackoverflow.com/questions/34065/how-to-read-a-value-from-the-windows-registry

class CRegistry
{
public:
    static bool OpenKey(const std::wstring& registryPath, HKEY baseKey, HKEY& hKey);
    static LONG GetDWORDValue(HKEY hKey, const std::wstring& valueName, DWORD& value, DWORD defaultValue = 0);
    static LONG GetBoolValue(HKEY hKey, const std::wstring& valueName, bool& value, bool defaultValue = false);
    static LONG GetStringValue(HKEY hKey, const std::wstring& valueName, std::wstring& value, const std::wstring& defaultValue = L"");
    static void CloseKey(HKEY hKey);
};

