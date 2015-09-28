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

#ifndef _MAIN_H_
#define _MAIN_H_

#include "memory.h"
#include "CVector.h"

#include "extdll.h"
#include "meta_api.h"

#ifdef _WIN32
	#define SIZEOF_CLIENT_T 20504
	#define PLAYER_NAME_OFFSET 19720
#else
	#define SIZEOF_CLIENT_T 20212
	#define PLAYER_NAME_OFFSET 19432
#endif // _WIN32

typedef struct server_static_s
{
	int initialized;
	int clients;
	int maxclients;
	//[..]
} server_static_t;

const char *szLocalizeBuffer[] =
{
	"#Team_Select", "#Team_Select_Spect", "#IG_Team_Select", "#IG_Team_Select_Spect", "#IG_VIP_Team_Select", "#IG_VIP_Team_Select_Spect", "#Terrorist_Select",
	"#CT_Select", "#Buy", "#CT_BuyItem", "#T_BuyItem", "#DCT_BuyItem", "#DT_BuyItem", "#CT_BuyPistol", "#T_BuyPistol", "#AS_BuyShotgun", "#BuyShotgun",
	"#CT_BuySubMachineGun", "#T_BuySubMachineGun", "#AS_CT_BuySubMachineGun", "#AS_T_BuySubMachineGun", "#T_BuyRifle", "#CT_BuyRifle", "#AS_T_BuyRifle",
	"#AS_CT_BuyRifle", "#AS_T_BuyMachineGun", "#BuyMachineGun", "#RadioA", "#RadioB", "#RadioC", "#AK47", "#SG552", "#M4A1", "#Famas", "#Galil", "#Aug", "#Scout",
	"#ArcticWarfareMagnum", "#G3SG1", "#SG550", "#USP45", "#Glock18", "#DesertEagle", "#P228", "#Beretta96G", "#FiveSeven", "#Super90", "#XM1014", "#mp5navy", "#tmp",
	"#FNP90", "#Mac10", "#UMP45", "#M249", "#Krieg552", "#M4A1_Short", "#Schmidt", "#Magnum", "#D3AU1", "#Krieg550", "#KM45Tactical", "#Sidearm9X19mm", "#NightHawk",
	"#P228Compact", "#Dual40", "#ESFiveSeven", "#Leone12", "#AutoShotgun", "#SubMachineGun", "#SchmidtMP", "#ESC90", "#Mac10_Short", "#KMUMP45", "#ESM249", "#TEAMS",
	"#PLAYERS", "#CLASS", "#SCORE", "#DEATHS", "#LATENCY", "#VOICE", "#Menu_OK", "#Menu_Cancel", "#Menu_Spectate", "#Team_AutoAssign", "#Target_Bombed", "#VIP_Escaped",
	"#VIP_Assassinated", "#Terrorists_Escaped", "#CTs_PreventEscape", "#Escaping_Terrorists_Neutralized", "#Bomb_Defused", "#CTs_Win", "#Terrorists_Win", "#Round_Draw",
	"#All_Hostages_Rescued", "#Target_Saved", "#Hostages_Not_Rescued", "#Terrorists_Not_Escaped", "#VIP_Not_Escaped", "#Cannot_Buy_This", "#Not_Enough_Money", "#Weapon_Not_Available",
	"#Already_Have_Kevlar", "#Already_Have_Kevlar_Helmet", "#Already_Have_Kevlar_Bought_Helmet", "#Cannot_Carry_Anymore", "#Already_Have_One", "#Cannot_Switch_From_VIP", "#All_Teams_Full",
	"#Terrorists_Full", "#CTs_Full", "#Too_Many_Terrorists", "#Too_Many_CTs", "#Wait_3_Seconds", "#Only_1_Team_Change", "#Ignore_Broadcast_Messages", "#Ignore_Broadcast_Team_Messages",
	"#Accept_All_Messages", "#Ignore_Radio", "#Accept_Radio", "#Command_Not_Available", "#Defusing_Bomb_With_Defuse_Kit", "#Defusing_Bomb_Without_Defuse_Kit", "#Killed_Hostage",
	"#Injured_Hostage", "#Auto_Team_Balance_Next_Round", "#All_VIP_Slots_Full", "#Killed_Teammate", "#Banned_For_Killing_Teammates", "#Cannot_Vote_Map", "#Weapon_Cannot_Be_Dropped",
	"#Terrorist_Escaped", "#C4_Plant_At_Bomb_Spot", "#C4_Plant_Must_Be_On_Ground", "#C4_Arming_Cancelled", "#Bomb_Planted", "#C4_Activated_At_Bomb_Spot", "#Switch_To_BurstFire",
	"#Switch_To_SemiAuto", "#Switch_To_FullAuto", "#TRAINING1", "#TRAINING2", "#TRAINING3", "#TRAINING4", "#TRAINING5", "#TRAINING6", "#TRAINING7", "#GAMESAVED", "#Cannot_Vote_Need_More_People",
	"#Map_Vote_Extend", "#Cannot_Vote_With_Less_Than_Three", "#Cover_me", "#You_take_the_point", "#Hold_this_position", "#Regroup_team", "#Follow_me", "#Taking_fire", "#Go_go_go", "#Team_fall_back",
	"#Stick_together_team", "#Get_in_position_and_wait", "#Storm_the_front", "#Report_in_team", "#Affirmative", "#Roger_that", "#Enemy_spotted", "#Need_backup", "#Sector_clear", "#In_position",
	"#Reporting_in", "#Get_out_of_there", "#Negative", "#Enemy_down", "#Hostage_down", "#Fire_in_the_hole", "#Cant_buy", "#VIP_cant_buy", "#CT_cant_buy", "#Terrorist_cant_buy", "#Vote", "#Votes",
	"#Friend", "#Enemy", "#Hostage", "#Health", "#Map_descr_not_avail", "#Class_descr_not_avail", "#Phoenix_Connexion", "#L337_Krew", "#Arctic_Avengers", "#Guerilla_Warfare", "#Auto_Select",
	"#Seal_Team_6", "#GSG_9", "#SAS", "#GIGN", "#Kevlar", "#Kevlar_Vest", "#Kevlar_Helmet", "#Kevlar_Vest_Ballistic_Helmet", "#Flashbang", "#HE_Grenade", "#High_Explosive_Grenade", "#Smoke_Grenade",
	"#Defusal_Kit", "#Bomb_Defusal_Kit", "#NightVision", "#Nightvision_Goggles", "#TactShield", "#TactShield_Desc", "#Pistols", "#Buy_pistols", "#Shotguns", "#Buy_shotguns", "#SMGs", "#Buy_smgs",
	"#Rifles", "#Buy_rifles", "#MachineGuns", "#Buy_machineguns", "#Prim_Ammo", "#Buy_prim_ammo", "#Sec_Ammo", "#Buy_sec_ammo", "#Equipment", "#Buy_equipment", "#Terrorist_Forces", "#CT_Forces",
	"#VIP", "#WINS", "#BOMB", "#DEAD", "#SCORES", "#Player", "#Player_plural", "#Got_defuser", "#Got_bomb", "#Mic_Volume", "#Speaker_Volume", "#Voice_Properties", "#Cannot_Be_Spectator",
	"#Map_Description_not_available", "#Muted", "#Unmuted", "#No_longer_hear_that_player", "#OBS_NONE", "#OBS_CHASE_LOCKED", "#OBS_CHASE_FREE", "#OBS_ROAMING", "#OBS_IN_EYE", "#OBS_MAP_FREE",
	"#OBS_MAP_CHASE", "#SPECT_OPTIONS", "#CAM_OPTIONS", "#Name_change_at_respawn", "#C4_Defuse_Must_Be_On_Ground", "#Spectators", "#Unassigned", "#Only_CT_Can_Move_Hostages", "#Selection_Not_Available",
	"#Alias_Not_Avail", "T0A0TITLE", "C0A0TITLE", "C0A1TITLE", "C1A1TITLE", "C1A2TITLE", "C1A3TITLE", "C1A4TITLE", "C2A1TITLE", "C2A2TITLE", "C2A3TITLE", "C2A4TITLE1", "C2A4TITLE2", "C2A5TITLE",
	"C3A1TITLE", "C3A2TITLE", "C4A1TITLE", "C4A1ATITLE", "C4A2TITLE", "C4A3TITLE", "C5TITLE",

};

extern DLL_FUNCTIONS *g_pFunctionTable;

static server_static_t *global_svs;

static CVector<const char *> localize;

static int localize_string(char *buf, bool apersand);

static void (*pfnCmd_TokenizeString)(char *buf);

static inline void localize_push()
{
	int j = (sizeof(szLocalizeBuffer) / sizeof(szLocalizeBuffer[0]));

	for(int i = 0; i < j; i++)
		localize.push_back(szLocalizeBuffer[i]);
}

static inline char *getClientName(edict_t *pEdict)
{
	unsigned int p = ENTINDEX(pEdict) - 1;
	return (char *)(global_svs->clients + p * SIZEOF_CLIENT_T + PLAYER_NAME_OFFSET);
}

#endif // _MAIN_H_
