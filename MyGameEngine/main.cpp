#include <cstdio>
#include <iostream>
#include <thread>
#include "CWindow.h"
#include "CRender.h"
#include "CDebugConsole.h"
#include "CFileExplorer.h"
#include "CFileManager.h"
#include "CBaseComponents.h"

LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    switch (uMsg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_pRender->SetRenderSize((UINT)LOWORD(lParam), (UINT)HIWORD(lParam));
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    case WM_LBUTTONUP:
        break;
    case WM_RBUTTONUP:
        break;
    case WM_MBUTTONUP:
        break;
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_KEYDOWN:
    case WM_KEYUP:
    {
        bool bDown = (uMsg == WM_SYSKEYDOWN || uMsg == WM_KEYDOWN);
        int	iKey = (int)wParam;
        unsigned int ScanCode = LOBYTE(HIWORD(lParam));

        break;
    }
default: ;
    }

    return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}
int WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nShowCmd
)
{
    g_pRender = new CRender();
    g_pWindow = new CWindow();
    g_pDebugConsole = new CDebugConsole();

    std::locale::global(std::locale("ru_RU.UTF-8"));

    g_pWindow->CreateHWND(WndProc);
    if (!g_pRender->CreateDeviceD3D(g_pWindow->GetHWND())) {
        g_pRender->CleanupDeviceD3D();
        g_pWindow->Unregister();
        return 1;
    }

    g_pFileExplorer = new CFileExplorer();
    g_pFileManager = new CFileManager();
    g_pBaseComponents = new CBaseComponents();

    g_pWindow->Show();

    g_pRender->InitImGui(g_pWindow->GetHWND());

    g_pRender->Render();

    g_pRender->DestroyImGui();
    g_pRender->CleanupDeviceD3D();
    g_pWindow->Destroy();

#if _DEBUG
    FreeConsole();
#endif
    return 0;
}