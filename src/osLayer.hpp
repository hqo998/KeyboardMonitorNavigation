#pragma once

namespace os
{

#ifdef _WIN32
int GetKeyPress(char key);

bool ShowWindow(void* hwnd, int cmd);

#endif

} // namespace os