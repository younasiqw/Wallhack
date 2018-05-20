#pragma once

#include "../../Engine/Engine.h"

class CMisc
{
public:
//[swap_lines]
	void OnCreateMove( CUserCmd* pCmd );

	vector<int> GetObservervators( int playerId );
//[/swap_lines]
};