
#include <osLayer.hpp>


#ifdef _WIN32

#include <windows.h>

int os::GetKeyPress(char key)
{
    return GetAsyncKeyState(key);
}

bool os::ShowWindow(void* hwnd, int cmd)
{
    return ShowWindow(static_cast<HWND>(hwnd), cmd);
}

#endif