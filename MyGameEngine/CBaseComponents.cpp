#include "CBaseComponents.h"
#include "CDebugConsole.h"
#include "CFileExplorer.h"

CBaseComponents* g_pBaseComponents;

CBaseComponents::CBaseComponents()
{
	this->m_vComponentsVector = {};
	this->InitDefaultComponents();
}

void CBaseComponents::Draw()
{
	ImGui::Begin("Base Components");
	for (auto& it : this->m_vComponentsVector) {
		ImGui::Image((ImTextureID)it.pIcon, { 35.f, 35.f });
		ImGui::SameLine();
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (ImGui::GetItemRectMin().y * 0.3f) - (ImGui::CalcTextSize(it.szName.c_str()).y * 0.5f));
		ImGui::Text(it.szName.c_str());
	}
	ImGui::End();
}

bool CBaseComponents::AddComponent(const std::string& iconName, const std::string& szComponentName)
{
	std::string path = g_pFileExplorer->GetComponentsPath().path().string() + "\\" + iconName;
	tComponent newComponent;
	newComponent.szName = szComponentName;
	HRESULT hr = D3DXCreateTextureFromFileA(g_pRender->GetDevice(), path.c_str(), &newComponent.pIcon);
	if (hr != S_OK) {
		g_pDebugConsole->AddErrorMessage("File: %s is not loaded! Error: 0x%X", path.c_str(), hr);
		return false;
	}
	
	this->m_vComponentsVector.push_back(newComponent);
	return true;
}

void CBaseComponents::InitDefaultComponents()
{
	this->AddComponent("textureIcon.png", "Texture");
}
