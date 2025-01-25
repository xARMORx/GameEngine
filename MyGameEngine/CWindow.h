#pragma once
#ifndef _WINDOW_H_
#define _WINDOW_H_
#include <Windows.h>
#include "CVector2d.h"

class CWindow
{
private:
	HWND m_hWnd;
	WNDCLASSEXW m_tWindowClass;
public:
	CWindow();
	void CreateHWND(WNDPROC wndProc);
	void Show();
	void Destroy();
	void Unregister();
	CVector2d GetWindowSize();
	HWND GetHWND();
};

extern CWindow* g_pWindow;

#endif // _WINDOW_H_