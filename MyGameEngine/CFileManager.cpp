#include "CFileManager.h"
#include "CRender.h"
#include "CRegistry.h"
#include "CAlgorithms.h"
#include <iostream>
#include <set>

#include "CLog.h"
#include "CDebugConsole.h"
#include "CFileExplorer.h"

#ifdef DeleteFile
#undef DeleteFile
#endif
#ifdef CopyFile
#undef CopyFile
#endif

CFileManager* g_pFileManager = { nullptr };

void CFileManager::InitSystemPaths()
{
	HKEY hKey;
	if (CRegistry::OpenKey(L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", HKEY_CURRENT_USER, hKey))
	{
		std::wstring szPath{};
		if (CRegistry::GetStringValue(hKey, L"Desktop", szPath) == ERROR_SUCCESS)
			this->m_SystemPaths.emplace(std::make_pair(L"Desktop", szPath));
		if (CRegistry::GetStringValue(hKey, L"Personal", szPath) == ERROR_SUCCESS)
			this->m_SystemPaths.emplace(std::make_pair(L"Documents", szPath));
		if (CRegistry::GetStringValue(hKey, L"My Pictures", szPath) == ERROR_SUCCESS)
			this->m_SystemPaths.emplace(std::make_pair(L"Pictures", szPath));
	}
	else
	{
		std::wcerr << L"Failed to open registry key!" << std::endl;
	}
}

CFileManager::CFileManager()
{
	this->m_bEnable = false;
	this->m_szCurrentPath = {};
	this->m_szCurrentFile = {};
	this->m_SystemPaths = {};
	this->m_vFilesList = {};
	this->m_nSelectedFile = {};
	this->InitSystemPaths();
}

void CFileManager::Open()
{
	this->m_bEnable = true;
}

void CFileManager::Close()
{
	this->m_bEnable = false;
}

bool CFileManager::IsOpened()
{
	return this->m_bEnable;
}

std::wstring CFileManager::GetCurrentPath()
{
	return CAlgorithms::ConvertStringToWideChar(this->m_szCurrentPath);
}

void CFileManager::OpenFile()
{
	std::filesystem::directory_entry entry = this->m_vFilesList[this->m_nSelectedFile];

	static const std::set<std::string> imageExtensions = {
		".jpg", ".jpeg", ".png"
	};

	if (entry.is_regular_file()) {
		std::string extension = entry.path().extension().string();
		std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
		if (imageExtensions.find(extension) != imageExtensions.end()) {
			g_pFileExplorer->AddToContentPath(entry);

		}
	}
}

void CFileManager::DeleteFile()
{
}

void CFileManager::CopyFile()
{
}

void CFileManager::CutFile()
{
}

void CFileManager::PasteFile()
{
}

void CFileManager::UpdateFileList()
{
	this->m_vFilesList.clear();
	this->m_nSelectedFile = -1;
	for (const auto& it : std::filesystem::directory_iterator(this->m_szCurrentPath))
	{
		this->m_vFilesList.push_back(it);
	}
}

void CFileManager::Draw()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 7.f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5f, 0.5f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1);
	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_FirstUseEver);
	ImGui::Begin("File Manager", &this->m_bEnable, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);

	ImVec2 vWindowSize = ImGui::GetWindowSize();
	ImGui::Button("<-", ImVec2(20.f, 20.f));
	ImGui::SameLine();
	ImGui::Button("->", ImVec2(20.f, 20.f));
	ImGui::SameLine();
	ImGui::PushItemWidth(vWindowSize.x - (ImGui::GetStyle().ItemSpacing.x * 4.f) - (20.f * 2.f));
	if (ImGui::InputText("##FileExplorerPath", &this->m_szCurrentPath, ImGuiInputTextFlags_EnterReturnsTrue)) {
		if (std::filesystem::is_directory(this->m_szCurrentPath)) {
			this->UpdateFileList();
		}
		else {
			g_pDebugConsole->AddErrorMessage("Path: %s is not a directory!", this->m_szCurrentPath.c_str());
			CLog::AddMessage(ERROR_MESSAGE, "Path: %s is not a directory!", this->m_szCurrentPath.c_str());
		}
	}
	ImGui::BeginChild("Base Path", ImVec2(vWindowSize.x * 0.1583f, vWindowSize.y - (ImGui::GetStyle().ItemSpacing.y * 4.f) - (20.f * 2.f)));
	for (auto& it : this->m_SystemPaths)
	{
		if (ImGui::Button(CAlgorithms::ConvertWideCharToString(it.first).c_str(), ImVec2(ImGui::GetWindowSize().x, 20.f)))
		{
			this->m_szCurrentPath = CAlgorithms::ConvertWideCharToString(it.second);
			this->UpdateFileList();
		}
	}
	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("CurrentPath", ImVec2((vWindowSize.x - (vWindowSize.x * 0.1583f)) - (ImGui::GetStyle().ItemSpacing.x * 3.f), vWindowSize.y - (ImGui::GetStyle().ItemSpacing.y * 4.f) - (20.f * 2.f)));

	/*
	Here rendered columns with info of files/folderes
	*/
	ImGui::Columns(2);
	for (int i{}; i < this->m_vFilesList.size(); i++)
	{
		ImGui::Selectable(this->m_vFilesList[i].path().filename().string().c_str(), i == this->m_nSelectedFile ? true : false, ImGuiSelectableFlags_SpanAllColumns);
		if (ImGui::IsItemHovered()) {
			if (ImGui::IsMouseDoubleClicked(0)) {
				if (this->m_vFilesList[i].is_directory()) {
					this->m_szCurrentPath = this->m_vFilesList[i].path().string();
					this->UpdateFileList();
					break;
				}
				else {
					this->OpenFile();
					break;
				}
			}
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left, false)) {
				this->m_nSelectedFile = i;
			}
		}
		
		ImGui::NextColumn();
		ImGui::Selectable(std::string(std::to_string(this->m_vFilesList[i].file_size() / 1024) + " KB##" + std::to_string(i)).c_str());
		ImGui::NextColumn();
		
	}

	ImGui::EndChild();
	ImGui::End();
	ImGui::PopStyleVar(3);
}
