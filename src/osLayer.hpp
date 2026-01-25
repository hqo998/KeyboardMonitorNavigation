#pragma once

template <typename T>
struct VectorXY
{
	T x;
	T y;
};

enum class MouseBTN
{
    LeftClick = 1,
    RightClick = 2,
};

class OSLayer
{
public:
    void *windowHandle;

    int GetKeyPresssed(char key);

    int IsKeyDown(char key);

    bool WindowVisibility(int cmd);

    bool SetMousePos(int x, int y);

    bool SendMouseClick(MouseBTN clickType);

    bool SendMouseClick(MouseBTN clickType, int x, int y)
    {
        if (!SetMousePos(x, y)) return false;
        if(!SendMouseClick(clickType)) return false;
        return true;
    };

}; // class OSLayer

#ifdef _WIN32
   // virtual keys
#define VK_BACK 0x08
#define VK_TAB 0x09

#define VK_CLEAR 0x0C
#define VK_RETURN 0x0D

#define VK_SHIFT 0x10
#define VK_CONTROL 0x11
#define VK_MENU 0x12
#define VK_PAUSE 0x13
#define VK_CAPITAL 0x14

#define VK_SPACE 0x20
#define VK_PRIOR 0x21
#define VK_NEXT 0x22
#define VK_END 0x23
#define VK_HOME 0x24
#define VK_LEFT 0x25
#define VK_UP 0x26
#define VK_RIGHT 0x27
#define VK_DOWN 0x28
#define VK_SELECT 0x29
#define VK_PRINT 0x2A
#define VK_EXECUTE 0x2B
#define VK_SNAPSHOT 0x2C
#define VK_INSERT 0x2D
#define VK_DELETE 0x2E
#define VK_HELP 0x2F

#define VK_NUMPAD0 0x60
#define VK_NUMPAD1 0x61
#define VK_NUMPAD2 0x62
#define VK_NUMPAD3 0x63
#define VK_NUMPAD4 0x64
#define VK_NUMPAD5 0x65
#define VK_NUMPAD6 0x66
#define VK_NUMPAD7 0x67
#define VK_NUMPAD8 0x68
#define VK_NUMPAD9 0x69
#define VK_MULTIPLY 0x6A
#define VK_ADD 0x6B
#define VK_SEPARATOR 0x6C
#define VK_SUBTRACT 0x6D
#define VK_DECIMAL 0x6E
#define VK_DIVIDE 0x6F
#define VK_F1 0x70
#define VK_F2 0x71
#define VK_F3 0x72
#define VK_F4 0x73
#define VK_F5 0x74
#define VK_F6 0x75
#define VK_F7 0x76
#define VK_F8 0x77
#define VK_F9 0x78
#define VK_F10 0x79
#define VK_F11 0x7A
#define VK_F12 0x7B
#define VK_F13 0x7C
#define VK_F14 0x7D
#define VK_F15 0x7E
#define VK_F16 0x7F
#define VK_F17 0x80
#define VK_F18 0x81
#define VK_F19 0x82
#define VK_F20 0x83
#define VK_F21 0x84
#define VK_F22 0x85
#define VK_F23 0x86
#define VK_F24 0x87

#define VK_NAVIGATION_VIEW 0x88   // reserved
#define VK_NAVIGATION_MENU 0x89   // reserved
#define VK_NAVIGATION_UP 0x8A     // reserved
#define VK_NAVIGATION_DOWN 0x8B   // reserved
#define VK_NAVIGATION_LEFT 0x8C   // reserved
#define VK_NAVIGATION_RIGHT 0x8D  // reserved
#define VK_NAVIGATION_ACCEPT 0x8E // reserved
#define VK_NAVIGATION_CANCEL 0x8F // reserved

#define VK_LSHIFT 0xA0
#define VK_RSHIFT 0xA1
#define VK_LCONTROL 0xA2
#define VK_RCONTROL 0xA3
#define VK_LMENU 0xA4
#define VK_RMENU 0xA5

#define VK_OEM_4 0xDB //  '[{' for US
#define VK_OEM_5 0xDC //  '\|' for US
#define VK_OEM_6 0xDD //  ']}' for US
#define VK_OEM_7 0xDE //  ''"' for US
#define VK_OEM_8 0xDF

#define VK_OEM_AX 0xE1  //  'AX' key on Japanese AX kbd
#define VK_OEM_102 0xE2 //  "<>" or "\|" on RT 102-key kbd.

// show window numbers
#define SW_HIDE 0
#define SW_NORMAL 1
#define SW_SHOWMINIMIZED 2
#define SW_SHOWMAXIMIZED 3
#define SW_SHOWNOACTIVATE 4
#define SW_SHOW 5
#define SW_MINIMIZE 6
#define SW_SHOWMINNOACTIVE 7
#define SW_SHOWNA 8
#define SW_RESTORE 9
#define SW_SHOWDEFAULT 10
#define SW_FORCEMINIMIZE 11

#endif // #ifdef _WIN32