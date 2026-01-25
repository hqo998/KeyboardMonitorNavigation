#include <raylib.h>
#include <print>
#include <string>

#include <osLayer.hpp>
// use winapi for registering a global hotkey

constexpr int optionsWide{10};
constexpr int optionsHigh{10};

Color C_mutedTeal = {126, 176, 155, 255};
Color C_cottenRose = {236, 190, 180, 255};
Color C_drySage = {197, 201, 164, 255};
Color C_seaGrass = {40, 90, 80, 255};
Color C_blueSlate = {71, 106, 111, 255};

std::string GetLabel(int index)
{
	std::string label = "";
	while (index > 0)
	{
		index--;
		char letter = ('A' + (index % 26)); // Z in ascii number - 25 back to one letter before 'A' then add the remainder. e.g. '?' + (1 % 26) = 'A',
		label += letter;
		index /= 26; // so that e.g 29 becomes 1, and does one more check, e.g 27 / 26 = 1 so means A
	}
	std::reverse(label.begin(), label.end()); // since the last letter added is appears first
	return label;
}

bool SequenceInString(std::string_view letterSequence, std::string_view stringToCheck)
{
	std::size_t found = stringToCheck.find(letterSequence);
	if (found <= 0)
		return true;
	// if (found != std::string::npos) return false;
	return false;
}

int main()
{

	SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_TOPMOST | FLAG_WINDOW_ALWAYS_RUN); // Configures window to be transparent + always on top + always running
	InitWindow(800, 450, "Transparent");
	SetWindowState(FLAG_WINDOW_UNDECORATED); // Hide border/titlebar; omit if you want them there.

	int monitorIndex = GetCurrentMonitor();
	const int screenWidth = GetMonitorWidth(monitorIndex);
	const int screenHeight = GetMonitorHeight(monitorIndex) - 1; // screen goes black if it perfectly fits the monitor

	std::println("Screen Width: {}, Screen Height: {}", screenWidth, screenHeight);

	SetWindowPosition(0, 0);
	SetWindowSize(screenWidth, screenHeight);

	SetTargetFPS(30);

	RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

	OSLayer os;
	os.windowHandle = GetWindowHandle(); // platform specific function to handle.

	bool showWindow = true;
	std::string letterSequence{""};

	std::println("{}", GetMonitorPosition(0).x);

	while (!WindowShouldClose())
	{
		if ((os.IsKeyDown(VK_CONTROL) && os.GetKeyPresssed('D'))) // all but one key has to be checked if down to make it so you dont need frame perfect press. But one pressed is needed to avoid repeated activation.
		{
			bool otherKeyPressed = false;

			for (int key = 0; key < 256; key++)
			{
				if (key != VK_CONTROL && key != 'D' && os.IsKeyDown(static_cast<char>(key))) // Check if any other key is pressed
				{
					otherKeyPressed = true;
					break;
				}
			}
			if (!otherKeyPressed)
			{
				if (showWindow)
				{
					showWindow = false;
					std::println("toggle off");
					MinimizeWindow();
					// OSLayer::ShowWindow(hwnd, 0);
				}
				else
				{
					showWindow = true;
					std::println("toggle on");
					// RestoreWindow();
					os.ShowWindow(9); // make enum for numbers
				}
			}
		}

		// record key strokes when visible by adding to letter sequene
		if (!IsWindowMinimized())
		{
			// std::println("{}", letterSequence);

			for (int key = 0; key < 256; key++)
			{
				if (os.GetKeyPresssed(static_cast<char>(key)))
				{
					if (key == VK_BACK) // Compare key directly as an integer
					{
						std::println("back key");
						if (!letterSequence.empty()) // Prevent popping from an empty string
						{
							letterSequence.pop_back();
						}
					}
					else if (key == VK_DELETE)
					{
						letterSequence.clear();
					}
					else if (key >= 0x41 && key <= 0x5A)
					{
						letterSequence += static_cast<char>(key);
					}
				}
			}
		}
		else
		{
			letterSequence.clear();
		}

		if (IsWindowMinimized()) // dont draw when hidden
		{
			continue;
		}

		// drawing to texture
		BeginTextureMode(target);

		ClearBackground(BLANK);

		const int spacingWide = screenWidth / optionsWide;
		const int spacingHigh = screenHeight / optionsHigh;
		int options { 0 };
		int selectionX = { };
		int selectionY = { };
		// use for loop to draw locations of each box
		for (int iWide = 1; iWide < optionsWide; iWide++)
		{
			for (int iHigh = 1; iHigh < optionsHigh; iHigh++)
			{
				// text
				std::string letterX = GetLabel(iWide);
				std::string letterY = GetLabel(iHigh);
				std::string buttonIdentity = std::format("{}{}", letterX, letterY);

				// buttonn placement
				Rectangle rect = {static_cast<float>(spacingWide * iWide),
								  static_cast<float>(spacingHigh * iHigh),
								  static_cast<float>(screenWidth / 40),
								  static_cast<float>(screenWidth / 90)};
				Vector2 origin = {rect.width * .5f, rect.height * .5f};
				Rectangle centredRect = {rect.x - origin.x, rect.y - origin.y, rect.width, rect.height};

				// drawing boxes
				DrawRectangleRounded({centredRect.x + 2, centredRect.y + 3, centredRect.width, centredRect.height},
									 .3f,
									 5,
									 C_cottenRose);

				DrawRectangleRounded(centredRect,
										.3f,
										5,
										SequenceInString(letterSequence, buttonIdentity) ? C_mutedTeal : C_seaGrass);

				// drawing box label
				DrawText(buttonIdentity.c_str(),
						 static_cast<int>(centredRect.x) + ((int)rect.width/2)-20,
						 static_cast<int>(centredRect.y) + ((int)rect.height/2)-10,
						 20,
						 C_blueSlate);
				
				if (SequenceInString(letterSequence, buttonIdentity))
				{
					options++; // add how many valid options match sequence
					selectionX = static_cast<int>(rect.x);
					selectionY = static_cast<int>(rect.y);
				}
			} // for (int iHigh = 1; iHigh < optionsHigh; iHigh++)
		} // for (int iWide = 1; iWide < optionsWide; iWide++)

		EndTextureMode();

		if (options == 1)
		{
			std::println("only 1!");
			showWindow = false;
			MinimizeWindow();
			os.SetCursorPosition(selectionX, selectionY);
		}

		// drawing texture on screen.
		BeginDrawing();
		ClearBackground(BLANK);

		DrawTexturePro(target.texture,
					   {0.0f, 0.0f, static_cast<float>(target.texture.width), -static_cast<float>(target.texture.height)},
					   {0.0f, 0.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight)},
					   {0.f, 0.f}, 0.0f, WHITE);

		EndDrawing();

	} // while (!WindowShouldClose())

	UnloadRenderTexture(target);
	CloseWindow();
}