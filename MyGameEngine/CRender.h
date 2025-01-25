#pragma once
#ifndef _RENDER_H_
#define _RENDER_H_
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui_internal.h"
#include "imgui_stdlib.h"
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include "CFileManager.h"
#include "CFileExplorer.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class CRender
{
private:
	LPDIRECT3D9 m_pDirect3D9;
	LPDIRECT3DDEVICE9 m_pDevice;
	bool m_bDeviceLost;
	unsigned int m_nResizeWidth;
	unsigned int m_nResizeHeight;
	D3DPRESENT_PARAMETERS m_tD3DParametrs;
	D3DCOLOR m_nBackgroundColor;
	CFileManager* m_pFileManager;
	CFileExplorer* m_pFileExporer;
public:
	CRender();

	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
	void ResetDevice();
	bool IsWantResize() const;
	void Resize();
	LPDIRECT3D9 GetDirect3D() const;
	LPDIRECT3DDEVICE9 GetDevice() const;
	void Render();

	bool IsLoss() const;
	void SetLoss(bool bLoss);
	void SetRenderSize(unsigned int nWidth, unsigned int nHeight);
	void SetBackgroundColor(D3DCOLOR nColor);

	void Begin();
	void Draw();
	void End();
	void InitImGui(HWND hWnd) const;
	void DestroyImGui();
};

extern CRender* g_pRender;

#endif // _RENDER_H_