#pragma once
#include "CRender.h"
#include <vector>
#include <filesystem>

class CBaseComponents
{
	struct tComponent {
		std::string szName;
		LPDIRECT3DTEXTURE9 pIcon;
	};

	std::vector<tComponent> m_vComponentsVector;
	void InitDefaultComponents();
public:
	CBaseComponents();

	void Draw();
	bool AddComponent(const std::string& iconPath, const std::string& szComponentName);
};

extern CBaseComponents* g_pBaseComponents;