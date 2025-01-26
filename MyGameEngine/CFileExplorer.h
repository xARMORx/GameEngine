#pragma once
#include <vector>
#include <string>
#include <filesystem>

class CFileExplorer
{
	struct tFile {
		std::string szFileName;
		std::string szFormat;
	};

	std::vector<tFile> m_vFiles;
	std::filesystem::directory_entry m_ContentPath;
	std::filesystem::directory_entry m_pComponentsPath;
public:
	CFileExplorer();

	void Draw();
	void DrawFileIcon(const tFile& file);
	void AddToContentPath(const std::filesystem::directory_entry& path);
	void RemoveFromContentPath(const std::filesystem::directory_entry& path);
	std::filesystem::directory_entry& GetComponentsPath();
};

extern CFileExplorer* g_pFileExplorer;