#include "hooks.h"
#include "..\WowLib.h"

namespace WowLib
{
	namespace Hooks
	{
		bool Compare(const BYTE* pData, const BYTE* bMask, const char* szMask)
		{
			for (; *szMask; ++szMask, ++pData, ++bMask)
				if (*szMask == 'x' && *pData != *bMask)   return 0;
			return (*szMask) == NULL;
		}

		DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask)
		{
			for (DWORD i = 0; i<dwLen; i++)
				if (Compare((BYTE*)(dwAddress + i), bMask, szMask))  return (DWORD)(dwAddress + i);
			return 0;
		}

		typedef HRESULT(WINAPI* tEndScene) (LPDIRECT3DDEVICE9 pDevice);
		extern tEndScene oEndScene;

		typedef HRESULT(WINAPI* tReset)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
		extern tReset oReset;

		HRESULT WINAPI hkEndScene(IDirect3DDevice9* pDevice);
		HRESULT WINAPI hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);


		tEndScene oEndScene = NULL;
		tReset oReset = NULL;

		HRESULT WINAPI hkEndScene(IDirect3DDevice9* pDevice)
		{
			Hack::HackMain(pDevice);

			return oEndScene(pDevice);
		}

		HRESULT WINAPI hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
		{
			long iReturnValue = oReset(pDevice, pPresentationParameters);
			Hack::HackReset(iReturnValue);

			return iReturnValue;
		}

		void InitHooks()
		{
			static byte bMask[] = { 0xC7, 0x06, 0x00, 0x00, 0x00, 0x00, 0x89, 0x86, 0x00, 0x00, 0x00, 0x00, 0x89, 0x86 };
			DWORD Address = FindPattern(reinterpret_cast<DWORD>(GetModuleHandle("d3d9.dll")), 0x128000, bMask, "xx????xx????xx");
			DWORD* VTable;
			memcpy(&VTable, reinterpret_cast<void*>(Address + 2), 4);

			oEndScene = (tEndScene)VTable[42];
			oReset = (tReset)VTable[16];

			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());

			DetourAttach(&(PVOID&)oEndScene, hkEndScene);
			DetourAttach(&(PVOID&)oReset, hkReset);

			DetourTransactionCommit();
			
			WowLib::GameFuncs::GetGameBase();
		}
	}
}