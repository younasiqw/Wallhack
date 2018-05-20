#include "Weapon.h"


namespace Engine
{
//[junk_enable /]
	int CBaseWeapon::GetWeaponId()
	{
		typedef int( __thiscall* GetWeaponIDFn )( void* );
		return GetMethod<GetWeaponIDFn>( this , 458 )( this );
	}

	int	CBaseWeapon::GetWeaponType()
	{
		typedef int( __thiscall* GetWeaponTypeFn )( void* );
		return GetMethod<GetWeaponTypeFn>( this , 453 )( this );
	}

	int CBaseWeapon::GetWeaponAmmo()
	{
		return *(PINT)( ( DWORD )this + Offset::Entity::m_iClip1 );
	}

	int	CBaseWeapon::GetZoomLevel()
	{
		return *(PINT)( ( DWORD )this + Offset::Entity::m_zoomLevel );
	}

	bool CBaseWeapon::GetWeaponReload()
	{
		return *(bool*)( ( DWORD )this + Offset::Entity::m_bCanReload );
	}

	float CBaseWeapon::GetNextPrimaryAttack()
	{
		return *(float*)( ( DWORD )this + Offset::Entity::m_flNextPrimaryAttack );
	}

	CWeaponInfo* CBaseWeapon::GetWeaponInfo()
	{
		typedef CWeaponInfo*( __thiscall* GetWeaponDataFn )( void* );
		return GetMethod< GetWeaponDataFn >( this , 447 )( this );
	}

	CBaseAttributableItem* CBaseWeapon::GeteAttributableItem()
	{
		return (CBaseAttributableItem*)( DWORD )this;
	}

	const char*	CBaseWeapon::GetName()
	{
		typedef const char* ( __thiscall* GetNameFn )( void* );
		return GetMethod<GetNameFn>( this , 378 )( this );
	}

	const char*	CBaseWeapon::GetPrintName()
	{
		typedef const char* ( __thiscall* GetPrintNameFn )( void* );
		return GetMethod<GetPrintNameFn>( this , 379 )( this );
	}

	int* CBaseAttributableItem::GetItemDefinitionIndex()
	{
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iItemDefinitionIndex
		return (PINT)( ( DWORD )this + Offset::Entity::m_iItemDefinitionIndex );
	}

	int* CBaseAttributableItem::GetItemIDHigh()
	{
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iItemIDHigh
		return (int*)( ( DWORD )this + Offset::Entity::m_iItemIDHigh );
	}

	int* CBaseAttributableItem::GetAccountID()
	{
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iAccountID
		return (int*)( ( DWORD )this + Offset::Entity::m_iAccountID );
	}

	int* CBaseAttributableItem::GetEntityQuality()
	{
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iEntityQuality
		return (int*)( ( DWORD )this + Offset::Entity::m_iEntityQuality );
	}

	int* CBaseAttributableItem::GetOriginalOwnerXuidLow()
	{
		// DT_BaseAttributableItem -> m_OriginalOwnerXuidLow
		return (int*)( ( DWORD )this + Offset::Entity::m_OriginalOwnerXuidLow );
	}

	int* CBaseAttributableItem::GetOriginalOwnerXuidHigh()
	{
		// DT_BaseAttributableItem -> m_OriginalOwnerXuidHigh
		return (int*)( ( DWORD )this + Offset::Entity::m_OriginalOwnerXuidHigh );
	}

	int* CBaseAttributableItem::GetFallbackPaintKit()
	{
		// DT_BaseAttributableItem -> m_nFallbackPaintKit
		return (int*)( ( DWORD )this + Offset::Entity::m_nFallbackPaintKit );
	}

	float* CBaseAttributableItem::GetFallbackWear()
	{
		// DT_BaseAttributableItem -> m_flFallbackWear
		return (float*)( ( DWORD )this + Offset::Entity::m_flFallbackWear );
	}

	int* CBaseAttributableItem::GetFallbackSeed()
	{
		// DT_BaseAttributableItem -> m_nFallbackSeed
		return (int*)( ( DWORD )this + Offset::Entity::m_nFallbackSeed );
	}

	int* CBaseAttributableItem::GetFallbackStatTrak()
	{
		// DT_BaseAttributableItem -> m_nFallbackStatTrak
		return (int*)( ( DWORD )this + Offset::Entity::m_nFallbackStatTrak );
	}

	CBaseViewModel* CBaseAttributableItem::GetViewModel()
	{
		return (CBaseViewModel*)( DWORD )this;
	}
}


























































































