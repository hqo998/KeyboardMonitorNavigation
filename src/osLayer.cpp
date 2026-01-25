
#include <osLayer.hpp>

#ifdef _WIN32

#include <windows.h>

int OSLayer::GetKeyPresssed(char key)
{
    return GetAsyncKeyState(key) & 0b1;
}

int OSLayer::IsKeyDown(char key)
{
    return GetAsyncKeyState(key);
}

bool OSLayer::WindowVisibility(int cmd)
{
    return ShowWindow(static_cast<HWND>(windowHandle), cmd);
}

bool OSLayer::FocusWindow()
{
    return SetFocus(static_cast<HWND>(windowHandle));
}

bool OSLayer::SetMousePos(int x, int y)
{
    return SetCursorPos(x, y);
}

bool OSLayer::SendMouseClick(MouseBTN clickType)
{

    INPUT mouse[2] = {};
    mouse[0].type = INPUT_MOUSE;
    mouse[0].mi.dx = 0;
    mouse[0].mi.dy = 0;
    mouse[0].mi.mouseData = 0;

    mouse[0].mi.time = 0;
    mouse[0].mi.dwExtraInfo = 0;

    mouse[1].type = INPUT_MOUSE;
    mouse[1].mi.dx = 0;
    mouse[1].mi.dy = 0;
    mouse[1].mi.mouseData = 0;
    mouse[1].mi.time = 0;
    mouse[1].mi.dwExtraInfo = 0;

    switch (clickType)
    {
    case MouseBTN::LeftClick:
        mouse[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        mouse[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
        break;

    case MouseBTN::RightClick:
        mouse[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
        mouse[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
        break;
    default:
        return false;
        break;
    }

    return SendInput(ARRAYSIZE(mouse), mouse, sizeof(INPUT));
}

#endif // _WIN32