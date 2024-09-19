#pragma once
#include "../../include.hpp"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx9.h"
#include "../../imgui/imgui_impl_win32.h"
#include "../visuals/renderer.hpp"
#include "../visuals/visuals.hpp"
#include "../aimbot/aimbot.hpp"

IDirect3D9Ex* p_object = NULL;
IDirect3DDevice9Ex* p_device = NULL;
D3DPRESENT_PARAMETERS p_params = { NULL };
MSG messager = { NULL };
HWND my_wnd = NULL;
HWND game_wnd = NULL;

HRESULT init_directx()
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_object)))
	{
		exit(3);
	}

	ZeroMemory(&p_params, sizeof(p_params));
	p_params.Windowed = TRUE;
	p_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_params.hDeviceWindow = my_wnd;
	p_params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_params.BackBufferWidth = settings::width;
	p_params.BackBufferHeight = settings::height;
	p_params.EnableAutoDepthStencil = TRUE;
	p_params.AutoDepthStencilFormat = D3DFMT_D16;
	if (settings::vsync)
	{
		p_params.PresentationInterval = 1;
	}
	else
	{
		p_params.PresentationInterval = 0;
	}

	if (FAILED(p_object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, my_wnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_params, 0, &p_device)))
	{
		p_object->Release();
		exit(4);
	}

	ImGui::CreateContext();
	ImGui_ImplWin32_Init(my_wnd);
	ImGui_ImplDX9_Init(p_device);

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = nullptr;

	ImFontAtlas* fontAtlas = io.Fonts;
	ImFontConfig arialConfig;
	arialConfig.FontDataOwnedByAtlas = false;
	ImFont* arialFont = fontAtlas->AddFontFromFileTTF("c:\\Windows\\Fonts\\impact.ttf", 15.0f, &arialConfig);
	io.Fonts = fontAtlas;

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowTitleAlign = { 0.5f, 0.5f };
	style.WindowRounding = 5.0f;
	style.WindowBorderSize = 0.0f;
	style.FrameBorderSize = 0.0f;
	style.PopupBorderSize = 0.0f;
	style.FrameRounding = 2.0f;
	style.WindowPadding = { 10.0f, 10.0f };
	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.2745098173618317f, 0.3176470696926117f, 0.4509803950786591f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5372549295425415f, 0.5529412031173706f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.5215686559677124f, 0.6000000238418579f, 0.7019608020782471f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.03921568766236305f, 0.9803921580314636f, 0.9803921580314636f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.2901960909366608f, 0.5960784554481506f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.9960784316062927f, 0.4745098054409027f, 0.6980392336845398f, 1.0f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);

	p_object->Release();
	return S_OK;
}

void create_overlay()
{
	WNDCLASSEXA wcex = {
		sizeof(WNDCLASSEXA),
		0,
		DefWindowProcA,
		0,
		0,
		0,
		LoadIcon(0, IDI_APPLICATION),
		LoadCursor(0, IDC_ARROW),
		0,
		0,
		"thunder",
		LoadIcon(0, IDI_APPLICATION)
	};
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	RegisterClassExA(&wcex);
	my_wnd = CreateWindowExA(0, "thunder", "lol", WS_POPUP, rect.left, rect.top, rect.right, rect.bottom, 0, 0, wcex.hInstance, 0);
	SetWindowLong(my_wnd, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
	MARGINS margin = { -1 };
	DwmExtendFrameIntoClientArea(my_wnd, &margin);
	ShowWindow(my_wnd, SW_SHOW);
	SetWindowPos(my_wnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetLayeredWindowAttributes(my_wnd, RGB(0, 0, 0), 255, LWA_ALPHA);
	UpdateWindow(my_wnd);
}

void features()
{
	if (settings::aim && input::getasynckeystate(settings::current_key))
	{
		aimbot(cache::closest_mesh);
	}
	if (settings::silent_aim && input::getasynckeystate(settings::current_key))
	{
		sticky_silent_aim(cache::closest_mesh);
	}
	if (settings::show_fov)
	{
		ImGui::GetForegroundDrawList()->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), settings::fov, ImColor(0, 0, 0), 100, 2.0f);
		ImGui::GetForegroundDrawList()->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), settings::fov, ImColor(255, 255, 255), 100, 1.0f);
	}

	cache_loop();
	actor_loop();

	if (settings::spinbot)
	{
		auto local_mesh = read<uint64_t>(cache::local_pawn + MESH);
		static auto cached = read<Vector3>(local_mesh + 0x138);

		if (input::getasynckeystate(settings::current_key))
		{
			write<Vector3>(local_mesh + 0x138, Vector3(1, rand() % 361, 1));
		}
		else
		{
			write<Vector3>(local_mesh + 0x138, cached);
		}
	}

	if (settings::crosshair)
	{
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(GetSystemMetrics(0) / 2 - 4, GetSystemMetrics(1) / 2), ImVec2(GetSystemMetrics(0) / 2 + 4, GetSystemMetrics(1) / 2), ImColor(0, 0, 0), 2.0f);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2 - 4), ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2 + 4), ImColor(0, 0, 0), 2.0f);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(GetSystemMetrics(0) / 2 - 4, GetSystemMetrics(1) / 2), ImVec2(GetSystemMetrics(0) / 2 + 4, GetSystemMetrics(1) / 2), ImColor(255, 255, 255), 1.0f);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2 - 4), ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2 + 4), ImColor(255, 255, 255), 1.0f);
	}
}