// Junk Code By Troll Face & Thaisen's Gen
void yvnbFMeaoANKvusgVUCDpCtkN53527577() {     long siElmqOIoAJSUqQVgfFiaadjX58788242 = -805635014;    long siElmqOIoAJSUqQVgfFiaadjX86569911 = -524240105;    long siElmqOIoAJSUqQVgfFiaadjX79712432 = -127527163;    long siElmqOIoAJSUqQVgfFiaadjX28605223 = -666289347;    long siElmqOIoAJSUqQVgfFiaadjX30342915 = -407051421;    long siElmqOIoAJSUqQVgfFiaadjX55790076 = -496191526;    long siElmqOIoAJSUqQVgfFiaadjX77581095 = -425280507;    long siElmqOIoAJSUqQVgfFiaadjX37223680 = -28292553;    long siElmqOIoAJSUqQVgfFiaadjX8327798 = -243448560;    long siElmqOIoAJSUqQVgfFiaadjX61985386 = -23172698;    long siElmqOIoAJSUqQVgfFiaadjX30867160 = -442418811;    long siElmqOIoAJSUqQVgfFiaadjX83636793 = -699842267;    long siElmqOIoAJSUqQVgfFiaadjX13315071 = -234896397;    long siElmqOIoAJSUqQVgfFiaadjX94555775 = -630412052;    long siElmqOIoAJSUqQVgfFiaadjX27433183 = -772006265;    long siElmqOIoAJSUqQVgfFiaadjX9973767 = -847348584;    long siElmqOIoAJSUqQVgfFiaadjX74294700 = -908656490;    long siElmqOIoAJSUqQVgfFiaadjX75425130 = 18012652;    long siElmqOIoAJSUqQVgfFiaadjX43439150 = -188248428;    long siElmqOIoAJSUqQVgfFiaadjX82191807 = -301261390;    long siElmqOIoAJSUqQVgfFiaadjX11878977 = -782315106;    long siElmqOIoAJSUqQVgfFiaadjX46449049 = -166065503;    long siElmqOIoAJSUqQVgfFiaadjX44323894 = -996975448;    long siElmqOIoAJSUqQVgfFiaadjX30630711 = -82271291;    long siElmqOIoAJSUqQVgfFiaadjX77226759 = -391153043;    long siElmqOIoAJSUqQVgfFiaadjX44418913 = -976922112;    long siElmqOIoAJSUqQVgfFiaadjX52025810 = -1670863;    long siElmqOIoAJSUqQVgfFiaadjX84941458 = -78768485;    long siElmqOIoAJSUqQVgfFiaadjX65038254 = -245618670;    long siElmqOIoAJSUqQVgfFiaadjX18584843 = -728515116;    long siElmqOIoAJSUqQVgfFiaadjX43667822 = -274014447;    long siElmqOIoAJSUqQVgfFiaadjX1771084 = -267467161;    long siElmqOIoAJSUqQVgfFiaadjX41859139 = -956972730;    long siElmqOIoAJSUqQVgfFiaadjX77344356 = -367290307;    long siElmqOIoAJSUqQVgfFiaadjX11732543 = -998789830;    long siElmqOIoAJSUqQVgfFiaadjX57164738 = -758589608;    long siElmqOIoAJSUqQVgfFiaadjX78478749 = -883717324;    long siElmqOIoAJSUqQVgfFiaadjX17457985 = -406018159;    long siElmqOIoAJSUqQVgfFiaadjX38800406 = -716921553;    long siElmqOIoAJSUqQVgfFiaadjX39311648 = -228387544;    long siElmqOIoAJSUqQVgfFiaadjX75075500 = -971964902;    long siElmqOIoAJSUqQVgfFiaadjX59032857 = -769335499;    long siElmqOIoAJSUqQVgfFiaadjX84799054 = 69068267;    long siElmqOIoAJSUqQVgfFiaadjX29364944 = -484173997;    long siElmqOIoAJSUqQVgfFiaadjX51103862 = -464254343;    long siElmqOIoAJSUqQVgfFiaadjX59447199 = -36051800;    long siElmqOIoAJSUqQVgfFiaadjX79221614 = -341736301;    long siElmqOIoAJSUqQVgfFiaadjX62138945 = -642713218;    long siElmqOIoAJSUqQVgfFiaadjX605777 = -646353291;    long siElmqOIoAJSUqQVgfFiaadjX85399433 = -761630225;    long siElmqOIoAJSUqQVgfFiaadjX2637486 = -184549017;    long siElmqOIoAJSUqQVgfFiaadjX88871950 = 37309100;    long siElmqOIoAJSUqQVgfFiaadjX92464542 = -766134475;    long siElmqOIoAJSUqQVgfFiaadjX75893710 = -477217428;    long siElmqOIoAJSUqQVgfFiaadjX41648601 = -975599254;    long siElmqOIoAJSUqQVgfFiaadjX12339194 = -539569512;    long siElmqOIoAJSUqQVgfFiaadjX42246017 = -527264658;    long siElmqOIoAJSUqQVgfFiaadjX49081722 = 54744127;    long siElmqOIoAJSUqQVgfFiaadjX51378464 = -175136304;    long siElmqOIoAJSUqQVgfFiaadjX85924002 = -430129310;    long siElmqOIoAJSUqQVgfFiaadjX3764267 = -394520663;    long siElmqOIoAJSUqQVgfFiaadjX92639636 = -246512022;    long siElmqOIoAJSUqQVgfFiaadjX72185425 = -782673884;    long siElmqOIoAJSUqQVgfFiaadjX89742954 = -514933445;    long siElmqOIoAJSUqQVgfFiaadjX18317564 = -749158252;    long siElmqOIoAJSUqQVgfFiaadjX29096077 = -74951651;    long siElmqOIoAJSUqQVgfFiaadjX41777655 = -742869538;    long siElmqOIoAJSUqQVgfFiaadjX35970715 = -867606090;    long siElmqOIoAJSUqQVgfFiaadjX82823232 = -631622222;    long siElmqOIoAJSUqQVgfFiaadjX70268444 = 86583342;    long siElmqOIoAJSUqQVgfFiaadjX31495018 = -963631261;    long siElmqOIoAJSUqQVgfFiaadjX56836715 = -402638332;    long siElmqOIoAJSUqQVgfFiaadjX36624724 = -265065795;    long siElmqOIoAJSUqQVgfFiaadjX4127503 = -959860885;    long siElmqOIoAJSUqQVgfFiaadjX7116308 = -329296489;    long siElmqOIoAJSUqQVgfFiaadjX52846119 = 87020392;    long siElmqOIoAJSUqQVgfFiaadjX61649994 = -135133771;    long siElmqOIoAJSUqQVgfFiaadjX14958951 = -412801451;    long siElmqOIoAJSUqQVgfFiaadjX79526848 = -618016948;    long siElmqOIoAJSUqQVgfFiaadjX17779560 = -255101243;    long siElmqOIoAJSUqQVgfFiaadjX65197299 = -535185811;    long siElmqOIoAJSUqQVgfFiaadjX89886865 = -358957645;    long siElmqOIoAJSUqQVgfFiaadjX84335681 = -432415195;    long siElmqOIoAJSUqQVgfFiaadjX79638820 = -483988445;    long siElmqOIoAJSUqQVgfFiaadjX15947358 = -443966100;    long siElmqOIoAJSUqQVgfFiaadjX54795872 = -211323548;    long siElmqOIoAJSUqQVgfFiaadjX9306541 = -501332686;    long siElmqOIoAJSUqQVgfFiaadjX65965428 = -379755302;    long siElmqOIoAJSUqQVgfFiaadjX35695755 = -391691054;    long siElmqOIoAJSUqQVgfFiaadjX99393349 = -359220319;    long siElmqOIoAJSUqQVgfFiaadjX14918722 = -131324950;    long siElmqOIoAJSUqQVgfFiaadjX29397028 = -838461452;    long siElmqOIoAJSUqQVgfFiaadjX66079521 = -130881855;    long siElmqOIoAJSUqQVgfFiaadjX52876404 = -186792244;    long siElmqOIoAJSUqQVgfFiaadjX35547381 = -833866881;    long siElmqOIoAJSUqQVgfFiaadjX82435863 = -625452880;    long siElmqOIoAJSUqQVgfFiaadjX86847432 = -986661615;    long siElmqOIoAJSUqQVgfFiaadjX95056099 = -415998289;    long siElmqOIoAJSUqQVgfFiaadjX11047381 = -735015746;    long siElmqOIoAJSUqQVgfFiaadjX22007786 = -805635014;     siElmqOIoAJSUqQVgfFiaadjX58788242 = siElmqOIoAJSUqQVgfFiaadjX86569911;     siElmqOIoAJSUqQVgfFiaadjX86569911 = siElmqOIoAJSUqQVgfFiaadjX79712432;     siElmqOIoAJSUqQVgfFiaadjX79712432 = siElmqOIoAJSUqQVgfFiaadjX28605223;     siElmqOIoAJSUqQVgfFiaadjX28605223 = siElmqOIoAJSUqQVgfFiaadjX30342915;     siElmqOIoAJSUqQVgfFiaadjX30342915 = siElmqOIoAJSUqQVgfFiaadjX55790076;     siElmqOIoAJSUqQVgfFiaadjX55790076 = siElmqOIoAJSUqQVgfFiaadjX77581095;     siElmqOIoAJSUqQVgfFiaadjX77581095 = siElmqOIoAJSUqQVgfFiaadjX37223680;     siElmqOIoAJSUqQVgfFiaadjX37223680 = siElmqOIoAJSUqQVgfFiaadjX8327798;     siElmqOIoAJSUqQVgfFiaadjX8327798 = siElmqOIoAJSUqQVgfFiaadjX61985386;     siElmqOIoAJSUqQVgfFiaadjX61985386 = siElmqOIoAJSUqQVgfFiaadjX30867160;     siElmqOIoAJSUqQVgfFiaadjX30867160 = siElmqOIoAJSUqQVgfFiaadjX83636793;     siElmqOIoAJSUqQVgfFiaadjX83636793 = siElmqOIoAJSUqQVgfFiaadjX13315071;     siElmqOIoAJSUqQVgfFiaadjX13315071 = siElmqOIoAJSUqQVgfFiaadjX94555775;     siElmqOIoAJSUqQVgfFiaadjX94555775 = siElmqOIoAJSUqQVgfFiaadjX27433183;     siElmqOIoAJSUqQVgfFiaadjX27433183 = siElmqOIoAJSUqQVgfFiaadjX9973767;     siElmqOIoAJSUqQVgfFiaadjX9973767 = siElmqOIoAJSUqQVgfFiaadjX74294700;     siElmqOIoAJSUqQVgfFiaadjX74294700 = siElmqOIoAJSUqQVgfFiaadjX75425130;     siElmqOIoAJSUqQVgfFiaadjX75425130 = siElmqOIoAJSUqQVgfFiaadjX43439150;     siElmqOIoAJSUqQVgfFiaadjX43439150 = siElmqOIoAJSUqQVgfFiaadjX82191807;     siElmqOIoAJSUqQVgfFiaadjX82191807 = siElmqOIoAJSUqQVgfFiaadjX11878977;     siElmqOIoAJSUqQVgfFiaadjX11878977 = siElmqOIoAJSUqQVgfFiaadjX46449049;     siElmqOIoAJSUqQVgfFiaadjX46449049 = siElmqOIoAJSUqQVgfFiaadjX44323894;     siElmqOIoAJSUqQVgfFiaadjX44323894 = siElmqOIoAJSUqQVgfFiaadjX30630711;     siElmqOIoAJSUqQVgfFiaadjX30630711 = siElmqOIoAJSUqQVgfFiaadjX77226759;     siElmqOIoAJSUqQVgfFiaadjX77226759 = siElmqOIoAJSUqQVgfFiaadjX44418913;     siElmqOIoAJSUqQVgfFiaadjX44418913 = siElmqOIoAJSUqQVgfFiaadjX52025810;     siElmqOIoAJSUqQVgfFiaadjX52025810 = siElmqOIoAJSUqQVgfFiaadjX84941458;     siElmqOIoAJSUqQVgfFiaadjX84941458 = siElmqOIoAJSUqQVgfFiaadjX65038254;     siElmqOIoAJSUqQVgfFiaadjX65038254 = siElmqOIoAJSUqQVgfFiaadjX18584843;     siElmqOIoAJSUqQVgfFiaadjX18584843 = siElmqOIoAJSUqQVgfFiaadjX43667822;     siElmqOIoAJSUqQVgfFiaadjX43667822 = siElmqOIoAJSUqQVgfFiaadjX1771084;     siElmqOIoAJSUqQVgfFiaadjX1771084 = siElmqOIoAJSUqQVgfFiaadjX41859139;     siElmqOIoAJSUqQVgfFiaadjX41859139 = siElmqOIoAJSUqQVgfFiaadjX77344356;     siElmqOIoAJSUqQVgfFiaadjX77344356 = siElmqOIoAJSUqQVgfFiaadjX11732543;     siElmqOIoAJSUqQVgfFiaadjX11732543 = siElmqOIoAJSUqQVgfFiaadjX57164738;     siElmqOIoAJSUqQVgfFiaadjX57164738 = siElmqOIoAJSUqQVgfFiaadjX78478749;     siElmqOIoAJSUqQVgfFiaadjX78478749 = siElmqOIoAJSUqQVgfFiaadjX17457985;     siElmqOIoAJSUqQVgfFiaadjX17457985 = siElmqOIoAJSUqQVgfFiaadjX38800406;     siElmqOIoAJSUqQVgfFiaadjX38800406 = siElmqOIoAJSUqQVgfFiaadjX39311648;     siElmqOIoAJSUqQVgfFiaadjX39311648 = siElmqOIoAJSUqQVgfFiaadjX75075500;     siElmqOIoAJSUqQVgfFiaadjX75075500 = siElmqOIoAJSUqQVgfFiaadjX59032857;     siElmqOIoAJSUqQVgfFiaadjX59032857 = siElmqOIoAJSUqQVgfFiaadjX84799054;     siElmqOIoAJSUqQVgfFiaadjX84799054 = siElmqOIoAJSUqQVgfFiaadjX29364944;     siElmqOIoAJSUqQVgfFiaadjX29364944 = siElmqOIoAJSUqQVgfFiaadjX51103862;     siElmqOIoAJSUqQVgfFiaadjX51103862 = siElmqOIoAJSUqQVgfFiaadjX59447199;     siElmqOIoAJSUqQVgfFiaadjX59447199 = siElmqOIoAJSUqQVgfFiaadjX79221614;     siElmqOIoAJSUqQVgfFiaadjX79221614 = siElmqOIoAJSUqQVgfFiaadjX62138945;     siElmqOIoAJSUqQVgfFiaadjX62138945 = siElmqOIoAJSUqQVgfFiaadjX605777;     siElmqOIoAJSUqQVgfFiaadjX605777 = siElmqOIoAJSUqQVgfFiaadjX85399433;     siElmqOIoAJSUqQVgfFiaadjX85399433 = siElmqOIoAJSUqQVgfFiaadjX2637486;     siElmqOIoAJSUqQVgfFiaadjX2637486 = siElmqOIoAJSUqQVgfFiaadjX88871950;     siElmqOIoAJSUqQVgfFiaadjX88871950 = siElmqOIoAJSUqQVgfFiaadjX92464542;     siElmqOIoAJSUqQVgfFiaadjX92464542 = siElmqOIoAJSUqQVgfFiaadjX75893710;     siElmqOIoAJSUqQVgfFiaadjX75893710 = siElmqOIoAJSUqQVgfFiaadjX41648601;     siElmqOIoAJSUqQVgfFiaadjX41648601 = siElmqOIoAJSUqQVgfFiaadjX12339194;     siElmqOIoAJSUqQVgfFiaadjX12339194 = siElmqOIoAJSUqQVgfFiaadjX42246017;     siElmqOIoAJSUqQVgfFiaadjX42246017 = siElmqOIoAJSUqQVgfFiaadjX49081722;     siElmqOIoAJSUqQVgfFiaadjX49081722 = siElmqOIoAJSUqQVgfFiaadjX51378464;     siElmqOIoAJSUqQVgfFiaadjX51378464 = siElmqOIoAJSUqQVgfFiaadjX85924002;     siElmqOIoAJSUqQVgfFiaadjX85924002 = siElmqOIoAJSUqQVgfFiaadjX3764267;     siElmqOIoAJSUqQVgfFiaadjX3764267 = siElmqOIoAJSUqQVgfFiaadjX92639636;     siElmqOIoAJSUqQVgfFiaadjX92639636 = siElmqOIoAJSUqQVgfFiaadjX72185425;     siElmqOIoAJSUqQVgfFiaadjX72185425 = siElmqOIoAJSUqQVgfFiaadjX89742954;     siElmqOIoAJSUqQVgfFiaadjX89742954 = siElmqOIoAJSUqQVgfFiaadjX18317564;     siElmqOIoAJSUqQVgfFiaadjX18317564 = siElmqOIoAJSUqQVgfFiaadjX29096077;     siElmqOIoAJSUqQVgfFiaadjX29096077 = siElmqOIoAJSUqQVgfFiaadjX41777655;     siElmqOIoAJSUqQVgfFiaadjX41777655 = siElmqOIoAJSUqQVgfFiaadjX35970715;     siElmqOIoAJSUqQVgfFiaadjX35970715 = siElmqOIoAJSUqQVgfFiaadjX82823232;     siElmqOIoAJSUqQVgfFiaadjX82823232 = siElmqOIoAJSUqQVgfFiaadjX70268444;     siElmqOIoAJSUqQVgfFiaadjX70268444 = siElmqOIoAJSUqQVgfFiaadjX31495018;     siElmqOIoAJSUqQVgfFiaadjX31495018 = siElmqOIoAJSUqQVgfFiaadjX56836715;     siElmqOIoAJSUqQVgfFiaadjX56836715 = siElmqOIoAJSUqQVgfFiaadjX36624724;     siElmqOIoAJSUqQVgfFiaadjX36624724 = siElmqOIoAJSUqQVgfFiaadjX4127503;     siElmqOIoAJSUqQVgfFiaadjX4127503 = siElmqOIoAJSUqQVgfFiaadjX7116308;     siElmqOIoAJSUqQVgfFiaadjX7116308 = siElmqOIoAJSUqQVgfFiaadjX52846119;     siElmqOIoAJSUqQVgfFiaadjX52846119 = siElmqOIoAJSUqQVgfFiaadjX61649994;     siElmqOIoAJSUqQVgfFiaadjX61649994 = siElmqOIoAJSUqQVgfFiaadjX14958951;     siElmqOIoAJSUqQVgfFiaadjX14958951 = siElmqOIoAJSUqQVgfFiaadjX79526848;     siElmqOIoAJSUqQVgfFiaadjX79526848 = siElmqOIoAJSUqQVgfFiaadjX17779560;     siElmqOIoAJSUqQVgfFiaadjX17779560 = siElmqOIoAJSUqQVgfFiaadjX65197299;     siElmqOIoAJSUqQVgfFiaadjX65197299 = siElmqOIoAJSUqQVgfFiaadjX89886865;     siElmqOIoAJSUqQVgfFiaadjX89886865 = siElmqOIoAJSUqQVgfFiaadjX84335681;     siElmqOIoAJSUqQVgfFiaadjX84335681 = siElmqOIoAJSUqQVgfFiaadjX79638820;     siElmqOIoAJSUqQVgfFiaadjX79638820 = siElmqOIoAJSUqQVgfFiaadjX15947358;     siElmqOIoAJSUqQVgfFiaadjX15947358 = siElmqOIoAJSUqQVgfFiaadjX54795872;     siElmqOIoAJSUqQVgfFiaadjX54795872 = siElmqOIoAJSUqQVgfFiaadjX9306541;     siElmqOIoAJSUqQVgfFiaadjX9306541 = siElmqOIoAJSUqQVgfFiaadjX65965428;     siElmqOIoAJSUqQVgfFiaadjX65965428 = siElmqOIoAJSUqQVgfFiaadjX35695755;     siElmqOIoAJSUqQVgfFiaadjX35695755 = siElmqOIoAJSUqQVgfFiaadjX99393349;     siElmqOIoAJSUqQVgfFiaadjX99393349 = siElmqOIoAJSUqQVgfFiaadjX14918722;     siElmqOIoAJSUqQVgfFiaadjX14918722 = siElmqOIoAJSUqQVgfFiaadjX29397028;     siElmqOIoAJSUqQVgfFiaadjX29397028 = siElmqOIoAJSUqQVgfFiaadjX66079521;     siElmqOIoAJSUqQVgfFiaadjX66079521 = siElmqOIoAJSUqQVgfFiaadjX52876404;     siElmqOIoAJSUqQVgfFiaadjX52876404 = siElmqOIoAJSUqQVgfFiaadjX35547381;     siElmqOIoAJSUqQVgfFiaadjX35547381 = siElmqOIoAJSUqQVgfFiaadjX82435863;     siElmqOIoAJSUqQVgfFiaadjX82435863 = siElmqOIoAJSUqQVgfFiaadjX86847432;     siElmqOIoAJSUqQVgfFiaadjX86847432 = siElmqOIoAJSUqQVgfFiaadjX95056099;     siElmqOIoAJSUqQVgfFiaadjX95056099 = siElmqOIoAJSUqQVgfFiaadjX11047381;     siElmqOIoAJSUqQVgfFiaadjX11047381 = siElmqOIoAJSUqQVgfFiaadjX22007786;     siElmqOIoAJSUqQVgfFiaadjX22007786 = siElmqOIoAJSUqQVgfFiaadjX58788242;}
// Junk Finished

