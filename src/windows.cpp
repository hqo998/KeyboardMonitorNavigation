#include <windows.h>

#include <windows.hpp>


int WinGetKeyPress(char key)
{
    return GetAsyncKeyState(key);
}
