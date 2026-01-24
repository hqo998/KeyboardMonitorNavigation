
#include <osLayer.hpp>

using namespace os;

#ifdef _WIN32

#include <windows.h>

int os::GetKeyPresssed(char key)
{
    return GetAsyncKeyState(key) & 0b1;
}

int os::IsKeyDown(char key)
{
    return GetAsyncKeyState(key);
}

bool os::ShowWindow(void* hwnd, int cmd)
{
    return ShowWindow(static_cast<HWND>(hwnd), cmd);
}
#endif