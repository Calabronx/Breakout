#include "constants.h"

 int get_height_desktop_resolution()
 {
	RECT desktop;

	const HWND h_desktop = GetDesktopWindow();
	GetWindowRect(h_desktop, &desktop);
	int height_screen = 0;

	std::cout << desktop.bottom << std::endl;
	if (desktop.bottom == 1080)
	{
		height_screen = desktop.bottom - 100;
	} else {
		height_screen = desktop.bottom;
	}
	std::cout << "call get_height_desktop_resolution()" << std::endl;
	return height_screen;
	// return 720;
 }