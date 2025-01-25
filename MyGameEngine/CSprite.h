#pragma once
#include "CRender.h"
#include "CComponent.h"
#include "CTexture.h"

class CSprite : public CComponent
{
	CVector2d m_vPos;
	CVector2d m_vSize;
	CTexture* m_pTexture;
public:
	CSprite();
	CSprite(CTexture* pTexture, CVector2d vPos = {0.f, 0.f}, CVector2d vSize = {256.f, 256.f});
	void SetTexture(CTexture* pTexture);
	void SetTexture(LPDIRECT3DTEXTURE9 pD3DTexture, CVector2d vSize);
	void SetSize(const CVector2d& vSize);
	CVector2d& GetSize();
	void Draw();
	void Draw(const CVector2d& vPos, const CVector2d& vSize);
};

