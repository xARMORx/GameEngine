#include "CSprite.h"

CSprite::CSprite()
{
	this->m_pTexture = { nullptr };
	this->m_vPos = { 0.f, 0.f };
	this->m_vSize = { 0.f, 0.f };
}

CSprite::CSprite(CTexture* pTexture, CVector2d vPos, CVector2d vSize)
{
	this->m_pTexture = pTexture;
	this->m_vPos = vPos;
	this->m_vSize = vSize;
}

void CSprite::SetTexture(CTexture* pTexture)
{
	this->m_pTexture = pTexture;
}

void CSprite::SetTexture(LPDIRECT3DTEXTURE9 pD3DTexture, CVector2d vSize)
{
	this->m_pTexture = new CTexture(pD3DTexture, vSize);
}

void CSprite::SetSize(const CVector2d& vSize)
{
	this->m_vSize = vSize;
}

CVector2d& CSprite::GetSize()
{
	return this->m_vPos;
}

void CSprite::Draw()
{
	this->Draw(this->m_vPos, this->m_vSize);
}

void CSprite::Draw(const CVector2d& vPos, const CVector2d& vSize)
{
	ImDrawList* pDrawList = { nullptr };
	switch (this->m_nDrawType) {
	case eDrawType::BACKGROUND: {
		pDrawList = ImGui::GetBackgroundDrawList();
		break;
	}
	case eDrawType::WINDOW: {
		pDrawList = ImGui::GetWindowDrawList();
		break;
	}
	case eDrawType::FOREGROUND: {
		pDrawList = ImGui::GetForegroundDrawList();
		break;
	}
	}
	if (!pDrawList || !this->m_pTexture->GetD3DTexture())
		return;

	pDrawList->AddImage(
		(ImTextureID)this->m_pTexture->GetD3DTexture(),
		{ vPos.x, vPos.y },
		{ vPos.x + vSize.x, vPos.y + vSize.y }
	);
}