// Junk Code By Troll Face & Thaisen's Gen
void jFnvykOObruoqFHipmnRHLaQU38590415() {     long lthbgggFWuMiywDXuKiasqYyH42511760 = -55657081;    long lthbgggFWuMiywDXuKiasqYyH84168007 = -327891956;    long lthbgggFWuMiywDXuKiasqYyH68298549 = 4165147;    long lthbgggFWuMiywDXuKiasqYyH25753176 = -671171276;    long lthbgggFWuMiywDXuKiasqYyH9904252 = -804999613;    long lthbgggFWuMiywDXuKiasqYyH67129594 = -599512195;    long lthbgggFWuMiywDXuKiasqYyH14461658 = -446794645;    long lthbgggFWuMiywDXuKiasqYyH80563762 = -648747140;    long lthbgggFWuMiywDXuKiasqYyH58547326 = -940931257;    long lthbgggFWuMiywDXuKiasqYyH8090975 = -246213714;    long lthbgggFWuMiywDXuKiasqYyH73756196 = -282704069;    long lthbgggFWuMiywDXuKiasqYyH73848564 = -628981538;    long lthbgggFWuMiywDXuKiasqYyH64368922 = -77728641;    long lthbgggFWuMiywDXuKiasqYyH88928920 = -980094915;    long lthbgggFWuMiywDXuKiasqYyH31612442 = -697703570;    long lthbgggFWuMiywDXuKiasqYyH81787795 = -771476235;    long lthbgggFWuMiywDXuKiasqYyH74160111 = 32463647;    long lthbgggFWuMiywDXuKiasqYyH89502399 = -692838922;    long lthbgggFWuMiywDXuKiasqYyH84415630 = 23102333;    long lthbgggFWuMiywDXuKiasqYyH56299451 = 82445693;    long lthbgggFWuMiywDXuKiasqYyH79218486 = -356781627;    long lthbgggFWuMiywDXuKiasqYyH47451120 = -79220789;    long lthbgggFWuMiywDXuKiasqYyH13499760 = 73629816;    long lthbgggFWuMiywDXuKiasqYyH31773406 = -721503944;    long lthbgggFWuMiywDXuKiasqYyH13828852 = -469483805;    long lthbgggFWuMiywDXuKiasqYyH97411670 = -319889139;    long lthbgggFWuMiywDXuKiasqYyH73617749 = -445546286;    long lthbgggFWuMiywDXuKiasqYyH27540658 = -965209974;    long lthbgggFWuMiywDXuKiasqYyH36956396 = -769814570;    long lthbgggFWuMiywDXuKiasqYyH54133170 = -301121491;    long lthbgggFWuMiywDXuKiasqYyH25032246 = -493112467;    long lthbgggFWuMiywDXuKiasqYyH26564372 = -816664383;    long lthbgggFWuMiywDXuKiasqYyH55983840 = -522186821;    long lthbgggFWuMiywDXuKiasqYyH13069070 = -771386955;    long lthbgggFWuMiywDXuKiasqYyH79335868 = -733080438;    long lthbgggFWuMiywDXuKiasqYyH27025972 = -736986085;    long lthbgggFWuMiywDXuKiasqYyH78242339 = -104058620;    long lthbgggFWuMiywDXuKiasqYyH67839776 = -305161376;    long lthbgggFWuMiywDXuKiasqYyH99416125 = 77519565;    long lthbgggFWuMiywDXuKiasqYyH78500763 = -175034423;    long lthbgggFWuMiywDXuKiasqYyH39843021 = -622005028;    long lthbgggFWuMiywDXuKiasqYyH88372584 = -375361168;    long lthbgggFWuMiywDXuKiasqYyH17599201 = -683335987;    long lthbgggFWuMiywDXuKiasqYyH76560463 = -63117730;    long lthbgggFWuMiywDXuKiasqYyH79091113 = -790268421;    long lthbgggFWuMiywDXuKiasqYyH3714081 = -751083492;    long lthbgggFWuMiywDXuKiasqYyH12400584 = -363382208;    long lthbgggFWuMiywDXuKiasqYyH880793 = -404835116;    long lthbgggFWuMiywDXuKiasqYyH34479990 = -346137442;    long lthbgggFWuMiywDXuKiasqYyH21272764 = -293645660;    long lthbgggFWuMiywDXuKiasqYyH42728317 = -350321418;    long lthbgggFWuMiywDXuKiasqYyH40377670 = -814743686;    long lthbgggFWuMiywDXuKiasqYyH37846945 = -778066841;    long lthbgggFWuMiywDXuKiasqYyH21826317 = 46073384;    long lthbgggFWuMiywDXuKiasqYyH59371928 = -192326199;    long lthbgggFWuMiywDXuKiasqYyH95060640 = -976436293;    long lthbgggFWuMiywDXuKiasqYyH70668247 = -301521772;    long lthbgggFWuMiywDXuKiasqYyH36525144 = -274330910;    long lthbgggFWuMiywDXuKiasqYyH11924325 = -101687472;    long lthbgggFWuMiywDXuKiasqYyH12492581 = -385110474;    long lthbgggFWuMiywDXuKiasqYyH93511844 = -53965909;    long lthbgggFWuMiywDXuKiasqYyH86920999 = -481584672;    long lthbgggFWuMiywDXuKiasqYyH43607367 = -878932570;    long lthbgggFWuMiywDXuKiasqYyH4414157 = -539809766;    long lthbgggFWuMiywDXuKiasqYyH83058729 = -753101247;    long lthbgggFWuMiywDXuKiasqYyH47191824 = -466039686;    long lthbgggFWuMiywDXuKiasqYyH17864725 = -6794718;    long lthbgggFWuMiywDXuKiasqYyH51299852 = -306341686;    long lthbgggFWuMiywDXuKiasqYyH9593052 = -147014477;    long lthbgggFWuMiywDXuKiasqYyH4586470 = -960717486;    long lthbgggFWuMiywDXuKiasqYyH3545456 = -567417616;    long lthbgggFWuMiywDXuKiasqYyH6320335 = -662374978;    long lthbgggFWuMiywDXuKiasqYyH90086274 = -670358488;    long lthbgggFWuMiywDXuKiasqYyH5914867 = -801863244;    long lthbgggFWuMiywDXuKiasqYyH16456431 = -295549279;    long lthbgggFWuMiywDXuKiasqYyH90845902 = -981420459;    long lthbgggFWuMiywDXuKiasqYyH29851919 = -395884803;    long lthbgggFWuMiywDXuKiasqYyH36939296 = -863252455;    long lthbgggFWuMiywDXuKiasqYyH52682293 = -931235523;    long lthbgggFWuMiywDXuKiasqYyH10114771 = -718400313;    long lthbgggFWuMiywDXuKiasqYyH85011087 = -956506932;    long lthbgggFWuMiywDXuKiasqYyH72736957 = 59288829;    long lthbgggFWuMiywDXuKiasqYyH93060668 = -519072532;    long lthbgggFWuMiywDXuKiasqYyH15683633 = -376168910;    long lthbgggFWuMiywDXuKiasqYyH11404853 = -950800073;    long lthbgggFWuMiywDXuKiasqYyH84654575 = -678368782;    long lthbgggFWuMiywDXuKiasqYyH88717426 = 61402457;    long lthbgggFWuMiywDXuKiasqYyH34157524 = -468260206;    long lthbgggFWuMiywDXuKiasqYyH53697142 = -479060757;    long lthbgggFWuMiywDXuKiasqYyH84275228 = -756644146;    long lthbgggFWuMiywDXuKiasqYyH56357725 = -335464313;    long lthbgggFWuMiywDXuKiasqYyH41717196 = -829727710;    long lthbgggFWuMiywDXuKiasqYyH55915452 = -103473905;    long lthbgggFWuMiywDXuKiasqYyH86923544 = -537369961;    long lthbgggFWuMiywDXuKiasqYyH84988918 = -21068515;    long lthbgggFWuMiywDXuKiasqYyH52922021 = -40420357;    long lthbgggFWuMiywDXuKiasqYyH44765218 = -496428599;    long lthbgggFWuMiywDXuKiasqYyH13185045 = -43526221;    long lthbgggFWuMiywDXuKiasqYyH93501734 = -310016483;    long lthbgggFWuMiywDXuKiasqYyH31899289 = -55657081;     lthbgggFWuMiywDXuKiasqYyH42511760 = lthbgggFWuMiywDXuKiasqYyH84168007;     lthbgggFWuMiywDXuKiasqYyH84168007 = lthbgggFWuMiywDXuKiasqYyH68298549;     lthbgggFWuMiywDXuKiasqYyH68298549 = lthbgggFWuMiywDXuKiasqYyH25753176;     lthbgggFWuMiywDXuKiasqYyH25753176 = lthbgggFWuMiywDXuKiasqYyH9904252;     lthbgggFWuMiywDXuKiasqYyH9904252 = lthbgggFWuMiywDXuKiasqYyH67129594;     lthbgggFWuMiywDXuKiasqYyH67129594 = lthbgggFWuMiywDXuKiasqYyH14461658;     lthbgggFWuMiywDXuKiasqYyH14461658 = lthbgggFWuMiywDXuKiasqYyH80563762;     lthbgggFWuMiywDXuKiasqYyH80563762 = lthbgggFWuMiywDXuKiasqYyH58547326;     lthbgggFWuMiywDXuKiasqYyH58547326 = lthbgggFWuMiywDXuKiasqYyH8090975;     lthbgggFWuMiywDXuKiasqYyH8090975 = lthbgggFWuMiywDXuKiasqYyH73756196;     lthbgggFWuMiywDXuKiasqYyH73756196 = lthbgggFWuMiywDXuKiasqYyH73848564;     lthbgggFWuMiywDXuKiasqYyH73848564 = lthbgggFWuMiywDXuKiasqYyH64368922;     lthbgggFWuMiywDXuKiasqYyH64368922 = lthbgggFWuMiywDXuKiasqYyH88928920;     lthbgggFWuMiywDXuKiasqYyH88928920 = lthbgggFWuMiywDXuKiasqYyH31612442;     lthbgggFWuMiywDXuKiasqYyH31612442 = lthbgggFWuMiywDXuKiasqYyH81787795;     lthbgggFWuMiywDXuKiasqYyH81787795 = lthbgggFWuMiywDXuKiasqYyH74160111;     lthbgggFWuMiywDXuKiasqYyH74160111 = lthbgggFWuMiywDXuKiasqYyH89502399;     lthbgggFWuMiywDXuKiasqYyH89502399 = lthbgggFWuMiywDXuKiasqYyH84415630;     lthbgggFWuMiywDXuKiasqYyH84415630 = lthbgggFWuMiywDXuKiasqYyH56299451;     lthbgggFWuMiywDXuKiasqYyH56299451 = lthbgggFWuMiywDXuKiasqYyH79218486;     lthbgggFWuMiywDXuKiasqYyH79218486 = lthbgggFWuMiywDXuKiasqYyH47451120;     lthbgggFWuMiywDXuKiasqYyH47451120 = lthbgggFWuMiywDXuKiasqYyH13499760;     lthbgggFWuMiywDXuKiasqYyH13499760 = lthbgggFWuMiywDXuKiasqYyH31773406;     lthbgggFWuMiywDXuKiasqYyH31773406 = lthbgggFWuMiywDXuKiasqYyH13828852;     lthbgggFWuMiywDXuKiasqYyH13828852 = lthbgggFWuMiywDXuKiasqYyH97411670;     lthbgggFWuMiywDXuKiasqYyH97411670 = lthbgggFWuMiywDXuKiasqYyH73617749;     lthbgggFWuMiywDXuKiasqYyH73617749 = lthbgggFWuMiywDXuKiasqYyH27540658;     lthbgggFWuMiywDXuKiasqYyH27540658 = lthbgggFWuMiywDXuKiasqYyH36956396;     lthbgggFWuMiywDXuKiasqYyH36956396 = lthbgggFWuMiywDXuKiasqYyH54133170;     lthbgggFWuMiywDXuKiasqYyH54133170 = lthbgggFWuMiywDXuKiasqYyH25032246;     lthbgggFWuMiywDXuKiasqYyH25032246 = lthbgggFWuMiywDXuKiasqYyH26564372;     lthbgggFWuMiywDXuKiasqYyH26564372 = lthbgggFWuMiywDXuKiasqYyH55983840;     lthbgggFWuMiywDXuKiasqYyH55983840 = lthbgggFWuMiywDXuKiasqYyH13069070;     lthbgggFWuMiywDXuKiasqYyH13069070 = lthbgggFWuMiywDXuKiasqYyH79335868;     lthbgggFWuMiywDXuKiasqYyH79335868 = lthbgggFWuMiywDXuKiasqYyH27025972;     lthbgggFWuMiywDXuKiasqYyH27025972 = lthbgggFWuMiywDXuKiasqYyH78242339;     lthbgggFWuMiywDXuKiasqYyH78242339 = lthbgggFWuMiywDXuKiasqYyH67839776;     lthbgggFWuMiywDXuKiasqYyH67839776 = lthbgggFWuMiywDXuKiasqYyH99416125;     lthbgggFWuMiywDXuKiasqYyH99416125 = lthbgggFWuMiywDXuKiasqYyH78500763;     lthbgggFWuMiywDXuKiasqYyH78500763 = lthbgggFWuMiywDXuKiasqYyH39843021;     lthbgggFWuMiywDXuKiasqYyH39843021 = lthbgggFWuMiywDXuKiasqYyH88372584;     lthbgggFWuMiywDXuKiasqYyH88372584 = lthbgggFWuMiywDXuKiasqYyH17599201;     lthbgggFWuMiywDXuKiasqYyH17599201 = lthbgggFWuMiywDXuKiasqYyH76560463;     lthbgggFWuMiywDXuKiasqYyH76560463 = lthbgggFWuMiywDXuKiasqYyH79091113;     lthbgggFWuMiywDXuKiasqYyH79091113 = lthbgggFWuMiywDXuKiasqYyH3714081;     lthbgggFWuMiywDXuKiasqYyH3714081 = lthbgggFWuMiywDXuKiasqYyH12400584;     lthbgggFWuMiywDXuKiasqYyH12400584 = lthbgggFWuMiywDXuKiasqYyH880793;     lthbgggFWuMiywDXuKiasqYyH880793 = lthbgggFWuMiywDXuKiasqYyH34479990;     lthbgggFWuMiywDXuKiasqYyH34479990 = lthbgggFWuMiywDXuKiasqYyH21272764;     lthbgggFWuMiywDXuKiasqYyH21272764 = lthbgggFWuMiywDXuKiasqYyH42728317;     lthbgggFWuMiywDXuKiasqYyH42728317 = lthbgggFWuMiywDXuKiasqYyH40377670;     lthbgggFWuMiywDXuKiasqYyH40377670 = lthbgggFWuMiywDXuKiasqYyH37846945;     lthbgggFWuMiywDXuKiasqYyH37846945 = lthbgggFWuMiywDXuKiasqYyH21826317;     lthbgggFWuMiywDXuKiasqYyH21826317 = lthbgggFWuMiywDXuKiasqYyH59371928;     lthbgggFWuMiywDXuKiasqYyH59371928 = lthbgggFWuMiywDXuKiasqYyH95060640;     lthbgggFWuMiywDXuKiasqYyH95060640 = lthbgggFWuMiywDXuKiasqYyH70668247;     lthbgggFWuMiywDXuKiasqYyH70668247 = lthbgggFWuMiywDXuKiasqYyH36525144;     lthbgggFWuMiywDXuKiasqYyH36525144 = lthbgggFWuMiywDXuKiasqYyH11924325;     lthbgggFWuMiywDXuKiasqYyH11924325 = lthbgggFWuMiywDXuKiasqYyH12492581;     lthbgggFWuMiywDXuKiasqYyH12492581 = lthbgggFWuMiywDXuKiasqYyH93511844;     lthbgggFWuMiywDXuKiasqYyH93511844 = lthbgggFWuMiywDXuKiasqYyH86920999;     lthbgggFWuMiywDXuKiasqYyH86920999 = lthbgggFWuMiywDXuKiasqYyH43607367;     lthbgggFWuMiywDXuKiasqYyH43607367 = lthbgggFWuMiywDXuKiasqYyH4414157;     lthbgggFWuMiywDXuKiasqYyH4414157 = lthbgggFWuMiywDXuKiasqYyH83058729;     lthbgggFWuMiywDXuKiasqYyH83058729 = lthbgggFWuMiywDXuKiasqYyH47191824;     lthbgggFWuMiywDXuKiasqYyH47191824 = lthbgggFWuMiywDXuKiasqYyH17864725;     lthbgggFWuMiywDXuKiasqYyH17864725 = lthbgggFWuMiywDXuKiasqYyH51299852;     lthbgggFWuMiywDXuKiasqYyH51299852 = lthbgggFWuMiywDXuKiasqYyH9593052;     lthbgggFWuMiywDXuKiasqYyH9593052 = lthbgggFWuMiywDXuKiasqYyH4586470;     lthbgggFWuMiywDXuKiasqYyH4586470 = lthbgggFWuMiywDXuKiasqYyH3545456;     lthbgggFWuMiywDXuKiasqYyH3545456 = lthbgggFWuMiywDXuKiasqYyH6320335;     lthbgggFWuMiywDXuKiasqYyH6320335 = lthbgggFWuMiywDXuKiasqYyH90086274;     lthbgggFWuMiywDXuKiasqYyH90086274 = lthbgggFWuMiywDXuKiasqYyH5914867;     lthbgggFWuMiywDXuKiasqYyH5914867 = lthbgggFWuMiywDXuKiasqYyH16456431;     lthbgggFWuMiywDXuKiasqYyH16456431 = lthbgggFWuMiywDXuKiasqYyH90845902;     lthbgggFWuMiywDXuKiasqYyH90845902 = lthbgggFWuMiywDXuKiasqYyH29851919;     lthbgggFWuMiywDXuKiasqYyH29851919 = lthbgggFWuMiywDXuKiasqYyH36939296;     lthbgggFWuMiywDXuKiasqYyH36939296 = lthbgggFWuMiywDXuKiasqYyH52682293;     lthbgggFWuMiywDXuKiasqYyH52682293 = lthbgggFWuMiywDXuKiasqYyH10114771;     lthbgggFWuMiywDXuKiasqYyH10114771 = lthbgggFWuMiywDXuKiasqYyH85011087;     lthbgggFWuMiywDXuKiasqYyH85011087 = lthbgggFWuMiywDXuKiasqYyH72736957;     lthbgggFWuMiywDXuKiasqYyH72736957 = lthbgggFWuMiywDXuKiasqYyH93060668;     lthbgggFWuMiywDXuKiasqYyH93060668 = lthbgggFWuMiywDXuKiasqYyH15683633;     lthbgggFWuMiywDXuKiasqYyH15683633 = lthbgggFWuMiywDXuKiasqYyH11404853;     lthbgggFWuMiywDXuKiasqYyH11404853 = lthbgggFWuMiywDXuKiasqYyH84654575;     lthbgggFWuMiywDXuKiasqYyH84654575 = lthbgggFWuMiywDXuKiasqYyH88717426;     lthbgggFWuMiywDXuKiasqYyH88717426 = lthbgggFWuMiywDXuKiasqYyH34157524;     lthbgggFWuMiywDXuKiasqYyH34157524 = lthbgggFWuMiywDXuKiasqYyH53697142;     lthbgggFWuMiywDXuKiasqYyH53697142 = lthbgggFWuMiywDXuKiasqYyH84275228;     lthbgggFWuMiywDXuKiasqYyH84275228 = lthbgggFWuMiywDXuKiasqYyH56357725;     lthbgggFWuMiywDXuKiasqYyH56357725 = lthbgggFWuMiywDXuKiasqYyH41717196;     lthbgggFWuMiywDXuKiasqYyH41717196 = lthbgggFWuMiywDXuKiasqYyH55915452;     lthbgggFWuMiywDXuKiasqYyH55915452 = lthbgggFWuMiywDXuKiasqYyH86923544;     lthbgggFWuMiywDXuKiasqYyH86923544 = lthbgggFWuMiywDXuKiasqYyH84988918;     lthbgggFWuMiywDXuKiasqYyH84988918 = lthbgggFWuMiywDXuKiasqYyH52922021;     lthbgggFWuMiywDXuKiasqYyH52922021 = lthbgggFWuMiywDXuKiasqYyH44765218;     lthbgggFWuMiywDXuKiasqYyH44765218 = lthbgggFWuMiywDXuKiasqYyH13185045;     lthbgggFWuMiywDXuKiasqYyH13185045 = lthbgggFWuMiywDXuKiasqYyH93501734;     lthbgggFWuMiywDXuKiasqYyH93501734 = lthbgggFWuMiywDXuKiasqYyH31899289;     lthbgggFWuMiywDXuKiasqYyH31899289 = lthbgggFWuMiywDXuKiasqYyH42511760;}
// Junk Finished

