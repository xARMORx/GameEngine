#include "CRegistry.h"

bool CRegistry::OpenKey(const std::wstring& registryPath, HKEY baseKey, HKEY& hKey)
{
    LONG result = RegOpenKeyExW(baseKey, registryPath.c_str(), 0, KEY_READ, &hKey);
    return (result == ERROR_SUCCESS);
}

LONG CRegistry::GetDWORDValue(HKEY hKey, const std::wstring& valueName, DWORD& value, DWORD defaultValue)
{
    value = defaultValue;
    DWORD dataSize = sizeof(DWORD);
    LONG error = RegQueryValueExW(hKey, valueName.c_str(), nullptr, nullptr, reinterpret_cast<LPBYTE>(&value), &dataSize);
    return error;
}

LONG CRegistry::GetBoolValue(HKEY hKey, const std::wstring& valueName, bool& value, bool defaultValue)
{
    DWORD defaultVal = defaultValue ? 1 : 0;
    DWORD result = defaultVal;
    LONG error = GetDWORDValue(hKey, valueName, result, defaultVal);
    value = (result != 0);
    return error;
}

LONG CRegistry::GetStringValue(HKEY hKey, const std::wstring& valueName, std::wstring& value, const std::wstring& defaultValue)
{
    value = defaultValue;
    WCHAR buffer[512];
    DWORD dataSize = sizeof(buffer);
    LONG error = RegQueryValueExW(hKey, valueName.c_str(), nullptr, nullptr, reinterpret_cast<LPBYTE>(buffer), &dataSize);
    if (error == ERROR_SUCCESS)
    {
        value = buffer;
    }
    return error;
}

void CRegistry::CloseKey(HKEY hKey)
{
    RegCloseKey(hKey);
}