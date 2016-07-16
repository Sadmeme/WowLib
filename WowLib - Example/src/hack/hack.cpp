#include "hack.h"
#include <stdio.h>
#include <process.h>
#include <time.h>

namespace Hack
{
	WowLib::Drawing::CDrawing drawing;
	DWORD base = WowLib::GameFuncs::GetGameBase();

	bool RoutineEnabled = false;
	void HackMain(IDirect3DDevice9* pDevice)
	{
		if (!drawing.Initialized())
			drawing.Initialize(pDevice, "Tahoma");

		drawing.DrawShadowString(false, 10, 10, D3DCOLOR_RGBA(255, 255, 255, 255), "Test Drawing!");

		
	}

	void HackReset(long resetvalue)
	{
		drawing.Reset(resetvalue);
	}

	void _tHackInit(LPVOID)
	{
		WowLib::Hooks::InitHooks();
		BOOL f = AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		ExitThread(0);
	}
}