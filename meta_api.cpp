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

#include "extdll.h"
#include "meta_api.h"

#undef C_DLLEXPORT
#ifdef _WIN32
	#define C_DLLEXPORT extern "C" __declspec(dllexport)
#else
	#define C_DLLEXPORT extern "C" __attribute__((visibility("default")))
#endif // _WIN32

plugin_info_t Plugin_info = {

	META_INTERFACE_VERSION,
	"LocalizeBug Fix",
	"2.4",
	"20/09/14",
	"s1lent",
	"http://www.aghl.ru/",
	"LocalizeBug Fix",
	PT_STARTUP,
	PT_NEVER,
};

DLL_FUNCTIONS gpFunctionTable;
DLL_FUNCTIONS *g_pFunctionTable;
enginefuncs_t g_engfuncs;

meta_globals_t *gpMetaGlobals;
gamedll_funcs_t *gpGamedllFuncs;
mutil_funcs_t *gpMetaUtilFuncs;

globalvars_t *gpGlobals;
META_FUNCTIONS gMetaFunctionTable;

void OnMetaAttach();
void ClientCommand(edict_t *pEdict);
void ClientUserInfoChanged(edict_t *pEdict,char *infobuffer);

C_DLLEXPORT int Meta_Query(char *,plugin_info_t **pPlugInfo,mutil_funcs_t *pMetaUtilFuncs)
{
	*pPlugInfo = &(Plugin_info);
	gpMetaUtilFuncs = pMetaUtilFuncs;
	return 1;
}
C_DLLEXPORT int GetEntityAPI2(DLL_FUNCTIONS *pFunctionTable,int *)
{
	memset(&gpFunctionTable,0,sizeof(DLL_FUNCTIONS));
	//gpFunctionTable.pfnClientCommand = ClientCommand;
	gpFunctionTable.pfnClientUserInfoChanged = ClientUserInfoChanged;
	memcpy(pFunctionTable,&gpFunctionTable,sizeof(DLL_FUNCTIONS));

	g_pFunctionTable = pFunctionTable;
	OnMetaAttach();

	return 1;
}
C_DLLEXPORT int Meta_Attach(PLUG_LOADTIME now,META_FUNCTIONS *pFunctionTable,meta_globals_t *pMGlobals,gamedll_funcs_t *pGamedllFuncs)
{
	if(!pMGlobals || !pFunctionTable)
		return 0;

	gpMetaGlobals = pMGlobals;
	gpGamedllFuncs = pGamedllFuncs;

	gMetaFunctionTable.pfnGetEntityAPI2 = GetEntityAPI2;
	memcpy(pFunctionTable,&gMetaFunctionTable,sizeof(META_FUNCTIONS));

	return 1;
}
C_DLLEXPORT int Meta_Detach(PLUG_LOADTIME now,PL_UNLOAD_REASON reason)
{
	return 0;
}
#ifdef __linux__
	C_DLLEXPORT void GiveFnptrsToDll(enginefuncs_t *pengfuncsFromEngine,globalvars_t *pGlobals) {
#else
	#ifdef _MSC_VER
	C_DLLEXPORT __declspec(naked) void GiveFnptrsToDll(enginefuncs_t *pengfuncsFromEngine,globalvars_t *pGlobals) {
		__asm {
			push ebp
			mov ebp,esp
			sub esp,__LOCAL_SIZE
			push ebx
			push esi
			push edi
		}
	#else	// _MSC_VER
		#ifdef __GNUC__
			C_DLLEXPORT void __stdcall GiveFnptrsToDll(enginefuncs_t *pengfuncsFromEngine,globalvars_t *pGlobals) {
		#else
			#error There is no support (yet) for your compiler. Please use MSVC or GCC compilers.
		#endif
	#endif // _MSC_VER
#endif // __linux__
		memcpy(&g_engfuncs,pengfuncsFromEngine,sizeof(enginefuncs_t));
		gpGlobals = pGlobals;
		#ifdef _MSC_VER
		if(sizeof(int *) == 8) {
			__asm {
				pop edi
				pop esi
				pop ebx
				mov esp,ebp
				pop ebp
				ret 16
			}
		}
		else {
			__asm {
				pop edi
				pop esi
				pop ebx
				mov esp,ebp
				pop ebp
				ret 8
			}
		}
	#endif // #ifdef _MSC_VER
}
