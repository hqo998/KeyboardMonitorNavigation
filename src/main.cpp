
#include <raylib.h>
#include <print>

#include <windows.hpp>

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	// SetConfigFlags(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_ALWAYS_RUN); // always on top + always running
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_TOPMOST | FLAG_WINDOW_ALWAYS_RUN); // Configures window to be transparent + always on top + always running
	InitWindow(screenWidth, screenHeight, "Transparent");

	SetWindowPosition(GetMonitorWidth(0) / 2 - screenWidth / 2, GetMonitorHeight(0) / 2 - screenHeight / 2);
	// SetWindowState(FLAG_WINDOW_UNDECORATED); // Hide border/titlebar; omit if you want them there.

	SetTargetFPS(30);

	RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    bool hotkeyPressed = false;

	while(!WindowShouldClose())
	{
        if (IsKeyPressed(KEY_D))
        {
            hotkeyPressed = true;
            std::println("true");
        }
        else if (IsKeyReleased(KEY_D))
        {
            hotkeyPressed = false;
            std::println("false");
        }

		BeginTextureMode(target);

		ClearBackground(BLANK);
		DrawRectangle(50, 50, 200, 100, {255, 0, 0, 192}); // Red at 75% opacity
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLANK);

        if (!hotkeyPressed)
        {
            DrawTexturePro(target.texture, { 0.0f, 0.0f, 800.0f, 450.0f }, { 0.0f, 0.0f, 800.0f, 450.0f },
        { 0.f, 0.f }, 0.0f, WHITE);
        }



		EndDrawing();
	}

	UnloadRenderTexture(target);
	CloseWindow();
}