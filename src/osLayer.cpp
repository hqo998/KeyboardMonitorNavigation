
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

bool OSLayer::SetCursorPosition(int x, int y)
{
    return SetCursorPos(x, y);
}

#endif // _WIN32