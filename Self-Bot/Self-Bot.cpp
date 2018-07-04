#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <algorithm>
#include <sstream>
#include <vector>
#include <ctime> 

void setConsoleColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void DisplayError(LPCTSTR errorDesc, DWORD errorCode)
{
	TCHAR errorMessage[1024] = TEXT("");

	DWORD flags = FORMAT_MESSAGE_FROM_SYSTEM
		| FORMAT_MESSAGE_IGNORE_INSERTS
		| FORMAT_MESSAGE_MAX_WIDTH_MASK;

	FormatMessage(flags,
		NULL,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		errorMessage,
		sizeof(errorMessage) / sizeof(TCHAR),
		NULL);
	std::wcerr << L"Error : " << errorDesc << std::endl;
	std::wcerr << L"Code    = " << errorCode << std::endl;
	std::wcerr << L"Message = " << errorMessage << std::endl;

}

template<typename Out>
void split(const std::string &s, char delim, Out result)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

#define MST (-7)
#define UTC (0)
#define CCT (+8)

int main()
{
	setConsoleColor(10);
	std::cout << "---[Welcome]---" << std::endl;
	setConsoleColor(15);
	Sleep(1000);
	system("CLS");
	std::string arguments;// varible 
	while (1)
	{
		std::cout << "How May I Help You Today?" << std::endl; // console out
		std::cout << "> "; // Extra

					  // get line gets the whole line. Just now, it was getting only the first word,
		std::getline(std::cin, arguments); // varible to store arguments

		std::vector<std::string> x = split(arguments, ' ');

		std::transform(arguments.begin(), arguments.end(), arguments.begin(), ::tolower); // makes it lower case
		if (x[0] == "t")
		{
			std::cout << std::endl;
			if (x[1] == "china")
			{
				struct tm timestruct;
				__int64 lltime;
				_time64(&lltime);
				_gmtime64_s(&timestruct, &lltime);


				std::cout << "Beijing (China) : " << std::setw(2) << std::setfill('0') << (timestruct.tm_hour + CCT) % 24 << ":" << std::setw(2) << std::setfill('0') << timestruct.tm_min;
			}
			else if (x[1] == "iceland")
			{
				struct tm timestruct;
				int64_t lltime;
				_time64(&lltime);
				_gmtime64_s(&timestruct, &lltime);

				std::cout << "Reykjavik (Iceland) : " << std::setw(2) << std::setfill('0') << (timestruct.tm_hour + UTC) % 24 << ":" << std::setw(2) << std::setfill('0') << timestruct.tm_min;
			}
			else if (x[1] == "us")
			{
				struct tm timestruct;
				int64_t lltime;
				_time64(&lltime);
				_gmtime64_s(&timestruct, &lltime);

				std::cout << "Phoenix, AZ (U.S.) : " << std::setw(2) << std::setfill('0') << (timestruct.tm_hour + MST) % 24 << ":" << std::setw(2) << std::setfill('0') << timestruct.tm_min;
			}
			else
			{
				struct tm timestruct;
				__int64 lltime;
				_time64(&lltime);
				_localtime64_s(&timestruct, &lltime);

				std::cout << "Local Time : " << std::setw(2) << std::setfill('0') << timestruct.tm_hour << ":" << std::setw(2) << std::setfill('0') << timestruct.tm_min;

			}
			Sleep(5000);
		}
		else if (x[0] == "o")
		{
			if (x[1] == "discord")
			{
				STARTUPINFO StartupInfo = { sizeof(StartupInfo) };
				PROCESS_INFORMATION ProcessInfo;
				ZeroMemory(&StartupInfo, sizeof(StartupInfo));
				ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));
				if (!CreateProcess(L"C:\\Users\\user\\AppData\\Local\\Discord\\app-0.0.301\\Discord.exe", NULL, NULL, NULL, TRUE, 0, NULL, NULL, &StartupInfo, &ProcessInfo)
					)
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else
				{
					std::cout << "Program Opened!" << std::endl;
				}
				Sleep(3000);
			}
			else if (x[1] == "ac")
			{
				STARTUPINFO StartupInfo = { sizeof(StartupInfo) };
				PROCESS_INFORMATION ProcessInfo;
				ZeroMemory(&StartupInfo, sizeof(StartupInfo));
				ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));
				if (!CreateProcess(L"C:\\Users\\user\\Desktop\\Content Manager.exe", NULL, NULL, NULL, TRUE, 0, NULL, NULL, &StartupInfo, &ProcessInfo))
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else
				{
					std::cout << "Program Opened!" << std::endl;
				}
				Sleep(3000);
			}
			else if (x[1] == "anime")
			{
				if (!ShellExecute(0, 0, L"https://9anime.to/", 0, 0, SW_SHOW)) // shell code 
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else
				{
					std::cout << "Website Launched" << std::endl;
				}
				Sleep(3000);
			}
			else if (x[1] == "github")
			{
				if (x[2] == "")
				{
					if (!ShellExecute(0, 0, L"https://github.com/SagaanTheEpic", 0, 0, SW_SHOW)) // shell code 
					{
						DWORD errorCode = GetLastError();
						DisplayError(TEXT("Unable to execute."), errorCode);
					}
					else
					{
						std::cout << "Website Launched" << std::endl;
					}
					Sleep(3000);
				}
				else
				{
					std::string Link = "https://github.com/" + x[2];

					std::wstring stemp = s2ws(Link);
					LPCWSTR LinkFinal = stemp.c_str();
					if (!ShellExecute(0, 0, LinkFinal, 0, 0, SW_SHOW)) // shell code 
					{
						DWORD errorCode = GetLastError();
						DisplayError(TEXT("Unable to execute."), errorCode);
					}
					else
					{
						std::cout << "Website Launched" << std::endl;
					}
					Sleep(3000);
				}
			}
			else if (x[1] == "youtube")
			{
				if (x[2] == "")
				{
					if (!ShellExecute(0, 0, L"https://www.youtube.com/", 0, 0, SW_SHOW)) // shell code 
					{
						DWORD errorCode = GetLastError();
						DisplayError(TEXT("Unable to execute."), errorCode);
					}
					else
					{
						std::cout << "Website Launched" << std::endl;
					}
					Sleep(3000);
				}
				else
				{
					std::string Link = "https://www.youtube.com/user/" + x[2] + "/videos";

					std::wstring stemp = s2ws(Link);
					LPCWSTR LinkFinal = stemp.c_str();
					if (!ShellExecute(0, 0, LinkFinal, 0, 0, SW_SHOW)) // shell code 
					{
						DWORD errorCode = GetLastError();
						DisplayError(TEXT("Unable to execute."), errorCode);
					}
					else
					{
						std::cout << "Website Launched" << std::endl;
					}
					Sleep(3000);
				}
			}
			else if (x[1] == "uc")
			{
				if (!ShellExecute(0, 0, L"https://www.unknowncheats.me/forum/index.php", 0, 0, SW_SHOW)) // shell code 
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else
				{
					std::cout << "Website Launched" << std::endl;
				}
				Sleep(3000);
			}
			else if (x[1] == "music")
			{
				STARTUPINFO StartupInfo = { sizeof(StartupInfo) };
				PROCESS_INFORMATION ProcessInfo;
				ZeroMemory(&StartupInfo, sizeof(StartupInfo));
				ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));
				if (!CreateProcess(L"C:\\Users\\user\\AppData\\Roaming\\Spotify\\Spotify.exe", NULL, NULL, NULL, TRUE, 0, NULL, NULL, &StartupInfo, &ProcessInfo))
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else
				{
					std::cout << "Program Opened!" << std::endl;
				}
				Sleep(3000);
			}
			else if (x[1] == "steam")
			{
				STARTUPINFO StartupInfo = { sizeof(StartupInfo) };
				PROCESS_INFORMATION ProcessInfo;
				ZeroMemory(&StartupInfo, sizeof(StartupInfo));
				ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));
				if (!CreateProcess(L"C:\\Program Files (x86)\\Steam\\Steam.exe", NULL, NULL, NULL, TRUE, 0, NULL, NULL, &StartupInfo, &ProcessInfo))
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else
				{
					std::cout << "Program Opened!" << std::endl;
				}
				Sleep(3000);
			}
			else if (x[1] == "setup")
			{
				if (!ShellExecute(0, 0, L"https://www.unknowncheats.me/forum/index.php", 0, 0, SW_SHOW)) // shell code 
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else if (!ShellExecute(0, 0, L"https://www.youtube.com/", 0, 0, SW_SHOW)) // shell code 
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else if (!ShellExecute(0, 0, L"https://github.com/SagaanTheEpic", 0, 0, SW_SHOW)) // shell code 
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else if (!ShellExecute(0, 0, L"https://www.speedrun.com/Assetto_Corsa", 0, 0, SW_SHOW)) // shell code 
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else
				{
					std::cout << "Website Launched" << std::endl;
				}
				Sleep(3000);
			}
			else
			{
				std::cout << "Unknown instruction." << std::endl;
				Sleep(1000);
			}
		}
		else if (x[1] != "")
		{
			std::cout << std::endl << "Instruction unclear, command stuck in ceiling fan." << std::endl;
			Sleep(1000);
		}

		system("CLS");
		arguments = ""; // remember to clear arguments so that it doesnt repeat

	}
}