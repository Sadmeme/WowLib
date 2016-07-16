#pragma once
#include "..\WowLib.h"

#define WOWLIB_BUFF "HELPFUL"
#define WOWLIB_DEBUFF "HARMFUL"
namespace WowLib
{
	namespace GameFuncs	
	{
		DWORD GetGameBase();
		Entity* GetLocalPlayer();
		EntityList* GetEntityList();
		DWORD GetTargetGUID();
		Entity* GetTargetEntity(EntityList* list, DWORD guid);
		void DoLua(char* str);
		char* GetLocalizedText(char* var);
		int GetSpellCooldown(char* spellName);
		bool IsInRange(char* spellName, char* who = "target");
		bool CastSpell(char* spellName, bool skipGCD = false, char* who = "target", bool noCD = false, bool ignoreRange = false);
		bool CastSpellOnSelf(char* spellName, bool skipGCD = false);
		int GetBuffCount(char* who, char* buffName, char* rank = WOWLIB_BUFF);
		bool HasBuff(char* who, char* buffName);
		bool HasDebuff(char* who, char* debuffName);
		bool IsMoving(char* who = "player");
		int CastingEnd(char* who, char* spell);
		float GetHealthPercentage(char* who);
		double GetTime();
		bool IsInCombat(char* who);
		float GetDistance(Entity* from, Entity* to);
		bool TargetIsEnemy();
		bool IsBehind(Entity* localPlayer, Entity* targ);
	}
}