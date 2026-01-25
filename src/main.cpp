#include <raylib.h>
#include <print>
#include <vector>

#include "osLayer.hpp"
#include "keybinds.hpp"
#include "configReader.hpp"





// use winapi for registering a global hotkey
Keybind toggleKeybind = {{VK_MENU, VK_SHIFT}, 'D'};

constexpr VectorXY options{20, 20};

namespace Colours
{
	constexpr Color valid = {126, 176, 155, 255};
	constexpr Color invalid = {40, 90, 80, 255};
	constexpr Color shadow = {236, 190, 180, 255};
	constexpr Color text = {71, 106, 111, 255};
}



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
	if (stringToCheck.find(letterSequence) <= 0)
		return true; // make sure sequence is at the beginning
	return false;
}

void FitToMonitor(VectorXY<int> &screen, int monitorIndex)
{
	if (monitorIndex > GetMonitorCount() - 1) return;
	screen = {GetMonitorWidth(monitorIndex), GetMonitorHeight(monitorIndex) - 1};
	SetWindowPosition((int)GetMonitorPosition(monitorIndex).x, (int)GetMonitorPosition(monitorIndex).y);
	SetWindowSize(screen.x, screen.y);
}

int main()
{
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_TOPMOST | FLAG_WINDOW_ALWAYS_RUN); // Configures window to be transparent + always on top + always running
	InitWindow(800, 450, "Keyboard Navigation");
	SetWindowState(FLAG_WINDOW_UNDECORATED); // Hide border/titlebar; omit if you want them there.

	int monitorIndex = GetCurrentMonitor();
	VectorXY<int> screen{};

	FitToMonitor(screen, monitorIndex);

	SetTargetFPS(30);

	RenderTexture2D target = LoadRenderTexture(screen.x, screen.y);

	OSLayer os;
	os.windowHandle = GetWindowHandle(); // platform specific function to handle.

	bool showWindow = true;
	std::string letterSequence{""};

	Font customFont = LoadFontEx("config/Oswald-Medium.ttf", 96, NULL, 0);
	SetTextureFilter(customFont.texture, TEXTURE_FILTER_BILINEAR);

	while (!WindowShouldClose())
	{
		// hotkey
		if (toggleKeybind.IsActivated(os)) {
			if (showWindow) {
				showWindow = false;
				std::println("toggle off");
				os.WindowVisibility(SW_SHOWMINIMIZED);
			} else {
				showWindow = true;
				std::println("toggle on");
				os.WindowVisibility(SW_RESTORE);
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
					else if (key >= 0x30 && key <= 0x39)
					{
						std::println("fitting to monitor: {}", key - 0x30);
						FitToMonitor(screen, key - 0x30 - 1);
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
		// BeginTextureMode(target);
		BeginDrawing();

		ClearBackground(BLANK);

		const VectorXY spacing{screen.x / options.x, screen.y / options.y};

		int amountValid{0};

		VectorXY<int> selection = {};

		// use for loop to draw locations of each box
		for (int iWide = 1; iWide < options.x; iWide++)
		{
			for (int iHigh = 1; iHigh < options.y; iHigh++)
			{
				// text
				std::string letterX = GetLabel(iWide);
				std::string letterY = GetLabel(iHigh);
				std::string buttonIdentity = std::format("{}{}", letterX, letterY);

				// text calcs
				float fontSize { 30 };
				float fontSpacing { 3 };
				Vector2 textSize = MeasureTextEx(customFont, buttonIdentity.c_str(), fontSize, fontSpacing);

				// buttonn placement
				Rectangle rect = {static_cast<float>(spacing.x * iWide),
								  static_cast<float>(spacing.y * iHigh),
								  std::max(static_cast<float>(screen.x / 40), (textSize.x + 10)),
								  30};
				Vector2 origin = {rect.width * .5f, rect.height * .5f};
				Rectangle centredRect = {rect.x - origin.x, rect.y - origin.y, rect.width, rect.height};

				// drawing boxes
				DrawRectangleRounded({centredRect.x + 2, centredRect.y + 3, centredRect.width, centredRect.height},
									 .3f,
									 5,
									 Colours::shadow);

				DrawRectangleRounded(centredRect,
									 .3f,
									 5,
									 SequenceInString(letterSequence, buttonIdentity) ? Colours::valid : Colours::invalid);

				// drawing box label
				// DrawText(buttonIdentity.c_str(), 
				// 		 static_cast<int>(centredRect.x + (rect.width / 2) - 20),
				// 		 static_cast<int>(centredRect.y + (rect.height / 2) - 9),
				// 		 20,
				// 		 Colours::text);
				
				DrawTextPro(customFont,
					buttonIdentity.c_str(), 
						 {(rect.x + (rect.width - textSize.x)/2), (rect.y + (rect.height - textSize.y)/2)},
						// {(rect.x), (rect.y)},
						 origin,
						 .0f,
						 fontSize,
						 fontSpacing,
						 Colours::text);

				// setting selection stuff.
				if (SequenceInString(letterSequence, buttonIdentity))
				{
					amountValid++; // add how many valid amountValid match sequence
					selection.x = static_cast<int>(rect.x + GetMonitorPosition(GetCurrentMonitor()).x); // TODO - MINUS MONITOR POSTION FOR CORRECT POS
					selection.y = static_cast<int>(rect.y + GetMonitorPosition(GetCurrentMonitor()).y); // TODO - MINUS MONITOR POSTION FOR CORRECT
				}
			} // for (int iHigh = 1; iHigh < options.y; iHigh++)
		} // for (int iWide = 1; iWide < options.x; iWide++)

		// EndTextureMode();
		EndDrawing();

		if (amountValid == 1)
		{
			std::println("only 1!");
			showWindow = false;
			MinimizeWindow();
			os.SendMouseClick(MouseBTN::LeftClick, selection.x, selection.y);
		}

	} // while (!WindowShouldClose())

	UnloadRenderTexture(target);
	CloseWindow();
}