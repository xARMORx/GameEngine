#include <cstdio>
#include <iostream>
#include <thread>
#include "CWindow.h"
#include "CRender.h"

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
#if _DEBUG
    if (!AllocConsole())
    {
        std::cerr << "Failed to allocate console!" << std::endl;
        return 1;
    }

    std::locale::global(std::locale("ru_RU.UTF-8"));

    SetConsoleOutputCP(CP_UTF8);

    FILE* pFile;
    if (freopen_s(&pFile, "CONOUT$", "w", stdout) != 0 || freopen_s(&pFile, "CONOUT$", "w", stderr) != 0)
    {
        std::cerr << "Failed to redirect stdout or stderr!" << std::endl;
        return 1;
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Failed to get console handle!" << std::endl;
        return 1;
    }

    DWORD dwMode;
    if (!GetConsoleMode(hConsole, &dwMode))
    {
        std::cerr << "Failed to get console mode!" << std::endl;
        return 1;
    }
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hConsole, dwMode))
    {
        std::cerr << "Failed to set console mode!" << std::endl;
        return 1;
    }


#endif

    g_pRender = new CRender();
    g_pWindow = new CWindow();

    g_pWindow->CreateHWND(WndProc);
    if (!g_pRender->CreateDeviceD3D(g_pWindow->GetHWND())) {
        g_pRender->CleanupDeviceD3D();
        g_pWindow->Unregister();
        return 1;
    }

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