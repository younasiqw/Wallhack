#pragma once

#include "../../Engine/Engine.h"

namespace Engine
{
	class CBaseEntity;
	class CPlayer;
}

using namespace Engine;

class CEsp
{
public:

	CEsp();
//[swap_lines]

	Color CT_HP_ColorM;
	Color TT_HP_ColorM;

	Color CT_AR_ColorM;
	Color TT_AR_ColorM;

	IMaterial* visible_flat;
	IMaterial* visible_tex;
	IMaterial* hidden_flat;
	IMaterial* hidden_tex;

	Color GetPlayerColor( CPlayer* pPlayer );
	Color GetPlayerColormisc(int k);
	Color GetPlayerVisibleColor( CPlayer* pPlayer );

	bool CheckPlayerTeam( CPlayer* pPlayer );

	void OnRender();
	void OnCreateMove( CUserCmd* pCmd );
	void OnDrawModelExecute( IMatRenderContext* ctx , const DrawModelState_t &state , const ModelRenderInfo_t &pInfo , matrix3x4_t *pCustomBoneToWorld = NULL );
	//[/swap_lines]
private:
//[swap_lines]
	void DrawPlayerEsp( CPlayer* pPlayer );
	void DrawPlayerSkeleton( CPlayer* pPlayer );
	void DrawPlayerBulletTrace( CPlayer* pPlayer );

	void DrawHitBoxLine( Vector* vHitBoxArray , Color color );
//[/swap_lines]
};