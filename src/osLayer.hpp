#pragma once

namespace os
{

#ifdef _WIN32
int GetKeyPresssed(char key);

int isKeyDown(char key);

bool ShowWindow(void* hwnd, int cmd);

#endif

} // namespace os