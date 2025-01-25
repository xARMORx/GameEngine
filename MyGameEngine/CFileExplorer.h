#pragma once
#include <vector>
#include <string>

class CFileExplorer
{
	struct tFile {
		std::string szFileName;
		std::string szFormat;
	};

	std::vector<tFile> m_vFiles;
public: 
	CFileExplorer();
	void Draw();
	void DrawFileIcon(const tFile& file);
};