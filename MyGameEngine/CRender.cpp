#include "CRender.h"

#include <string>

#include "CLog.h"
#include "CTexture.h"
#include "CVector2d.h"

CRender* g_pRender = nullptr;

CRender::CRender() {
	this->m_pDirect3D9 = { nullptr };
	this->m_pDevice = { nullptr };
	this->m_bDeviceLost = { false };
	this->m_nResizeWidth = { 0 };
	this->m_nResizeHeight = { 0 };
	this->m_tD3DParametrs = {};
	this->m_nBackgroundColor = { 0xFFFFFFFF };
    this->m_pFileExplorer = new CFileManager();
}

bool CRender::CreateDeviceD3D(HWND hWnd) {
    HRESULT hError = { 0 };
    if ((this->m_pDirect3D9 = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
        return false;
    CLog::AddMessage(DEBUG_MESSAGE, "pDirect3D9 created: 0x%llX", this->m_pDirect3D9);

    ZeroMemory(&this->m_tD3DParametrs, sizeof(this->m_tD3DParametrs));
    this->m_tD3DParametrs.Windowed = TRUE;
    this->m_tD3DParametrs.SwapEffect = D3DSWAPEFFECT_DISCARD;
    this->m_tD3DParametrs.BackBufferFormat = D3DFMT_UNKNOWN;
    this->m_tD3DParametrs.EnableAutoDepthStencil = TRUE;
    this->m_tD3DParametrs.AutoDepthStencilFormat = D3DFMT_D16;
    this->m_tD3DParametrs.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    hError = this->m_pDirect3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &this->m_tD3DParametrs, &this->m_pDevice);
    if (!this->m_pDevice)
    {
        CLog::AddMessage(ERROR_MESSAGE, "pDevice isn't created!");
        return false;
    }

    CLog::AddMessage(DEBUG_MESSAGE, "pDevice created: 0x%llX", this->m_pDevice);
    return true;
}

void CRender::CleanupDeviceD3D() {
    if (this->m_pDevice) { this->m_pDevice->Release(); this->m_pDevice = nullptr; }
    if (this->m_pDirect3D9) { this->m_pDirect3D9->Release(); this->m_pDirect3D9 = nullptr; }
}

void CRender::ResetDevice() {
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = this->m_pDevice->Reset(&this->m_tD3DParametrs);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}
void CRender::Begin() {
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    this->Draw();
}

void CRender::Draw()
{
    if (m_pFileExplorer->IsOpened())
    {
        m_pFileExplorer->Draw();
    }
    ImGuiIO& io = ImGui::GetIO();
    
    ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
    ImGui::SetNextWindowSize({ static_cast<float>(this->m_tD3DParametrs.BackBufferWidth), static_cast<float>(this->m_tD3DParametrs.BackBufferHeight) });
    ImGui::Begin("Window", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar );
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open"))
            {
                m_pFileExplorer->Open();
                CLog::AddMessage(DEBUG_MESSAGE, "You click on Open");
            }
            if (ImGui::MenuItem("Close"))
                CLog::AddMessage(DEBUG_MESSAGE, "You click on Close");
            if (ImGui::MenuItem("Save"))
                CLog::AddMessage(DEBUG_MESSAGE, "You click on Save");
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Copy"))
                CLog::AddMessage(DEBUG_MESSAGE, "You click on Copy");
            if (ImGui::MenuItem("Paste"))
                CLog::AddMessage(DEBUG_MESSAGE, "You click on Paste");
            if (ImGui::MenuItem("Settings"))
                CLog::AddMessage(DEBUG_MESSAGE, "You click on Settings");
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
    float fMenuBarHeight = ImGui::GetItemRectSize().y;
    ImVec2 vWindowSize = ImGui::GetWindowSize();

    ImGui::SetCursorPos({0.f, fMenuBarHeight});
    ImGui::BeginChild("Base components", ImVec2(vWindowSize.x * 0.2083f, (vWindowSize.y * 0.6296f) - fMenuBarHeight), ImGuiChildFlags_Border);
    ImGui::Text("Base components");
    ImGui::EndChild();

    ImGui::SetCursorPos({ vWindowSize.x * 0.7916f, fMenuBarHeight });
    ImGui::BeginChild("ComponentSettings", ImVec2(vWindowSize.x * 0.2093f, (vWindowSize.y * 0.6296f) - fMenuBarHeight), ImGuiChildFlags_Border);
    ImGui::Text("ComponentSettings");
    ImGui::EndChild();

    ImGui::SetCursorPos({ vWindowSize.x * 0.2083f, fMenuBarHeight });
    ImGui::BeginChild("ViewPort", ImVec2(vWindowSize.x * 0.5838f, (vWindowSize.y * 0.6296f) - fMenuBarHeight), ImGuiChildFlags_Border);
    ImGui::Text("ViewPort");
    ImGui::EndChild();

    ImGui::SetCursorPos({ 0.f, (vWindowSize.y * 0.6296f) });
    ImGui::BeginChild("File Explorer", ImVec2(vWindowSize.x, (vWindowSize.y) - (vWindowSize.y * 0.6290f)), ImGuiChildFlags_Border);
    ImGui::Text("File Explorer");
    ImGui::EndChild();

    ImGui::End();
}

bool CRender::IsWantResize() const
{
    return this->m_nResizeWidth != 0 && this->m_nResizeHeight != 0;
}

void CRender::Resize() {
    this->m_tD3DParametrs.BackBufferWidth = this->m_nResizeWidth;
    this->m_tD3DParametrs.BackBufferHeight = this->m_nResizeHeight;
    this->m_nResizeWidth = this->m_nResizeHeight = 0;
    ResetDevice();
}

LPDIRECT3D9 CRender::GetDirect3D() const
{
    return this->m_pDirect3D9;
}

LPDIRECT3DDEVICE9 CRender::GetDevice() const
{
    return this->m_pDevice;
}

void CRender::Render()
{
    bool done = false;

    while (!done)
    {
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        if (this->IsLoss())
        {
            HRESULT hr = this->GetDevice()->TestCooperativeLevel();
            if (hr == D3DERR_DEVICELOST)
            {
                ::Sleep(10);
                continue;
            }
            if (hr == D3DERR_DEVICENOTRESET)
                this->ResetDevice();
            this->SetLoss(false);
        }

        if (this->IsWantResize()) {
            this->Resize();
        }

        this->Begin();

        this->End();
    }
}

bool CRender::IsLoss() const
{
    return this->m_bDeviceLost;
}

void CRender::SetLoss(bool bLoss)
{
    this->m_bDeviceLost = bLoss;
}

void CRender::SetRenderSize(unsigned int nWidth, unsigned int nHeight)
{
    this->m_nResizeWidth = nWidth;
    this->m_nResizeHeight = nHeight;
}

void CRender::SetBackgroundColor(D3DCOLOR nColor)
{
    this->m_nBackgroundColor = nColor;
}

void CRender::End() {
    ImGui::EndFrame();
    this->m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    this->m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    this->m_pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
    this->m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, this->m_nBackgroundColor, 1.0f, 0);
    if (this->m_pDevice->BeginScene() >= 0)
    {
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        this->m_pDevice->EndScene();
    }
    HRESULT result = this->m_pDevice->Present(nullptr, nullptr, nullptr, nullptr);
    if (result == D3DERR_DEVICELOST)
        this->m_bDeviceLost = true;
}

void CRender::InitImGui(HWND hWnd) const
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.IniFilename = nullptr;

    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.84f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
    colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowBorderSize = 0;

#pragma warning(disable: 4996)
    std::string fontPath{ getenv("WINDIR") }; fontPath += "\\Fonts\\trebucbd.ttf";
#pragma warning(default: 4996)
    ImGui::GetIO().Fonts->AddFontFromFileTTF(fontPath.c_str(), 14.0f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX9_Init(this->m_pDevice);
    ImGui_ImplWin32_EnableAlphaCompositing(hWnd);
}

void CRender::DestroyImGui() {
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}