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

#define MAX_CLIENTS 32

#ifdef _WIN32
	#define SIZEOF_CLIENT_T 20504
	#define PLAYER_NAME_OFFSET 19720
#else
	#define SIZEOF_CLIENT_T 20212
	#define PLAYER_NAME_OFFSET 19432
#endif

typedef struct server_static_s
{
	int initialized;
	int clients;
	int maxclients;
	//[..]
} server_static_t;

const char *szLocalizeBuffer[] =
{
	"#GameUI_DetailTextures",
	"#Team_Select","#Team_Select_Spect","#IG_Team_Select","#IG_Team_Select_Spect","#IG_VIP_Team_Select","#IG_VIP_Team_Select_Spect","#Terrorist_Select",
	"#CT_Select","#Buy","#CT_BuyItem","#T_BuyItem","#DCT_BuyItem","#DT_BuyItem","#CT_BuyPistol","#T_BuyPistol","#AS_BuyShotgun","#BuyShotgun","#CT_BuySubMachineGun",
	"#T_BuySubMachineGun","#AS_CT_BuySubMachineGun","#AS_T_BuySubMachineGun","#T_BuyRifle","#CT_BuyRifle","#AS_T_BuyRifle","#AS_CT_BuyRifle","#AS_T_BuyMachineGun",
	"#BuyMachineGun","#RadioA","#RadioB","#RadioC","#AK47","#SG552","#M4A1","#Famas","#Galil","#Aug","#Scout","#ArcticWarfareMagnum","#G3SG1","#SG550","#USP45","#Glock18",
	"#DesertEagle","#P228","#Beretta96G","#FiveSeven","#Super90","#XM1014","#mp5navy","#tmp","#FNP90","#Mac10","#UMP45","#M249","#Krieg552","#M4A1_Short","#Schmidt","#Magnum",
	"#D3AU1","#Krieg550","#KM45Tactical","#Sidearm9X19mm","#NightHawk","#P228Compact","#Dual40","#ESFiveSeven","#Leone12","#AutoShotgun","#SubMachineGun","#SchmidtMP","#ESC90",
	"#Mac10_Short","#KMUMP45","#ESM249","#TEAMS","#PLAYERS","#CLASS","#SCORE","#DEATHS","#LATENCY","#VOICE","#Menu_OK","#Menu_Cancel","#Menu_Spectate","#Team_AutoAssign",
	"#Title_SelectYourTeam","#Target_Bombed","#VIP_Escaped","#VIP_Assassinated","#Terrorists_Escaped","#CTs_PreventEscape","#Escaping_Terrorists_Neutralized","#Bomb_Defused",
	"#CTs_Win","#Terrorists_Win","#Round_Draw","#All_Hostages_Rescued","#Target_Saved","#Hostages_Not_Rescued","#Terrorists_Not_Escaped","#VIP_Not_Escaped","#Cannot_Buy_This",
	"#Not_Enough_Money","#Weapon_Not_Available","#Already_Have_Kevlar","#Already_Have_Kevlar_Helmet","#Already_Have_Kevlar_Bought_Helmet","#Cannot_Carry_Anymore","#Already_Have_One",
	"#Cannot_Switch_From_VIP","#All_Teams_Full","#Terrorists_Full","#CTs_Full","#Too_Many_Terrorists","#Too_Many_CTs","#Wait_3_Seconds","#Only_1_Team_Change","#Ignore_Broadcast_Messages",
	"#Ignore_Broadcast_Team_Messages","#Accept_All_Messages","#Ignore_Radio","#Accept_Radio","#Command_Not_Available","#Defusing_Bomb_With_Defuse_Kit",
	"#Defusing_Bomb_Without_Defuse_Kit","#Killed_Hostage","#Injured_Hostage","#Auto_Team_Balance_Next_Round","#All_VIP_Slots_Full","#Killed_Teammate",
	"#Banned_For_Killing_Teammates","#Cannot_Vote_Map","#Weapon_Cannot_Be_Dropped","#Terrorist_Escaped","#C4_Plant_At_Bomb_Spot","#C4_Plant_Must_Be_On_Ground",
	"#C4_Arming_Cancelled","#Bomb_Planted","#C4_Activated_At_Bomb_Spot","#Switch_To_BurstFire","#Switch_To_SemiAuto","#Switch_To_FullAuto","#TRAINING1","#TRAINING2","#TRAINING3",
	"#TRAINING4","#TRAINING5","#TRAINING6","#TRAINING7","#GAMESAVED","#Game_Commencing","#Game_connected","#Game_disconnected","#Game_join_terrorist","#Game_join_ct",
	"#Game_join_terrorist_auto","#Game_join_ct_auto","#Game_scoring","#Game_idle_kick","#Game_bomb_drop","#Game_bomb_pickup","#Game_no_timelimit","#Game_timelimit",
	"#Game_unknown_command","#Game_in_position","#Game_added_position","#Game_teammate_kills","#Game_required_votes","#Game_radio","#Game_teammate_attack","#Game_kicked",
	"#Game_vote_cast","#Game_vote_usage","#Game_vote_player_not_found","#Game_vote_players_on_your_team","#Game_vote_not_yourself","#Game_voted_for_map","#Game_votemap_usage",
	"#Cannot_Vote_Need_More_People","#Map_Vote_Extend","#Cannot_Vote_With_Less_Than_Three","#Game_will_restart_in","#Game_will_restart_in_console","#Cover_me","#You_take_the_point",
	"#Hold_this_position","#Regroup_team","#Follow_me","#Taking_fire","#Go_go_go","#Team_fall_back","#Stick_together_team","#Get_in_position_and_wait","#Storm_the_front","#Report_in_team",
	"#Affirmative","#Roger_that","#Enemy_spotted","#Need_backup","#Sector_clear","#In_position","#Reporting_in","#Get_out_of_there","#Negative","#Enemy_down","#Hostage_down",
	"#Fire_in_the_hole","#Cant_buy","#VIP_cant_buy","#CT_cant_buy","#Terrorist_cant_buy","#Vote","#Votes","#Hint_press_buy_to_purchase","#Hint_use_nightvision","#Hint_lost_money",
	"#Hint_removed_for_next_hostage_killed","#Hint_careful_around_hostages","#Hint_careful_around_teammates","#Hint_reward_for_killing_vip","#Hint_win_round_by_killing_enemy",
	"#Hint_try_not_to_injure_teammates","#Hint_you_are_in_targetzone","#Hint_hostage_rescue_zone","#Hint_terrorist_escape_zone","#Hint_ct_vip_zone","#Hint_terrorist_vip_zone",
	"#Hint_cannot_play_because_tk","#Hint_use_hostage_to_stop_him","#Hint_lead_hostage_to_rescue_point","#Hint_you_have_the_bomb","#Hint_you_are_the_vip","#Hint_out_of_ammo",
	"#Hint_spotted_a_friend","#Hint_spotted_an_enemy","#Hint_prevent_hostage_rescue","#Hint_rescue_the_hostages","#Hint_press_use_so_hostage_will_follow","#Friend","#Enemy","#Hostage",
	"#Health","#Map_descr_not_avail","#Class_descr_not_avail","#Title_terrorist_model_selection","#Phoenix_Connexion","#L337_Krew","#Arctic_Avengers","#Guerilla_Warfare","#Auto_Select",
	"#Title_ct_model_selection","#Seal_Team_6","#Title_seal_team","#GSG_9","#Title_gsg9","#SAS","#Title_sas","#GIGN","#Title_gign","#Title_select_category_of_purchase",
	"#Title_equipment_selection","#Kevlar","#Kevlar_Vest","#Kevlar_Helmet","#Kevlar_Vest_Ballistic_Helmet","#Flashbang","#HE_Grenade","#High_Explosive_Grenade","#Smoke_Grenade",
	"#Defusal_Kit","#Bomb_Defusal_Kit","#NightVision","#Nightvision_Goggles","#TactShield","#TactShield_Desc","#Title_pistol_selection","#Pistols","#Buy_pistols",
	"#Title_shotgun_selection","#Shotguns","#Buy_shotguns","#Title_smg_selection","#SMGs","#Buy_smgs","#Title_rifle_selection","#Rifles","#Buy_rifles","#Title_machinegun_selection",
	"#MachineGuns","#Buy_machineguns","#Prim_Ammo","#Buy_prim_ammo","#Sec_Ammo","#Buy_sec_ammo","#Equipment","#Buy_equipment","#Terrorist_Forces","#CT_Forces","#VIP","#WINS","#BOMB","#DEAD",
	"#SCORES","#Player","#Player_plural","#Got_defuser","#Got_bomb","#Mic_Volume","#Speaker_Volume","#Voice_Properties","#Cannot_Be_Spectator","#Map_Description_not_available","#Muted",
	"#Unmuted","#No_longer_hear_that_player","#OBS_NONE","#OBS_CHASE_LOCKED","#OBS_CHASE_FREE","#OBS_ROAMING","#OBS_IN_EYE","#OBS_MAP_FREE","#OBS_MAP_CHASE","#SPECT_OPTIONS","#CAM_OPTIONS",
	"#Name_change_at_respawn","#C4_Defuse_Must_Be_On_Ground","#Spec_Mode1","#Spec_Mode2","#Spec_Mode3","#Spec_Mode4","#Spec_Mode5","#Spec_Mode6","#Spec_NoTarget","#Spec_Help_Title",
	"#Spec_Help_Text","#Spec_Slow_Motion","#Spec_Replay","#Spec_Auto","#Spec_Time","#Spec_Map","#Spectators","#Unassigned","#Only_CT_Can_Move_Hostages","#Spec_Duck",
	"#Spec_Not_Valid_Choice","#Spec_Not_In_Spectator_Mode","#Spec_NoPlayers","#Spec_ListPlayers","#Selection_Not_Available","#Alias_Not_Avail","#Spec_No_PIP"
};

extern DLL_FUNCTIONS *g_pFunctionTable;

static server_static_t *global_svs;

static CVector<const char *> localize;

static int localize_string(char *buf,bool apersand);

static void (*pfnCmd_TokenizeString)(char *buf);

static inline void localize_push()
{
	int j = (sizeof(szLocalizeBuffer) / sizeof(szLocalizeBuffer[0]));

	for(int i = 0; i < j; i++)
		localize.push_back(szLocalizeBuffer[i]);
};
static inline char *getClientName(edict_t *pEdict)
{
	unsigned int p = ENTINDEX(pEdict) - 1;
	return (char *)(global_svs->clients + p * SIZEOF_CLIENT_T + PLAYER_NAME_OFFSET);
}

#endif //_MAIN_H_