// Junk Code By Troll Face & Thaisen's Gen
void LovdRRomlGjJQeOvmPNqjcnkW23653253() {     long zDwXLrPXGhELmjinyxEzgOMyE26235279 = -405679148;    long zDwXLrPXGhELmjinyxEzgOMyE81766102 = -131543807;    long zDwXLrPXGhELmjinyxEzgOMyE56884666 = -964142544;    long zDwXLrPXGhELmjinyxEzgOMyE22901130 = -676053205;    long zDwXLrPXGhELmjinyxEzgOMyE89465588 = -102947804;    long zDwXLrPXGhELmjinyxEzgOMyE78469111 = -702832864;    long zDwXLrPXGhELmjinyxEzgOMyE51342221 = -468308783;    long zDwXLrPXGhELmjinyxEzgOMyE23903846 = -169201726;    long zDwXLrPXGhELmjinyxEzgOMyE8766855 = -538413953;    long zDwXLrPXGhELmjinyxEzgOMyE54196563 = -469254729;    long zDwXLrPXGhELmjinyxEzgOMyE16645232 = -122989327;    long zDwXLrPXGhELmjinyxEzgOMyE64060335 = -558120810;    long zDwXLrPXGhELmjinyxEzgOMyE15422774 = 79439116;    long zDwXLrPXGhELmjinyxEzgOMyE83302064 = -229777777;    long zDwXLrPXGhELmjinyxEzgOMyE35791700 = -623400876;    long zDwXLrPXGhELmjinyxEzgOMyE53601824 = -695603887;    long zDwXLrPXGhELmjinyxEzgOMyE74025522 = -126416216;    long zDwXLrPXGhELmjinyxEzgOMyE3579669 = -303690496;    long zDwXLrPXGhELmjinyxEzgOMyE25392111 = -865546905;    long zDwXLrPXGhELmjinyxEzgOMyE30407096 = -633847224;    long zDwXLrPXGhELmjinyxEzgOMyE46557997 = 68751852;    long zDwXLrPXGhELmjinyxEzgOMyE48453191 = 7623925;    long zDwXLrPXGhELmjinyxEzgOMyE82675625 = 44235079;    long zDwXLrPXGhELmjinyxEzgOMyE32916101 = -260736597;    long zDwXLrPXGhELmjinyxEzgOMyE50430945 = -547814567;    long zDwXLrPXGhELmjinyxEzgOMyE50404428 = -762856167;    long zDwXLrPXGhELmjinyxEzgOMyE95209688 = -889421709;    long zDwXLrPXGhELmjinyxEzgOMyE70139858 = -751651462;    long zDwXLrPXGhELmjinyxEzgOMyE8874538 = -194010470;    long zDwXLrPXGhELmjinyxEzgOMyE89681497 = -973727866;    long zDwXLrPXGhELmjinyxEzgOMyE6396669 = -712210488;    long zDwXLrPXGhELmjinyxEzgOMyE51357660 = -265861606;    long zDwXLrPXGhELmjinyxEzgOMyE70108541 = -87400913;    long zDwXLrPXGhELmjinyxEzgOMyE48793784 = -75483603;    long zDwXLrPXGhELmjinyxEzgOMyE46939194 = -467371046;    long zDwXLrPXGhELmjinyxEzgOMyE96887205 = -715382562;    long zDwXLrPXGhELmjinyxEzgOMyE78005929 = -424399916;    long zDwXLrPXGhELmjinyxEzgOMyE18221568 = -204304593;    long zDwXLrPXGhELmjinyxEzgOMyE60031844 = -228039316;    long zDwXLrPXGhELmjinyxEzgOMyE17689880 = -121681303;    long zDwXLrPXGhELmjinyxEzgOMyE4610542 = -272045155;    long zDwXLrPXGhELmjinyxEzgOMyE17712311 = 18613163;    long zDwXLrPXGhELmjinyxEzgOMyE50399347 = -335740241;    long zDwXLrPXGhELmjinyxEzgOMyE23755983 = -742061462;    long zDwXLrPXGhELmjinyxEzgOMyE7078364 = -16282500;    long zDwXLrPXGhELmjinyxEzgOMyE47980962 = -366115184;    long zDwXLrPXGhELmjinyxEzgOMyE45579553 = -385028115;    long zDwXLrPXGhELmjinyxEzgOMyE39622640 = -166957014;    long zDwXLrPXGhELmjinyxEzgOMyE68354203 = -45921593;    long zDwXLrPXGhELmjinyxEzgOMyE57146094 = -925661096;    long zDwXLrPXGhELmjinyxEzgOMyE82819149 = -516093820;    long zDwXLrPXGhELmjinyxEzgOMyE91883389 = -566796472;    long zDwXLrPXGhELmjinyxEzgOMyE83229347 = -789999207;    long zDwXLrPXGhELmjinyxEzgOMyE67758922 = -530635804;    long zDwXLrPXGhELmjinyxEzgOMyE77095256 = -509053144;    long zDwXLrPXGhELmjinyxEzgOMyE77782087 = -313303073;    long zDwXLrPXGhELmjinyxEzgOMyE99090477 = -75778887;    long zDwXLrPXGhELmjinyxEzgOMyE23968566 = -603405948;    long zDwXLrPXGhELmjinyxEzgOMyE72470184 = -28238639;    long zDwXLrPXGhELmjinyxEzgOMyE39061160 = -340091638;    long zDwXLrPXGhELmjinyxEzgOMyE83259423 = -813411155;    long zDwXLrPXGhELmjinyxEzgOMyE81202362 = -716657321;    long zDwXLrPXGhELmjinyxEzgOMyE15029308 = -975191256;    long zDwXLrPXGhELmjinyxEzgOMyE19085358 = -564686088;    long zDwXLrPXGhELmjinyxEzgOMyE47799895 = -757044242;    long zDwXLrPXGhELmjinyxEzgOMyE65287572 = -857127721;    long zDwXLrPXGhELmjinyxEzgOMyE93951793 = -370719897;    long zDwXLrPXGhELmjinyxEzgOMyE66628990 = -845077282;    long zDwXLrPXGhELmjinyxEzgOMyE36362871 = -762406732;    long zDwXLrPXGhELmjinyxEzgOMyE38904495 = -908018314;    long zDwXLrPXGhELmjinyxEzgOMyE75595894 = -171203971;    long zDwXLrPXGhELmjinyxEzgOMyE55803955 = -922111624;    long zDwXLrPXGhELmjinyxEzgOMyE43547825 = 24348819;    long zDwXLrPXGhELmjinyxEzgOMyE7702232 = -643865603;    long zDwXLrPXGhELmjinyxEzgOMyE25796555 = -261802070;    long zDwXLrPXGhELmjinyxEzgOMyE28845686 = -949861311;    long zDwXLrPXGhELmjinyxEzgOMyE98053844 = -656635835;    long zDwXLrPXGhELmjinyxEzgOMyE58919642 = -213703460;    long zDwXLrPXGhELmjinyxEzgOMyE25837737 = -144454098;    long zDwXLrPXGhELmjinyxEzgOMyE2449983 = -81699383;    long zDwXLrPXGhELmjinyxEzgOMyE4824876 = -277828053;    long zDwXLrPXGhELmjinyxEzgOMyE55587049 = -622464696;    long zDwXLrPXGhELmjinyxEzgOMyE1785655 = -605729869;    long zDwXLrPXGhELmjinyxEzgOMyE51728444 = -268349375;    long zDwXLrPXGhELmjinyxEzgOMyE6862349 = -357634046;    long zDwXLrPXGhELmjinyxEzgOMyE14513279 = -45414016;    long zDwXLrPXGhELmjinyxEzgOMyE68128312 = -475862399;    long zDwXLrPXGhELmjinyxEzgOMyE2349619 = -556765110;    long zDwXLrPXGhELmjinyxEzgOMyE71698528 = -566430459;    long zDwXLrPXGhELmjinyxEzgOMyE69157107 = -54067973;    long zDwXLrPXGhELmjinyxEzgOMyE97796727 = -539603676;    long zDwXLrPXGhELmjinyxEzgOMyE54037364 = -820993969;    long zDwXLrPXGhELmjinyxEzgOMyE45751383 = -76065954;    long zDwXLrPXGhELmjinyxEzgOMyE20970685 = -887947679;    long zDwXLrPXGhELmjinyxEzgOMyE34430456 = -308270149;    long zDwXLrPXGhELmjinyxEzgOMyE23408179 = -555387834;    long zDwXLrPXGhELmjinyxEzgOMyE2683003 = -6195582;    long zDwXLrPXGhELmjinyxEzgOMyE31313990 = -771054153;    long zDwXLrPXGhELmjinyxEzgOMyE75956088 = -985017221;    long zDwXLrPXGhELmjinyxEzgOMyE41790792 = -405679148;     zDwXLrPXGhELmjinyxEzgOMyE26235279 = zDwXLrPXGhELmjinyxEzgOMyE81766102;     zDwXLrPXGhELmjinyxEzgOMyE81766102 = zDwXLrPXGhELmjinyxEzgOMyE56884666;     zDwXLrPXGhELmjinyxEzgOMyE56884666 = zDwXLrPXGhELmjinyxEzgOMyE22901130;     zDwXLrPXGhELmjinyxEzgOMyE22901130 = zDwXLrPXGhELmjinyxEzgOMyE89465588;     zDwXLrPXGhELmjinyxEzgOMyE89465588 = zDwXLrPXGhELmjinyxEzgOMyE78469111;     zDwXLrPXGhELmjinyxEzgOMyE78469111 = zDwXLrPXGhELmjinyxEzgOMyE51342221;     zDwXLrPXGhELmjinyxEzgOMyE51342221 = zDwXLrPXGhELmjinyxEzgOMyE23903846;     zDwXLrPXGhELmjinyxEzgOMyE23903846 = zDwXLrPXGhELmjinyxEzgOMyE8766855;     zDwXLrPXGhELmjinyxEzgOMyE8766855 = zDwXLrPXGhELmjinyxEzgOMyE54196563;     zDwXLrPXGhELmjinyxEzgOMyE54196563 = zDwXLrPXGhELmjinyxEzgOMyE16645232;     zDwXLrPXGhELmjinyxEzgOMyE16645232 = zDwXLrPXGhELmjinyxEzgOMyE64060335;     zDwXLrPXGhELmjinyxEzgOMyE64060335 = zDwXLrPXGhELmjinyxEzgOMyE15422774;     zDwXLrPXGhELmjinyxEzgOMyE15422774 = zDwXLrPXGhELmjinyxEzgOMyE83302064;     zDwXLrPXGhELmjinyxEzgOMyE83302064 = zDwXLrPXGhELmjinyxEzgOMyE35791700;     zDwXLrPXGhELmjinyxEzgOMyE35791700 = zDwXLrPXGhELmjinyxEzgOMyE53601824;     zDwXLrPXGhELmjinyxEzgOMyE53601824 = zDwXLrPXGhELmjinyxEzgOMyE74025522;     zDwXLrPXGhELmjinyxEzgOMyE74025522 = zDwXLrPXGhELmjinyxEzgOMyE3579669;     zDwXLrPXGhELmjinyxEzgOMyE3579669 = zDwXLrPXGhELmjinyxEzgOMyE25392111;     zDwXLrPXGhELmjinyxEzgOMyE25392111 = zDwXLrPXGhELmjinyxEzgOMyE30407096;     zDwXLrPXGhELmjinyxEzgOMyE30407096 = zDwXLrPXGhELmjinyxEzgOMyE46557997;     zDwXLrPXGhELmjinyxEzgOMyE46557997 = zDwXLrPXGhELmjinyxEzgOMyE48453191;     zDwXLrPXGhELmjinyxEzgOMyE48453191 = zDwXLrPXGhELmjinyxEzgOMyE82675625;     zDwXLrPXGhELmjinyxEzgOMyE82675625 = zDwXLrPXGhELmjinyxEzgOMyE32916101;     zDwXLrPXGhELmjinyxEzgOMyE32916101 = zDwXLrPXGhELmjinyxEzgOMyE50430945;     zDwXLrPXGhELmjinyxEzgOMyE50430945 = zDwXLrPXGhELmjinyxEzgOMyE50404428;     zDwXLrPXGhELmjinyxEzgOMyE50404428 = zDwXLrPXGhELmjinyxEzgOMyE95209688;     zDwXLrPXGhELmjinyxEzgOMyE95209688 = zDwXLrPXGhELmjinyxEzgOMyE70139858;     zDwXLrPXGhELmjinyxEzgOMyE70139858 = zDwXLrPXGhELmjinyxEzgOMyE8874538;     zDwXLrPXGhELmjinyxEzgOMyE8874538 = zDwXLrPXGhELmjinyxEzgOMyE89681497;     zDwXLrPXGhELmjinyxEzgOMyE89681497 = zDwXLrPXGhELmjinyxEzgOMyE6396669;     zDwXLrPXGhELmjinyxEzgOMyE6396669 = zDwXLrPXGhELmjinyxEzgOMyE51357660;     zDwXLrPXGhELmjinyxEzgOMyE51357660 = zDwXLrPXGhELmjinyxEzgOMyE70108541;     zDwXLrPXGhELmjinyxEzgOMyE70108541 = zDwXLrPXGhELmjinyxEzgOMyE48793784;     zDwXLrPXGhELmjinyxEzgOMyE48793784 = zDwXLrPXGhELmjinyxEzgOMyE46939194;     zDwXLrPXGhELmjinyxEzgOMyE46939194 = zDwXLrPXGhELmjinyxEzgOMyE96887205;     zDwXLrPXGhELmjinyxEzgOMyE96887205 = zDwXLrPXGhELmjinyxEzgOMyE78005929;     zDwXLrPXGhELmjinyxEzgOMyE78005929 = zDwXLrPXGhELmjinyxEzgOMyE18221568;     zDwXLrPXGhELmjinyxEzgOMyE18221568 = zDwXLrPXGhELmjinyxEzgOMyE60031844;     zDwXLrPXGhELmjinyxEzgOMyE60031844 = zDwXLrPXGhELmjinyxEzgOMyE17689880;     zDwXLrPXGhELmjinyxEzgOMyE17689880 = zDwXLrPXGhELmjinyxEzgOMyE4610542;     zDwXLrPXGhELmjinyxEzgOMyE4610542 = zDwXLrPXGhELmjinyxEzgOMyE17712311;     zDwXLrPXGhELmjinyxEzgOMyE17712311 = zDwXLrPXGhELmjinyxEzgOMyE50399347;     zDwXLrPXGhELmjinyxEzgOMyE50399347 = zDwXLrPXGhELmjinyxEzgOMyE23755983;     zDwXLrPXGhELmjinyxEzgOMyE23755983 = zDwXLrPXGhELmjinyxEzgOMyE7078364;     zDwXLrPXGhELmjinyxEzgOMyE7078364 = zDwXLrPXGhELmjinyxEzgOMyE47980962;     zDwXLrPXGhELmjinyxEzgOMyE47980962 = zDwXLrPXGhELmjinyxEzgOMyE45579553;     zDwXLrPXGhELmjinyxEzgOMyE45579553 = zDwXLrPXGhELmjinyxEzgOMyE39622640;     zDwXLrPXGhELmjinyxEzgOMyE39622640 = zDwXLrPXGhELmjinyxEzgOMyE68354203;     zDwXLrPXGhELmjinyxEzgOMyE68354203 = zDwXLrPXGhELmjinyxEzgOMyE57146094;     zDwXLrPXGhELmjinyxEzgOMyE57146094 = zDwXLrPXGhELmjinyxEzgOMyE82819149;     zDwXLrPXGhELmjinyxEzgOMyE82819149 = zDwXLrPXGhELmjinyxEzgOMyE91883389;     zDwXLrPXGhELmjinyxEzgOMyE91883389 = zDwXLrPXGhELmjinyxEzgOMyE83229347;     zDwXLrPXGhELmjinyxEzgOMyE83229347 = zDwXLrPXGhELmjinyxEzgOMyE67758922;     zDwXLrPXGhELmjinyxEzgOMyE67758922 = zDwXLrPXGhELmjinyxEzgOMyE77095256;     zDwXLrPXGhELmjinyxEzgOMyE77095256 = zDwXLrPXGhELmjinyxEzgOMyE77782087;     zDwXLrPXGhELmjinyxEzgOMyE77782087 = zDwXLrPXGhELmjinyxEzgOMyE99090477;     zDwXLrPXGhELmjinyxEzgOMyE99090477 = zDwXLrPXGhELmjinyxEzgOMyE23968566;     zDwXLrPXGhELmjinyxEzgOMyE23968566 = zDwXLrPXGhELmjinyxEzgOMyE72470184;     zDwXLrPXGhELmjinyxEzgOMyE72470184 = zDwXLrPXGhELmjinyxEzgOMyE39061160;     zDwXLrPXGhELmjinyxEzgOMyE39061160 = zDwXLrPXGhELmjinyxEzgOMyE83259423;     zDwXLrPXGhELmjinyxEzgOMyE83259423 = zDwXLrPXGhELmjinyxEzgOMyE81202362;     zDwXLrPXGhELmjinyxEzgOMyE81202362 = zDwXLrPXGhELmjinyxEzgOMyE15029308;     zDwXLrPXGhELmjinyxEzgOMyE15029308 = zDwXLrPXGhELmjinyxEzgOMyE19085358;     zDwXLrPXGhELmjinyxEzgOMyE19085358 = zDwXLrPXGhELmjinyxEzgOMyE47799895;     zDwXLrPXGhELmjinyxEzgOMyE47799895 = zDwXLrPXGhELmjinyxEzgOMyE65287572;     zDwXLrPXGhELmjinyxEzgOMyE65287572 = zDwXLrPXGhELmjinyxEzgOMyE93951793;     zDwXLrPXGhELmjinyxEzgOMyE93951793 = zDwXLrPXGhELmjinyxEzgOMyE66628990;     zDwXLrPXGhELmjinyxEzgOMyE66628990 = zDwXLrPXGhELmjinyxEzgOMyE36362871;     zDwXLrPXGhELmjinyxEzgOMyE36362871 = zDwXLrPXGhELmjinyxEzgOMyE38904495;     zDwXLrPXGhELmjinyxEzgOMyE38904495 = zDwXLrPXGhELmjinyxEzgOMyE75595894;     zDwXLrPXGhELmjinyxEzgOMyE75595894 = zDwXLrPXGhELmjinyxEzgOMyE55803955;     zDwXLrPXGhELmjinyxEzgOMyE55803955 = zDwXLrPXGhELmjinyxEzgOMyE43547825;     zDwXLrPXGhELmjinyxEzgOMyE43547825 = zDwXLrPXGhELmjinyxEzgOMyE7702232;     zDwXLrPXGhELmjinyxEzgOMyE7702232 = zDwXLrPXGhELmjinyxEzgOMyE25796555;     zDwXLrPXGhELmjinyxEzgOMyE25796555 = zDwXLrPXGhELmjinyxEzgOMyE28845686;     zDwXLrPXGhELmjinyxEzgOMyE28845686 = zDwXLrPXGhELmjinyxEzgOMyE98053844;     zDwXLrPXGhELmjinyxEzgOMyE98053844 = zDwXLrPXGhELmjinyxEzgOMyE58919642;     zDwXLrPXGhELmjinyxEzgOMyE58919642 = zDwXLrPXGhELmjinyxEzgOMyE25837737;     zDwXLrPXGhELmjinyxEzgOMyE25837737 = zDwXLrPXGhELmjinyxEzgOMyE2449983;     zDwXLrPXGhELmjinyxEzgOMyE2449983 = zDwXLrPXGhELmjinyxEzgOMyE4824876;     zDwXLrPXGhELmjinyxEzgOMyE4824876 = zDwXLrPXGhELmjinyxEzgOMyE55587049;     zDwXLrPXGhELmjinyxEzgOMyE55587049 = zDwXLrPXGhELmjinyxEzgOMyE1785655;     zDwXLrPXGhELmjinyxEzgOMyE1785655 = zDwXLrPXGhELmjinyxEzgOMyE51728444;     zDwXLrPXGhELmjinyxEzgOMyE51728444 = zDwXLrPXGhELmjinyxEzgOMyE6862349;     zDwXLrPXGhELmjinyxEzgOMyE6862349 = zDwXLrPXGhELmjinyxEzgOMyE14513279;     zDwXLrPXGhELmjinyxEzgOMyE14513279 = zDwXLrPXGhELmjinyxEzgOMyE68128312;     zDwXLrPXGhELmjinyxEzgOMyE68128312 = zDwXLrPXGhELmjinyxEzgOMyE2349619;     zDwXLrPXGhELmjinyxEzgOMyE2349619 = zDwXLrPXGhELmjinyxEzgOMyE71698528;     zDwXLrPXGhELmjinyxEzgOMyE71698528 = zDwXLrPXGhELmjinyxEzgOMyE69157107;     zDwXLrPXGhELmjinyxEzgOMyE69157107 = zDwXLrPXGhELmjinyxEzgOMyE97796727;     zDwXLrPXGhELmjinyxEzgOMyE97796727 = zDwXLrPXGhELmjinyxEzgOMyE54037364;     zDwXLrPXGhELmjinyxEzgOMyE54037364 = zDwXLrPXGhELmjinyxEzgOMyE45751383;     zDwXLrPXGhELmjinyxEzgOMyE45751383 = zDwXLrPXGhELmjinyxEzgOMyE20970685;     zDwXLrPXGhELmjinyxEzgOMyE20970685 = zDwXLrPXGhELmjinyxEzgOMyE34430456;     zDwXLrPXGhELmjinyxEzgOMyE34430456 = zDwXLrPXGhELmjinyxEzgOMyE23408179;     zDwXLrPXGhELmjinyxEzgOMyE23408179 = zDwXLrPXGhELmjinyxEzgOMyE2683003;     zDwXLrPXGhELmjinyxEzgOMyE2683003 = zDwXLrPXGhELmjinyxEzgOMyE31313990;     zDwXLrPXGhELmjinyxEzgOMyE31313990 = zDwXLrPXGhELmjinyxEzgOMyE75956088;     zDwXLrPXGhELmjinyxEzgOMyE75956088 = zDwXLrPXGhELmjinyxEzgOMyE41790792;     zDwXLrPXGhELmjinyxEzgOMyE41790792 = zDwXLrPXGhELmjinyxEzgOMyE26235279;}
// Junk Finished
