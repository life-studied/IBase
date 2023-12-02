#include "init.hpp"
#include "WinRoaming/WinRoam.h"
#include "LoginWindow.h"

using namespace IBase;
int main()
{
	// 窗口指针
	GLFWwindow* Windows;
	// glfw初始化窗口
	glfwInit();
	// 定义窗口创建模式
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);  // 设置 背景窗口 透明

	// 创建窗口并给予窗口指针
	Windows = glfwCreateWindow(900, 800, SystemName, NULL, NULL);
	// 给予控制权
	glfwMakeContextCurrent(Windows);
	glfwSwapInterval(0);

	//初始化ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext(NULL);
	// 设置io内容
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	Init::ioInit(io);

	// 设置风格
	ImGuiStyle& style = ImGui::GetStyle();
	Init::styleInit(style);

	// 初始化ImGui用于Glfw创建的窗口 (而且使用OpenGL进行底层渲染)
	ImGui_ImplGlfw_InitForOpenGL(Windows, true);
	// 初始化ImGui用于OpenGL渲染绘制  (需要定义OpenGL版本好  进行GLSL代码的自动创建)
	ImGui_ImplOpenGL3_Init("#version 330");

	// 初始化窗口标签
	auto wflags = Init::wflagsInit();

	// 注册窗口
	Init::regisWindows();

	auto main_loop = [&](window::WinRoam& winM) {
		while (!glfwWindowShouldClose(Windows))
		{
			// 清除渲染数据
			glClear(GL_COLOR_BUFFER_BIT);
			// ImGui每帧初始化
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			// 创建视口停靠
			ImGui::DockSpaceOverViewport();

			{
				if (!winM.draw())
					break;
			}

			// 渲染
			ImGui::Render();
			// 绘制ImGui数据
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				//当窗口拉出范围时，创建子窗口
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
			// 绘制窗口内容
			glfwSwapBuffers(Windows);
			// 绘制事件
			glfwPollEvents();

		}
	};

	// 启动！
	window::WinRoam winM(new IWindows::LoginWindow);
	main_loop(winM);

}