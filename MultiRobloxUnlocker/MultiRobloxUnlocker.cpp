#include <iostream>
#include <string>
#include <Windows.h>

HANDLE hMutex;

static BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
    case CTRL_C_EVENT:
    case CTRL_CLOSE_EVENT:
        if (hMutex) {
            ReleaseMutex(hMutex);
            CloseHandle(hMutex);
        }
        return TRUE;
    default:
        return FALSE;
    }
}

static bool Choice() {
	std::string Response;
	std::getline(std::cin, Response);
	if (Response[0] != 'y' && Response[0] != 'Y' && Response[0] != 'n' && Response[0] != 'N') {
		do {
			std::cout << "Enter a valid input [y/N]: ";
			std::getline(std::cin, Response);
		} while (Response.empty() || (Response[0] != 'y' && Response[0] != 'Y' && Response[0] != 'n' && Response[0] != 'N'));
	}

	if (Response[0] == 'y' || Response[0] == 'Y') {
		return true;
	}
	else {
		return false;
	}
}

int main()
{
    if (!SetConsoleCtrlHandler(CtrlHandler, TRUE)) {
        std::cout << "Error setting CtrlHandler! DO NOT CLOSE DIRECTRY THE PROGRAM OR PRESS Ctrl+C !\n\n";
    }
    std::cout << "Welcome to a simple program made by @RMP_Official\nThis program allow opening multiple instances of roblox by creating a mutex!\n\nCreating a mutex..\n";
    hMutex = CreateMutex(0, 1, L"ROBLOX_singletonEvent");
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        std::cout << "Mutex already exists! Close all roblox instances before opening this program!\n\n";
        system("pause");
        return 1;
    }
    std::cout << "Mutex sucessfully created, dont close this program while you play roblox!\n";
	std::cout << "\nClose the program, press Ctrl+C or press ENTER when you finished playing: ";
    system("pause");
end:
	if (hMutex) {
        ReleaseMutex(hMutex);
        CloseHandle(hMutex);
    }
	return 0;
}