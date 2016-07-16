#pragma once

#include <Windows.h>
#include <vector>
#include "hooks\drawing\drawing.h"
#include "wow\gameclasses.h"
#include "wow\gameoffsets.h"
#include "wow\gamefunctions.h"
#include "hooks\detours\detours.h"
#include "hooks\hooks.h"

namespace Hack
{
	// CALLED FROM ENDSCENE HOOK (D3D9)
	void HackMain(IDirect3DDevice9* pDevice);

	// CALLED FROM RESET HOOK (D3D9)
	void HackReset(long resetvalue);
}