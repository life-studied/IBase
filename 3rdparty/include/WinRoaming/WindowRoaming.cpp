// WindowRoaming.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "WinRoam.h"

namespace TestWindow
{
    using namespace std;
    using namespace window;
    class HelloWindow : public Window
    {
    public:
        HelloWindow(string s = "Hello", string _parent = "Login") :Window(s, _parent) {  }
        virtual string drawNext(unordered_map<string, Window*>& windowlist) override
        {
            std::cout << "hello" << std::endl;
            int num{};
            std::cin >> num;
            if (num == 1)
                return parent;
            return getName();
        }
    };

    class LoginWindow : public Window
    {
    public:
        LoginWindow(string s = "Login") :Window(s) { window::window_register::getInstance().register_class(s, []() {return new LoginWindow; }); };
        virtual string drawNext(unordered_map<string, Window*>& windowlist) override
        {
            std::cout << "Login" << std::endl;
            int num{};
            std::cin >> num;
            if (num == 1)
            {
                return "Hello";
            }
            if (num == 2)
                return {};

            return getName();
        }
    };
#define registWindow(name)            \
window::window_register::getInstance().register_class(#name, []() {return new name##Window; })

    void initWindow()
    {
        registWindow(Hello);
        registWindow(Login);
    }
    
}


int main()
{
    TestWindow::initWindow();
    using namespace window;
    WinRoam manager(new TestWindow::LoginWindow);
    while (true)
    {
        if (!manager.draw())
            break;
    }
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
