/*
 * Localize Bug Fix
 * Copyright (c) 2013 - 2014 AGHL.RU Dev Team
 * 
 * http://aghl.ru/forum/ - Russian Half-Life and Adrenaline Gamer Community
 *
 *
 *    This program is free software; you can redistribute it and/or modify it
 *    under the terms of the GNU General Public License as published by the
 *    Free Software Foundation; either version 2 of the License, or (at
 *    your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software Foundation,
 *    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *    In addition, as a special exception, the author gives permission to
 *    link the code of this program with the Half-Life Game Engine ("HL
 *    Engine") and Modified Game Libraries ("MODs") developed by Valve,
 *    L.L.C ("Valve").  You must obey the GNU General Public License in all
 *    respects for all of the code used other than the HL Engine and MODs
 *    from Valve.  If you modify this file, you may extend this exception
 *    to your version of the file, but you are not obligated to do so.  If
 *    you do not wish to do so, delete this exception statement from your
 *    version.
 *
 */

#include "main.h"

void Cmd_TokenizeString_Handler(char *buf)
{
	if (!strncmp(buf, "say ", 4) || !strncmp(buf, "say_team ", 9))
	{
		localize_string(buf, true);
	}

	pfnCmd_TokenizeString(buf);
}

void OnMetaAttach()
{
	lib_t lib;

	char *addr;
	char patch[4];

#ifdef _WIN32
	char p1[] = "\x55\x8B\x2A\xA1\x2A\x2A\x2A\x2A\x56\x33\x2A\x85\x2A\x7E\x2A\x8B\x2A\x2A\x2A\x2A\x2A\x2A\x50";
	char p2[] = "\x56\xE8\x2A\x2A\x2A\x2A\xA1\x2A\x2A\x2A\x2A\x50\xFF\x2A\x2A\x2A\x2A\x2A\x83\x2A\x2A\x5E\xC3";
#endif // _WIN32

	lib_load_info((void *)gpGlobals, &lib);

#ifdef _WIN32
	// * Cmd_TokenizeString | addr - 049A3FC0
	addr = lib_find_pattern(&lib, p1, sizeof(p1) - 1);//23
#else
	addr = lib_find_symbol(&lib, "Cmd_TokenizeString");
#endif // _WIN32

	if (!addr)
	{
		LOG_ERROR(PLID, "can't find \"Cmd_TokenizeString\"");
		return;
	}

	pfnCmd_TokenizeString = reinterpret_cast<void (*)(char *)>(addr);

#ifdef _WIN32
	// * SV_ParseStringCommand | addr - 01DAB0AF
	addr = lib_find_pattern(&lib, p2, sizeof(p2) - 1);

	if (!addr)
	{
		LOG_ERROR(PLID, "can't find \"Cmd_TokenizeString\" inside function \"SV_ParseStringCommand\"");
		return;
	}
	// 01DAB0D8 56                       push    esi
	// 01DAB0D9 E8 E2 8E F8 FF			call    Cmd_TokenizeString

	addr += 2;// 01DAB0D8 + 1
#else

	addr = lib_find_symbol(&lib, "SV_ParseStringCommand");

	if (!addr)
	{
		LOG_ERROR(PLID, "can't find \"SV_ParseStringCommand\"");
		return;
	}

	// 0009B1B0 53                       push    ebx
	// 0009B1B1 E8 AA A5 FA FF                      call    Cmd_TokenizeString

	addr = mem_find_ref(addr, 200, '\xE8', (dword)pfnCmd_TokenizeString, 1);

	if (!addr)
	{
		LOG_ERROR(PLID, "can't find \"Cmd_TokenizeString\" inside function \"SV_ParseStringCommand\"");
		return;
	}

	addr += 1;
#endif // _WIN32

	*(dword *)patch = (dword)Cmd_TokenizeString_Handler - (dword)addr - 4;

	if (!mem_change_protection(addr, patch, sizeof(patch)))
	{
		LOG_ERROR(PLID, "patch failed.");
		return;
	}

#ifdef _WIN32
	addr = lib_find_pattern_fstr(&lib, "#      name userid uniqueid frag time ping loss adr\n", -12, "\x68\x2A\x2A\x2A\x2A\x53\x56", 7);
#else
	addr = lib_find_symbol(&lib, "svs");
#endif // _WIN32

	if (!addr)
	{
		LOG_ERROR(PLID, "can't find \"svs\"");
		return;
	}

#ifdef _WIN32
	addr += 25;
	global_svs = (struct server_static_s *)(*(dword **)addr - 2);
#else
	global_svs = (struct server_static_s *)addr;
#endif // _WIN32

	localize_push();
}

void ClientUserInfoChanged(edict_t *pEdict, char *infobuffer)
{
	if (!global_svs)
		RETURN_META(MRES_IGNORED);

	char c;
	char *s;
	char *buf;

	int i = 0;
	int j = 0;

	s = getClientName(pEdict);
	buf = INFOKEY_VALUE(infobuffer, "name");

	if (*s != '\0' && !strcmp(s, buf))
	{
		RETURN_META(MRES_IGNORED);
	}

	if (*s == '#')
		*s = '*';

	for (;*buf != '\0'; buf++, i++)
	{
		if (*buf != '+')
			continue;

		c = *(buf + 1);

		if (!isspace(c) && (isdigit(c) || isalpha(c)))
		{
			*buf = '*';
			j++;
		}
	};

	if (localize_string(buf -= i, false) || j)
	{
		SET_CLIENT_KEYVALUE(ENTINDEX(pEdict), infobuffer, "name", buf);
	}

	RETURN_META(MRES_IGNORED);
}

#ifdef _WIN32
static char *strcasestr(const char *phaystack, const char *pneedle)
{
	const char *a,*b;
	for (;*phaystack; *phaystack++)
	{
		a = phaystack;
		b = pneedle;

		while ((*a++|32) == (*b++|32))
		{
			if (!*b)
				return (char *)phaystack;
		}
	}
	return NULL;
}
#endif // _WIN32

static int localize_string(char *buf, bool apersand)
{
	if (*buf == '\0')
	{
		return 0;
	}

	int t = 0;
	char *j,*a;
	char *c = buf;

	if (apersand)
	{
		do {
			if (*c == '%')
				*c = ' ';

			t++;

		} while (*c++);

		c -= t;
	}

	t = 0;

	while (true)
	{
		if (!c || !(j = strstr(c, "#")))
			break;

		c = j + 1;

		if (!isdigit(*c) && isalpha(*c) && !isspace(*c))
		{
			for (CVector<const char *>::iterator i = localize.begin(); i != localize.end(); i++)
			{
				while (true)
				{
					if (!(a = strcasestr(buf, (*i)))
						&& !(a = strcasestr(buf, "#CZero_"))
						&& !(a = strcasestr(buf, "#Cstrike_"))
						&& !(a = strcasestr(buf, "#Career_"))
						&& !(a = strcasestr(buf, "#GameUI_"))
						&& !(a = strcasestr(buf, "#Hint_"))
						&& !(a = strcasestr(buf, "#Spec_"))
						&& !(a = strcasestr(buf, "#Game_"))
						&& !(a = strcasestr(buf, "#Title_"))
						&& !(a = strcasestr(buf, "#Valve_")))
					{
						break;
					}

					*a = '*';
					t++;
				}
			}
		}
	}

	return (t > 0 && *buf != '\0');
}
