#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <D3DX11.h>
#include <dxgi.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

#include "kiero/kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

#include "CodClass.h"
#include "W2S.h"
#include "Draw.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

namespace opt{
	namespace frn {
		float color[3];
		bool lines;
		bool Box2D;
		bool Box3D;
		bool Name;
		bool Health;
	}
	namespace enm {
		float color[3];
		bool lines;
		bool Box2D;
		bool Box3D;
		bool Name;
		bool Health;
	}
	float Fov = 65.f;
}

void HackLoop() {
	DWORD EntList = *(DWORD*)0x235E7E4;

	Entity* LocalPlayer = (Entity*)(0x234B808 + ClientGS->ClientNum * 0x808);

	for (int i = 0; i < 20; i++) {
		EntityInfo* EntInf = (EntityInfo*)(EntList + i * 0x31C);
		Entity* Ent = (Entity*)(0x234B808 + EntInf->PlayerId * 0x808);

		Vec3 HeadPos = Vec3{ EntInf->Position.x,  EntInf->Position.y, EntInf->HeadPos.z };

		if (EntInf->Health <= 0) { continue; }

		if (Ent->Team == LocalPlayer->Team) {
			if (opt::frn::Box2D) {
				Draw::Draw2DBox(HeadPos, EntInf->Position, ImColor{ opt::frn::color[0], opt::frn::color[1], opt::frn::color[2], 255.f });
			}
			if (opt::frn::Box3D) {
				Draw::Draw3DBox(HeadPos, EntInf->Position, ImColor{ opt::frn::color[0], opt::frn::color[1], opt::frn::color[2], 255.f });
			}
			if (opt::frn::Name) {
				Draw::DrawName(HeadPos, ImColor{ opt::frn::color[0], opt::frn::color[1], opt::frn::color[2], 255.f }, Ent->Name);
			}
			if (opt::frn::lines) {
				Draw::DrawTopSnapLine(HeadPos, ImColor{ opt::frn::color[0], opt::frn::color[1], opt::frn::color[2], 255.f });
			}
			if (opt::frn::Health) {
				Draw::DrawHealth(HeadPos, EntInf->Position, EntInf->Health);
			}
		}
		else {
			if (opt::enm::Box2D) {
				Draw::Draw2DBox(HeadPos, EntInf->Position, ImColor{ opt::enm::color[0], opt::enm::color[1], opt::enm::color[2], 255.f });
			}
			if (opt::enm::Box3D) {
				Draw::Draw3DBox(HeadPos, EntInf->Position, ImColor{ opt::enm::color[0], opt::enm::color[1], opt::enm::color[2], 255.f });
			}
			if (opt::enm::Name) {
				Draw::DrawName(HeadPos, ImColor{ opt::enm::color[0], opt::enm::color[1], opt::enm::color[2], 255.f }, Ent->Name);
			}
			if (opt::enm::lines) {
				Draw::DrawBottomSnapLine(EntInf->Position, ImColor{ opt::enm::color[0], opt::enm::color[1], opt::enm::color[2], 255.f });
			}
			if (opt::enm::Health) {
				Draw::DrawHealth(HeadPos, EntInf->Position, EntInf->Health);
			}
		}
	}
}

#define AOC_PURPLE 0.549, 0.011, 0.988, 1.f
#define AOC_DARKPURPLE 0.219, 0.035, 0.286, 1.f
#define AOC_BLACK 0.078, 0.078, 0.078, 0.8f
#define AOC_WHITE 1, 1, 1, 1.f

void Style() {
	ImGui::GetStyle().ScaleAllSizes(1);
	ImGui::GetIO().FontGlobalScale = 1;
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowTitleAlign = ImVec2(0.45, 0.5);
	style->WindowPadding = ImVec2(15, 5);
	style->WindowRounding = 8.f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 8.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 20.f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 0.f;
	style->Colors[ImGuiCol_Text] = ImColor(255,255,255);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_Border] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(AOC_WHITE);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_Button] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_Header] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImColor(AOC_BLACK);
	style->Colors[ImGuiCol_TabUnfocused] = ImColor(AOC_BLACK);
	style->Colors[ImGuiCol_TabUnfocusedActive] = ImColor(AOC_BLACK);
}

bool init = false, show = true;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	if (!init) {
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice))) {
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
			io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Arial.ttf", 15.f, NULL, io.Fonts->GetGlyphRangesJapanese());
			ImGui_ImplWin32_Init(window);
			ImGui_ImplDX11_Init(pDevice, pContext);
			init = true;
		}
		else {
			return oPresent(pSwapChain, SyncInterval, Flags);
		}
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	Style();
	if (show) {
		char Name[12];
		memcpy(Name, (void*)0x2C23194, sizeof(Name));
		ImGui::Begin("Art of Cheats [Plutonium ESP]", 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse);
		ImGui::Text("Welcome: %s", Name);
		ImGui::Separator();
		ImGui::Text("Friendly");
		ImGui::BeginChild("Friendlies", ImVec2{ 300,200 }, true);
		{
			ImGui::Checkbox("Box 2D", &opt::frn::Box2D);
			ImGui::Checkbox("Box 3D", &opt::frn::Box3D);
			ImGui::Checkbox("Snap Lines", &opt::frn::lines);
			ImGui::Checkbox("Name", &opt::frn::Name);
			ImGui::Checkbox("Health", &opt::frn::Health);
			ImGui::ColorEdit3("Color", opt::frn::color);
		}
		ImGui::EndChild();
		ImGui::Text("Enemy");
		ImGui::BeginChild("Enemy", ImVec2{ 300,200 }, true);
		{
			ImGui::Checkbox("Box 2D", &opt::enm::Box2D);
			ImGui::Checkbox("Box 3D", &opt::enm::Box3D);
			ImGui::Checkbox("Snap Lines", &opt::enm::lines);
			ImGui::Checkbox("Name", &opt::enm::Name);
			ImGui::Checkbox("Health", &opt::enm::Health);
			ImGui::ColorEdit3("Color", opt::enm::color);
		}
		ImGui::EndChild();
		ImGui::Spacing();
		ImGui::End();
	}

	//if (ClientGS->isInGame) {
	HackLoop();
	//}

	ImGui::Render();

	if (GetAsyncKeyState(VK_INSERT) & 1) { show = !show; }

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved){
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved){
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}
