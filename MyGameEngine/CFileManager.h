#pragma once
#include <filesystem>
#include <map>

class CFileManager
{
private:
	std::string m_szCurrentPath;
	std::wstring m_szCurrentFile;
	bool m_bEnable;
	std::map<std::wstring, std::wstring> m_SystemPaths;
	std::vector<std::filesystem::directory_entry> m_vFilesList;


	void InitSystemPaths();
public:
	CFileManager();
	void Open();
	void Close();
	bool IsOpened();
	std::wstring GetCurrentPath();
	void OpenFile();
	void DeleteFile();
	void CopyFile();
	void CutFile();
	void PasteFile();
	void UpdateFileList();
	void Draw();
};