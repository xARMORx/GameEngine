#include "CTexture.h"

CTexture::CTexture()
{
	this->m_vSize = { 0.f, 0.f };
	this->m_pD3DTexture = { nullptr };
}

CTexture::CTexture(LPDIRECT3DTEXTURE9 pD3DTexture, CVector2d vSize)
{
}

void CTexture::SetD3DTexture(LPDIRECT3DTEXTURE9 pD3DTexture)
{
	this->m_pD3DTexture = pD3DTexture;
}

CVector2d& CTexture::GetSize()
{
	return this->m_vSize;
}

void CTexture::SetSize(const CVector2d& vSize)
{
	this->m_vSize = vSize;
}

LPDIRECT3DTEXTURE9 CTexture::GetD3DTexture()
{
	return this->m_pD3DTexture;
}