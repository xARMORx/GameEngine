#include "CFileExplorer.h"
#include "CRender.h"

CFileExplorer::CFileExplorer()
{
	this->m_vFiles = {};
}

void CFileExplorer::Draw()
{
	ImGui::Begin("File Explorer");

	ImGui::End();
}

void CFileExplorer::DrawFileIcon(const tFile& file)
{
	auto dl = ImGui::GetWindowDrawList();
}