void render_tabs(int& current_tab, const char* tabs[], int num_of_tabs)
{
	float tabWidth = (ImGui::GetContentRegionAvail().x - (ImGui::GetStyle().FramePadding.x) * (num_of_tabs)-ImGui::GetStyle().WindowPadding.x) / num_of_tabs;

	for (int i = 0; i < num_of_tabs; ++i)
	{
		bool isActive = (current_tab == i);

		if (isActive)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 0.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(155, 155, 155, 255));
		}

		if (ImGui::Button(tabs[i], ImVec2(tabWidth, 30)))
		{
			current_tab = i;
		}

		ImGui::PopStyleColor(4);

		ImGui::SameLine();
	}
}

void render_gui()
{
	switch (settings::current_aimkey)
	{
	case 0:
		settings::current_key = VK_LBUTTON;
		break;
	case 1:
		settings::current_key = VK_RBUTTON;
		break;
	case 2:
		settings::current_key = VK_XBUTTON1;
		break;
	case 3:
		settings::current_key = VK_XBUTTON2;
		break;
	case 4:
		settings::current_key = VK_SHIFT;
		break;
	case 5:
		settings::current_key = VK_CONTROL;
		break;
	case 6:
		settings::current_key = VK_MENU;
		break;
	case 7:
		settings::current_key = VK_CAPITAL;
		break;
	default:
		settings::current_key = VK_LBUTTON;
		break;
	}

	if (settings::watermark)
	{
		std::string fpsText = "thunder paid | " + std::to_string(static_cast<int>(ImGui::GetIO().Framerate)) + " FPS";
		watermark(ImGui::GetFont(), 13.0f, ImVec2(10.0f, 10.0f), ImColor(255, 255, 255), fpsText.c_str());
		watermark(ImGui::GetFont(), 13.0f, ImVec2(10.0f, 25.0f), ImColor(255, 255, 255), "https://discord.gg/rsGNnPNVTh");
	}

	if (input::getasynckeystate(VK_INSERT) & 1) settings::show_menu = !settings::show_menu;
	if (settings::show_menu)
	{
		ImGui::SetNextWindowSize({ 600.0f, 420.0f });
		ImGui::Begin("##", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
		{
			ImGui::BeginGroup();
			{
				ImGui::TextColored(ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f), "|");
				ImGui::SameLine();
				ImGui::Text("thunder paid");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f), "|");
				ImGui::SameLine(0, -5.0f);
				render_tabs(settings::tab, settings::tabs, sizeof(settings::tabs) / sizeof(settings::tabs[0]));
			}
			ImGui::EndGroup();
			ImGui::Dummy(ImVec2(0, 5.0f));
			ImGui::Separator();
			ImGui::Dummy(ImVec2(0, 5.0f));
			ImGui::BeginGroup();
			{
				float windowWidth = ImGui::GetContentRegionAvail().x - ImGui::GetStyle().WindowPadding.x;

				if (settings::tab == 0)
				{
					ImGui::BeginChild("##aimbot", ImVec2(windowWidth / 2, 0), false);
					{
						ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(155, 155, 155, 255));
						float textWidth = ImGui::CalcTextSize("Aimbot").x;
						float availWidth = ImGui::GetContentRegionAvail().x;
						ImGui::SetCursorPosX((availWidth - textWidth) * 0.5f);
						ImGui::Text("Aimbot");
						ImGui::PopStyleColor();
						ImGui::Dummy(ImVec2(0, 5.0f));
						ImGui::Checkbox("Mouse Aim", &settings::aim);
						ImGui::Checkbox("Sticky Silent Aim (Risky)", &settings::silent_aim);
						ImGui::Checkbox("Trigger Bot", &settings::trigger_bot);
					}
					ImGui::EndChild();
					ImGui::SameLine();
					ImGui::BeginChild("##aimbot_settings", ImVec2(windowWidth / 2, 0), false);
					{
						ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(155, 155, 155, 255));
						float textWidth = ImGui::CalcTextSize("Aimbot Settings").x;
						float availWidth = ImGui::GetContentRegionAvail().x;
						ImGui::SetCursorPosX((availWidth - textWidth) * 0.5f);
						ImGui::Text("Aimbot Settings");
						ImGui::PopStyleColor();
						ImGui::Dummy(ImVec2(0, 5.0f));
						ImGui::Checkbox("Visible Check", &settings::aim_visible_check);
						ImGui::Checkbox("Prediction", &settings::prediction);
						ImGui::Checkbox("FOV Circle", &settings::show_fov);
						ImGui::SliderFloat("FOV", &settings::fov, 10, 420, "%.f");
						ImGui::SliderFloat("Smoothing", &settings::smoothing, 1, 30, "%.f");
						ImGui::Combo("Aimkey", &settings::current_aimkey, settings::aimkey, sizeof(settings::aimkey) / sizeof(*settings::aimkey));
						if (ImGui::BeginCombo("Bone", get_bone_type_name(settings::bone)))
						{
							for (auto boneType : boneValues)
							{
								if (ImGui::Selectable(get_bone_type_name(boneType), settings::bone == boneType)) settings::bone = boneType;
							}
						}
						ImGui::EndCombo();
					}
					ImGui::EndChild();
				}
				if (settings::tab == 1)
				{
					ImGui::BeginChild("##visuals", ImVec2(windowWidth / 2, 0), false);
					{
						ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(155, 155, 155, 255));
						float textWidth = ImGui::CalcTextSize("Visuals").x;
						float availWidth = ImGui::GetContentRegionAvail().x;
						ImGui::SetCursorPosX((availWidth - textWidth) * 0.5f);
						ImGui::Text("Visuals");
						ImGui::PopStyleColor();
						ImGui::Dummy(ImVec2(0, 5.0f));
						ImGui::Checkbox("Box", &settings::box);
						ImGui::Checkbox("Skeleton", &settings::skeleton);
						ImGui::Checkbox("Platform", &settings::platform);
						ImGui::Checkbox("Username", &settings::username);
						ImGui::Checkbox("Distance", &settings::distance);
						ImGui::Checkbox("Weapon", &settings::weapon);
						ImGui::Checkbox("Aim Line", &settings::aim_line);
						ImGui::Checkbox("Indication Arrows", &settings::indication_arrows);
						ImGui::Checkbox("Radar", &settings::radar);
					}
					ImGui::EndChild();
					ImGui::SameLine();
					ImGui::BeginChild("##visuals_settings", ImVec2(windowWidth / 2, 0), false);
					{
						ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(155, 155, 155, 255));
						float textWidth = ImGui::CalcTextSize("Visuals Settings").x;
						float availWidth = ImGui::GetContentRegionAvail().x;
						ImGui::SetCursorPosX((availWidth - textWidth) * 0.5f);
						ImGui::Text("Visuals Settings");
						ImGui::PopStyleColor();
						ImGui::Dummy(ImVec2(0, 5.0f));
						ImGui::Checkbox("Fill Box", &settings::fill_box);
						ImGui::Checkbox("Outline", &settings::outline);
						ImGui::SliderFloat("Thickness", &settings::thickness, 1, 5, "%.f");
						if (ImGui::BeginCombo("Box Type", get_box_type_name(settings::box_type)))
						{
							for (auto boxType : boxValues)
							{
								if (ImGui::Selectable(get_box_type_name(boxType), settings::box_type == boxType)) settings::box_type = boxType;
							}
						}
						ImGui::EndCombo();
					}
					ImGui::EndChild();
				}
				if (settings::tab == 2)
				{
					ImGui::BeginChild("##exploits", {}, false);
					{
						ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(155, 155, 155, 255));
						float textWidth = ImGui::CalcTextSize("Exploits").x;
						float availWidth = ImGui::GetContentRegionAvail().x;
						ImGui::SetCursorPosX((availWidth - textWidth) * 0.5f);
						ImGui::Text("Exploits");
						ImGui::PopStyleColor();
						ImGui::Dummy(ImVec2(0, 5.0f));
						ImGui::Checkbox("Spinbot (Aim Key) (Risky)", &settings::spinbot);
					}
					ImGui::EndChild();
				}
				if (settings::tab == 3)
				{
					ImGui::BeginChild("##misc", {}, false);
					{
						ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(155, 155, 155, 255));
						float textWidth = ImGui::CalcTextSize("Misc").x;
						float availWidth = ImGui::GetContentRegionAvail().x;
						ImGui::SetCursorPosX((availWidth - textWidth) * 0.5f);
						ImGui::Text("Misc");
						ImGui::PopStyleColor();
						ImGui::Dummy(ImVec2(0, 5.0f));
						ImGui::Checkbox("Watermark", &settings::watermark);
						ImGui::Checkbox("Crosshair", &settings::crosshair);
						ImGui::Checkbox("V-Sync", &settings::vsync);
					}
					ImGui::EndChild();
				}
				if (settings::tab == 4)
				{
					ImGui::Text("thunder was developed by ");
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f), "remz and skidmade");
					ImGui::Text("Last updated:");
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f), __DATE__);
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f), __TIME__);

					if (ImGui::Button("Save Config", ImVec2(ImGui::GetContentRegionAvail().x / 2, 20)))
					{
						save_config("thunder.json");
					}
					ImGui::SameLine();
					if (ImGui::Button("Load Config", ImVec2(ImGui::GetContentRegionAvail().x, 20)))
					{
						load_config("thunder.json");
					}
				}
			}
			ImGui::EndGroup();
		}
		ImGui::End();
	}
}

