#pragma once

#include "../Main/Main.h"


namespace Settings
{
	namespace Esp
	{
		//[swap_lines]
		extern bool esp_style; // 0 - Box 1 - CoalBox
		extern int esp_Size;
		extern bool esp_Line;
		extern bool esp_Outline; // Box ( 0 - Box 1 - OutlineBox ) ,
						  // CoalBox ( 0 - CoalBox 1 - OutlineCoalBox )	
		extern bool espb;
		extern bool esp_Name;
		extern bool esp_Rank;
		extern bool esp_Health;
		extern bool esp_Armor;
		extern bool esp_Weapon;
		extern bool esp_Ammo;
		extern bool esp_Distance;
		extern bool esp_Sound;

		extern bool esp_Skeleton;
		extern int esp_BulletTrace;
		extern bool esp_Team;
		extern bool esp_Enemy;
		extern int esp_Visible;

		extern bool esp_chams;
		extern int esp_Chams;
		extern bool esp_Bomb;
		extern int esp_BombTimer;
		extern bool esp_WorldWeapons;
		extern bool esp_WorldGrenade;

		extern float esp_Color_CT[3];
		extern float esp_Color_TT[3];
		extern float esp_Color_VCT[3];
		extern float esp_Color_VTT[3];

		extern float chams_Color_CT[3];
		extern float chams_Color_TT[3];
		extern float chams_Color_VCT[3];
		extern float chams_Color_VTT[3];

		extern float esp_Color_Skeleton[3];
		extern float esp_Color_Text[3];
		//[/swap_lines]
	}

	namespace Misc
	{
		//[swap_lines]
		extern bool misc_Bhop;
		//[/swap_lines]
	}
}

//[enc_string_enable /]

#define HACK_NAME "Wallhack"

#define VISUAL_TEXT "Visual"
#define COLORMENU_TEXT "Colors"
#define MISC_TEXT "Misc"


#define CVAR_KEY_MOUSE3 "MOUSE3"
#define CVAR_KEY_MOUSE4 "MOUSE4"
#define CVAR_KEY_MOUSE5 "MOUSE5"

#define CVAR_ESP_STYLE "esp_Style"
#define CVAR_ESP_SIZE "esp_Size"
#define CVAR_ESP_LINE "esp_Line"
#define CVAR_ESP_OUTLINE "esp_Outline"
#define CVAR_ESP_NAME "esp_Name"
#define CVAR_ESP_RANK "esp_Rank"

#define CVAR_ESP_HEALTH "esp_Health"
#define CVAR_ESP_ARMOR "esp_Armor"
#define CVAR_ESP_WEAPON "esp_Weapon"
#define CVAR_ESP_AMMO "esp_Ammo"
#define CVAR_ESP_DISTANCE "esp_Distance"
#define CVAR_ESP_SOUND "esp_Sound"

#define CVAR_ESP_SKELETON "esp_Skeleton"
#define CVAR_ESP_BULLETTRACE "esp_BulletTrace"
#define CVAR_ESP_TEAM "esp_Team"
#define CVAR_ESP_ENEMY "esp_Enemy"
#define CVAR_ESP_VISIBLE "esp_Visible"

#define CVAR_ESP_CHAMS "esp_Chams"
#define CVAR_ESP_BOMB "esp_Bomb"
#define CVAR_ESP_BOMBTIMER "esp_BombTimer"
#define CVAR_ESP_WORLDWEAPONS "esp_WorldWeapons"
#define CVAR_ESP_WORLDGRENADE "esp_WorldGrenade"

#define CVAR_ESP_COLOR_CT "esp_Color_CT"
#define CVAR_ESP_COLOR_TT "esp_Color_TT"
#define CVAR_ESP_COLOR_VCT "esp_Color_VCT"
#define CVAR_ESP_COLOR_VTT "esp_Color_VTT"

#define CVAR_CHAMS_COLOR_CT "chams_Color_CT"
#define CVAR_CHAMS_COLOR_TT "chams_Color_TT"
#define CVAR_CHAMS_COLOR_VCT "chams_Color_VCT"
#define CVAR_CHAMS_COLOR_VTT "chams_Color_VTT"

#define C4_TIMER_STRING "C4 Timer: %0.2f"

#define CVAR_MISC_BHOP "misc_Bhop"
