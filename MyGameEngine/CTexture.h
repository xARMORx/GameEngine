#pragma once
#include "CRender.h"
#include "CVector2d.h"

class CTexture
{
private:
	CVector2d m_vSize;
	LPDIRECT3DTEXTURE9 m_pD3DTexture;
public:
	CTexture();
	CTexture(LPDIRECT3DTEXTURE9 pD3DTexture, CVector2d vSize = {256.f, 256.f});
	void SetD3DTexture(LPDIRECT3DTEXTURE9 pD3DTexture);
	CVector2d& GetSize();
	void SetSize(const CVector2d& vSize);
	LPDIRECT3DTEXTURE9 GetD3DTexture();


};
