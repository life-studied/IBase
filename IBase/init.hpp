#include "GL/glew.h"
#include "GLFW/glfw3.h"

#pragma comment(lib, "../3rdparty/lib/glew32.lib")
#pragma comment(lib, "../3rdparty/lib/glfw3.lib")
#pragma comment(lib, "../3rdparty/lib/jsoncpp.lib")
#pragma comment(lib, "../3rdparty/lib/libmysql.lib")
#pragma comment(lib, "Opengl32.lib")
#pragma comment(linker, "/subsystem:windows")


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "WinRoaming/Window.h"
#include "LoginWindow.h"

#define SystemName "IBase System"

namespace IBase
{
	namespace Init
	{
		void ioInit(ImGuiIO& io)
		{
			io.Fonts->AddFontFromFileTTF("SmileySans-Oblique.ttf", 25, nullptr, io.Fonts->GetGlyphRangesChineseFull());

			//允許停靠
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			//視口設置無裝飾
			io.ConfigFlags |= ImGuiViewportFlags_NoDecoration;
			//允許視口停靠
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
			//停靠於背景
			io.ConfigFlags |= ImGuiCol_DockingEmptyBg;

			io.ConfigViewportsNoAutoMerge = true;                       // 设置背景窗口透明时，防止内窗口自动合并上透明窗口


		}
		void styleInit(ImGuiStyle& style)
		{
			//從風格當中獲取顏色列表
			ImVec4* colors = style.Colors;
			//進行顏色配置
			colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.17f, 1.00f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.37f, 0.36f, 0.36f, 102.00f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(0.10f, 0.10f, 0.10f, 171.00f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 255.00f);
			colors[ImGuiCol_CheckMark] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
			colors[ImGuiCol_SliderGrab] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
			colors[ImGuiCol_Button] = ImVec4(0.22f, 0.22f, 0.22f, 0.40f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
			colors[ImGuiCol_Header] = ImVec4(0.45f, 0.45f, 0.45f, 0.31f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.55f, 0.55f, 0.55f, 0.80f);
			colors[ImGuiCol_HeaderActive] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.46f, 0.46f, 0.46f, 0.67f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(0.17f, 0.17f, 0.17f, 0.95f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
			colors[ImGuiCol_SeparatorHovered] = ImVec4(0.50f, 0.50f, 0.50f, 0.78f);
			colors[ImGuiCol_TabHovered] = ImVec4(0.45f, 0.45f, 0.45f, 0.80f);
			colors[ImGuiCol_TabActive] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
			colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
			colors[ImGuiCol_DockingPreview] = ImVec4(0.51f, 0.51f, 0.51f, 0.70f);
			colors[ImGuiCol_Tab] = ImVec4(0.21f, 0.21f, 0.21f, 0.86f);
			colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.15f, 0.15f, 0.97f);
			colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.40f, 0.13f, 1.00f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(0.45f, 1.00f, 0.85f, 0.35f);
		}

		auto wflagsInit()
		{
			ImGuiWindowFlags_ wflags{};
			auto addflag = [&wflags](ImGuiWindowFlags_ f) { wflags = static_cast<ImGuiWindowFlags_>(wflags | f); };
			//addflag(ImGuiWindowFlags_NoDecoration);
			return wflags;
		}
#define regisWindow(name)            \
window::window_register::getInstance().register_class(#name, []() {return new name##Window; })
		void regisWindows()
		{
			using namespace IWindows;
			regisWindow(Login);
		}
	}
}