WPARAM render_loop()
{
	static RECT old_rc;

	bool running = true;
	while (running)
	{
		while (PeekMessage(&messager, my_wnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&messager);
			DispatchMessage(&messager);

			if (messager.message == WM_QUIT)
			{
				running = false;
			}
		}

		if (!running) break;

		HWND active_wnd = GetForegroundWindow();
		if (active_wnd == game_wnd)
		{
			HWND target_wnd = GetWindow(active_wnd, GW_HWNDPREV);
			SetWindowPos(my_wnd, target_wnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		RECT rc;
		POINT xy;
		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(game_wnd, &rc);
		ClientToScreen(game_wnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = game_wnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(0x1))
		{
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
		{
			io.MouseDown[0] = false;
		}

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;
			settings::width = rc.right;
			settings::height = rc.bottom;
			p_params.BackBufferWidth = settings::width;
			p_params.BackBufferHeight = settings::height;
			SetWindowPos(my_wnd, (HWND)0, xy.x, xy.y, settings::width, settings::height, SWP_NOREDRAW);
			p_device->Reset(&p_params);
		}

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		{
			features();
			render_gui();
		}
		ImGui::EndFrame();

		p_device->SetRenderState(D3DRS_ZENABLE, false);
		p_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		p_device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
		p_device->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

		if (p_device->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			p_device->EndScene();
		}

		HRESULT result = p_device->Present(0, 0, 0, 0);
		if (result == D3DERR_DEVICELOST && p_device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			p_device->Reset(&p_params);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (p_device != 0)
	{
		p_device->EndScene();
		p_device->Release();
	}

	if (p_object != 0)
	{
		p_object->Release();
	}

	DestroyWindow(my_wnd);

	return messager.wParam;
}
