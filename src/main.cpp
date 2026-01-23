
#include <raylib.h>
#include <print>

#include <windows.hpp>
// use winapi for registering a global hotkey

int main()
{

	SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_TOPMOST | FLAG_WINDOW_ALWAYS_RUN); // Configures window to be transparent + always on top + always running
	InitWindow(800, 450, "Transparent");
	// SetWindowState(FLAG_WINDOW_UNDECORATED); // Hide border/titlebar; omit if you want them there.

	int monitorIndex = GetCurrentMonitor();
	const int screenWidth = GetMonitorWidth(monitorIndex);
	const int screenHeight = GetMonitorWidth(monitorIndex);

	SetWindowPosition(0, 0);
	SetWindowSize(screenWidth, screenHeight);

	SetTargetFPS(30);

	RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

	bool hotkeyPressed = false;

	while (!WindowShouldClose())
	{

		if ((WinGetKeyPress('D') & 0b1))
		{
			if (hotkeyPressed)
			{
				hotkeyPressed = false;
				std::println("toggle off");
			}
			else
			{
				hotkeyPressed = true;
				std::println("toggle on");
			}
		}

		// std::println("{}", hotkeyPressed);

		BeginTextureMode(target);

		ClearBackground(BLANK);
		DrawRectangle(50, 50, 200, 400, {255, 0, 0, 192}); // Red at 75% opacity
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLANK);

		if (!hotkeyPressed)
		{
			DrawTexturePro(target.texture,
						   {0.0f, 0.0f, static_cast<float>(target.texture.width), static_cast<float>(target.texture.height)},
						   {0.0f, 0.0f, static_cast<float>(screenWidth), 1440.0f},
						   {0.f, 0.f}, 0.0f, WHITE);
		}

		EndDrawing();
	}

	UnloadRenderTexture(target);
	CloseWindow();
}