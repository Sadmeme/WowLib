#include "gamefunctions.h"

namespace WowLib
{
	namespace GameFuncs	
	{
		DWORD base = NULL;
		DWORD GetGameBase()
		{
			if (!base)
				base = (DWORD)GetModuleHandle(NULL);
			return base;
		}

		Entity* GetLocalPlayer()
		{
			return *(Entity**)(base + OFFSET_LOCALPLAYER);
		}

		EntityList* GetEntityList()
		{
			return *(EntityList**)(base + OFFSET_ENTITYLIST);
		}

		DWORD GetTargetGUID()
		{
			return *(DWORD*)(base + OFFSET_TARGETGUID);
		}

		Entity* GetTargetEntity(EntityList* list, DWORD guid)
		{
			if (guid == 0)
				return nullptr;

			Entity* curEnt = list->firstEntity;
			while (true)
			{
				if (curEnt->desc->guid == guid)
				{
					return curEnt;
				}

				if (IsBadReadPtr(curEnt->nextEnttiy, sizeof(curEnt->nextEnttiy)))
					break;

				curEnt = curEnt->nextEnttiy;
			}
			
			return nullptr;
		}

		void DoLua(char* str)
		{
			typedef int(__cdecl* tDoString)(char* lua0, char* lua1, int a3);
			static tDoString doString = (tDoString)(base + LUA_DOSTRING);
			doString(str, str, 0);
		}

		char* GetLocalizedText(char* var)
		{
			typedef DWORD(* tGetPlayerObj)();
			static tGetPlayerObj getPlayerObj = (tGetPlayerObj)(base + FUNC_GETPLAYEROBJ);

			DWORD playerObj = getPlayerObj();

			typedef char*(__thiscall* tGetLocalizedText)(DWORD playerObj, char* var, int unk);
			static tGetLocalizedText getLocalizedText = (tGetLocalizedText)(base + LUA_GETLOCALIZEDTEXT);
			return getLocalizedText(playerObj, var, -1);
		}

		int GetSpellCooldown(char* spellName)
		{
			char str[512];
			sprintf_s(str, "start, duration, enable = GetSpellCooldown(\"%s\")", spellName);
			DoLua(str);

			char* dur = GetLocalizedText("duration");
			if (strlen(dur) > 0)
				return atoi(dur);
			else
				return 0;
		}

		bool IsInRange(char* spellName, char* who)
		{
			char str[512];
			sprintf_s(str, "inRange = IsSpellInRange(\"%s\", \"%s\")", spellName, who);
			DoLua(str);

			int inRange = atoi(GetLocalizedText("inRange"));
			return inRange == 1;
		}

		bool IsMounted()
		{
			char str[512];
			sprintf_s(str, "mounted = IsMounted()");
			DoLua(str);

			int mounted = atoi(GetLocalizedText("mounted"));
			return mounted == 1;
		}

		double lastCast = 0;
		char* lastSpell = "";
		bool CastSpell(char* spellName, bool skipGCD, char* who, bool noCD, bool ignoreRange)
		{
			if (IsMounted())
				return false;

			double gcd = lastCast + 0.770;
			double curTime = GetTime();
			if (!skipGCD && curTime < gcd)
				return false;

			if (strlen(lastSpell) > 0)
			{
				int end = CastingEnd("player", lastSpell) * 1000;
				if (curTime < end)
					return false;
			}

			int cd = GetSpellCooldown(spellName);
			if (cd > 0 && !noCD)
				return false;

			if (!ignoreRange)
				if (strcmp(who, "player") != 0)
					if (!IsInRange(spellName, who))
						return false;

			char str[512];
			sprintf_s(str, "CastSpellByName(\"%s\", \"%s\")", spellName, who);
			DoLua(str);

			printf("%s\n", str);

			lastCast = GetTime();
			lastSpell = spellName;
		}

		bool CastSpellOnSelf(char* spellName, bool skipGCD)
		{
			return CastSpell(spellName, skipGCD, "player");
		}

		int GetBuffCount(char* who, char* buffName, char* rank)
		{
			char str[512];
			sprintf_s(str, "name, rank, icon, count, dispelType, duration, expires, caster, isStealable, shouldConsolidate, spellID, canApplyAura, isBossDebuff, value1, value2, value3 = UnitAura(\"%s\", \"%s\", nil, \"%s\")", who, buffName, rank);
			DoLua(str);

			char* count = GetLocalizedText("count");
			if (strlen(count) > 0)
				return atoi(count) + 1;
			
			return 0;
		}

		bool HasBuff(char* who, char* buffName)
		{
			return GetBuffCount(who, buffName, WOWLIB_BUFF) >= 1;
		}

		bool HasDebuff(char* who, char* debuffName)
		{
			int c = GetBuffCount(who, debuffName, WOWLIB_DEBUFF);
			return c >= 1;
		}

		bool IsMoving(char* who)
		{
			char str[512];
			sprintf_s(str, "value = GetUnitSpeed(\"%s\")", who);
			DoLua(str);

			char* value = GetLocalizedText("value");
			printf("%f \n", value);
			if (strlen(value) > 0)
				return atof(value) > 0.0;
			
			return false;
		}

		int CastingEnd(char* who, char* spell)
		{
			char str[512];
			sprintf_s(str, "spell, rank, displayName, icon, startTime, endTime, isTradeSkill, castID, interrupt = UnitCastingInfo(\"%s\")", who);
			DoLua(str);
		
			char* _spell = GetLocalizedText("spell");
			if (strlen(_spell) == 0)
				return 0;

			if (strcmp(_spell, spell) == 0)
			{
				char* endTime = GetLocalizedText("endTime");
				return atoi(endTime);
			}

			return 0;
		}

		float GetHealthPercentage(char* who)
		{
			char str[512];
			sprintf_s(str, "health = UnitHealth(\"%s\");", who);
			DoLua(str);

			int health = atoi(GetLocalizedText("health"));
			
			sprintf_s(str, "max_health  = UnitHealthMax(\"%s\");", who);
			DoLua(str);

			int max_health = atoi(GetLocalizedText("max_health"));

			if (max_health <= 0 || health <= 0)
				return 0;

			return health / max_health;
		}

		double GetTime()
		{
			char str[512];
			sprintf_s(str, "seconds = GetTime();");
			DoLua(str);

			return atof(GetLocalizedText("seconds"));
		}

		bool IsInCombat(char* who)
		{
			char str[512];
			sprintf_s(str, "affectingCombat = UnitAffectingCombat(\"%s\");", who);
			DoLua(str);

			int affectingCombat = atoi(GetLocalizedText("affectingCombat"));
			return affectingCombat == 1;
		}

		float GetDistance(Entity* from, Entity* to)
		{
			D3DXVECTOR3 f = from->movementInfo->position, t = to->movementInfo->position;

			D3DXVECTOR3 v = f - t;
			float dist = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
			return dist;
		}

		bool TargetIsEnemy()
		{
			char str[512];
			sprintf_s(str, "isEnemy = UnitIsEnemy(\"player\", \"target\");");
			DoLua(str);

			int isEnemy = atoi(GetLocalizedText("isEnemy"));
			return isEnemy == 1;
		}

		bool IsBehind(Entity* localPlayer, Entity* targ)
		{
			return false;
		}
	}
}