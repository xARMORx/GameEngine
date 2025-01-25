#include "CWindow.h"
#include "CLog.h"

CWindow* g_pWindow = { nullptr };

CWindow::CWindow()
{
	this->m_hWnd = { nullptr };
	this->m_tWindowClass = {};
}

void CWindow::CreateHWND(WNDPROC wndProc)
{
	this->m_tWindowClass = {
		sizeof(m_tWindowClass),
		CS_CLASSDC,
		wndProc,
		0L,
		0L,
		GetModuleHandle(nullptr),
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		L"ImGui Example",
		nullptr
	};
	::RegisterClassExW(&m_tWindowClass);
	this->m_hWnd = ::CreateWindowW(m_tWindowClass.lpszClassName, L"GameEngine", WS_OVERLAPPEDWINDOW, 0, 0, 1920, 1080, nullptr, nullptr, m_tWindowClass.hInstance, nullptr);
	if (this->m_hWnd)	
	{
		CLog::AddMessage(DEBUG_MESSAGE, "hWnd created: 0x%llX", this->m_hWnd);
	}
	else
	{
		CLog::AddMessage(ERROR_MESSAGE, "hWnd isn't created!");
	}
}

void CWindow::Show()
{
	::ShowWindow(this->m_hWnd, SW_SHOWMAXIMIZED);
	::UpdateWindow(this->m_hWnd);
}

void CWindow::Destroy()
{
	::DestroyWindow(this->m_hWnd);
    ::UnregisterClassW(this->m_tWindowClass.lpszClassName, this->m_tWindowClass.hInstance);
}

void CWindow::Unregister()
{
	::UnregisterClassW(this->m_tWindowClass.lpszClassName, this->m_tWindowClass.hInstance);
}

CVector2d CWindow::GetWindowSize()
{
	RECT rect;
	GetWindowRect(m_hWnd, &rect);
	return { static_cast<float>(rect.right), static_cast<float>(rect.bottom) };
}

HWND CWindow::GetHWND()
{
	return this->m_hWnd;
}
