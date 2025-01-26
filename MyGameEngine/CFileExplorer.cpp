#include "CFileExplorer.h"
#include "CRender.h"
#include "CDebugConsole.h"

CFileExplorer* g_pFileExplorer = { nullptr };

CFileExplorer::CFileExplorer()
{
	this->m_vFiles = {};
	
	if (!std::filesystem::directory_entry(CAlgorithms::GetExecutableDirectory().string() + "\\Content").exists()) {
		g_pDebugConsole->AddDebugMessage("Content path is not exists and will created!");
		std::filesystem::create_directory(CAlgorithms::GetExecutableDirectory().string() + "\\Content");
	}
	this->m_ContentPath = std::filesystem::directory_entry(CAlgorithms::GetExecutableDirectory().string() + "\\Content");
	for (auto& it : std::filesystem::directory_iterator(this->m_ContentPath)) {
		tFile file;
		file.szFileName = it.path().filename().string();
		file.szFormat = it.path().extension().string();
		this->m_vFiles.push_back(file);
	}

	if (!std::filesystem::directory_entry(CAlgorithms::GetExecutableDirectory().string() + "\\Components").exists()) {
		g_pDebugConsole->AddDebugMessage("Content path is not exists and will created!");
		std::filesystem::create_directory(CAlgorithms::GetExecutableDirectory().string() + "\\Components");
	}
	this->m_pComponentsPath = std::filesystem::directory_entry(CAlgorithms::GetExecutableDirectory().string() + "\\Components");
}

void CFileExplorer::Draw()
{
	ImGui::Begin("File Explorer");
	for (auto& it : this->m_vFiles) {
		this->DrawFileIcon(it);
	}
	ImGui::End();
}

void CFileExplorer::DrawFileIcon(const tFile& file)
{
	
	ImGui::Button(file.szFileName.c_str(), {100.f, 100.f});
	ImGui::SameLine();
}

void CFileExplorer::AddToContentPath(const std::filesystem::directory_entry& path)
{
	if (!this->m_ContentPath.exists()) {
		g_pDebugConsole->AddErrorMessage("Content path is not exists!");
		return;
	}

	if (!path.exists()) {
		g_pDebugConsole->AddErrorMessage("File %s is not exists!", path.path().filename().string().c_str());
		return;
	}

	for (const auto& it : std::filesystem::directory_iterator(this->m_ContentPath))
	{
		if (it.path().filename().string() == path.path().filename().string()) {
			this->RemoveFromContentPath(it);
		}
	}

	if (this->m_ContentPath.exists() && path.exists()) {
		g_pDebugConsole->AddDebugMessage("File: %s added to file explorer", path.path().filename().string().c_str());
		std::filesystem::copy(path, this->m_ContentPath);
		tFile newFile;
		newFile.szFileName = path.path().filename().string();
		newFile.szFormat = path.path().extension().string();
		this->m_vFiles.push_back(newFile);
	}
}

void CFileExplorer::RemoveFromContentPath(const std::filesystem::directory_entry& path)
{
	std::filesystem::remove(path);
}

std::filesystem::directory_entry& CFileExplorer::GetComponentsPath()
{
	return this->m_pComponentsPath;
}
