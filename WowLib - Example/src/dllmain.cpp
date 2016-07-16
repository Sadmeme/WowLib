#include <Windows.h>
#include <process.h>
#include "hack\hack.h"

DWORD WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		_beginthread(Hack::_tHackInit, 0, 0);
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}

	return TRUE;
}