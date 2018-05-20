#include "SDK.h"

//[enc_string_enable /]

namespace SDK
{
//[swap_lines]
	IVEngineClient*     Interfaces::g_pEngine = nullptr;
	IBaseClientDLL*     Interfaces::g_pClient = nullptr;
	IClientEntityList*  Interfaces::g_pEntityList = nullptr;
	CGlobalVarsBase*    Interfaces::g_pGlobals = nullptr;
	CInput*             Interfaces::g_pInput = nullptr;
	IEngineTrace*       Interfaces::g_pEngineTrace = nullptr;
	IClientMode*        Interfaces::g_pClientMode = nullptr;
	IVModelInfoClient*	Interfaces::g_pModelInfo = nullptr;
	IEngineSound*		Interfaces::g_pSound = nullptr;
	IVModelRender*		Interfaces::g_pModelRender = nullptr;
	IVRenderView*		Interfaces::g_pRenderView = nullptr;
	IMaterialSystem*	Interfaces::g_pMaterialSystem = nullptr;
	ISurface*			Interfaces::g_pSurface = nullptr;
	IGameEventManager2*	Interfaces::g_pGameEventMgr = nullptr;
	IInputSystem*		Interfaces::g_pInputSystem = nullptr;
//[/swap_lines]
//[junk_enable /]
	CreateInterfaceFn CaptureFactory( char* FactoryModule )
	{
		CreateInterfaceFn Interface = 0;

		while ( !Interface )
		{
			HMODULE hFactoryModule = GetModuleHandleA( FactoryModule );

			if ( hFactoryModule )
			{
				Interface = (CreateInterfaceFn)( GetProcAddress( hFactoryModule , "CreateInterface" ) );
			}

			Sleep( 100 );
		}

		return Interface;
	}

	template<typename T>
	T* CaptureInterface( CreateInterfaceFn Interface , char* InterfaceName )
	{
		T* dwPointer = nullptr;

		while ( !dwPointer )
		{
			dwPointer = (T*)( Interface( InterfaceName , 0 ) );

			Sleep( 100 );
		}

		return dwPointer;
	}

	IVEngineClient* Interfaces::Engine()
	{
		if ( !g_pEngine )
		{
			CreateInterfaceFn pfnFactory = CaptureFactory( ENGINE_DLL );
			g_pEngine = CaptureInterface<IVEngineClient>( pfnFactory , VENGINE_CLIENT_INTERFACE_VERSION );
			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::g_pEngine = %X", g_pEngine);
			#endif
		}
		
		return g_pEngine;
	}

	IBaseClientDLL* Interfaces::Client()
	{
		if ( !g_pClient )
		{
			CreateInterfaceFn pfnFactory = CaptureFactory( CLIENT_DLL );
			g_pClient = CaptureInterface<IBaseClientDLL>( pfnFactory , CLIENT_DLL_INTERFACE_VERSION );

			while (!((DWORD)**(IClientMode***)( (*(uint32_t**)Client())[10] + 0x5 )) || !((DWORD)**(CGlobalVarsBase***)( (*(uint32_t**)Client())[0] + 0x1B )))
			{
				Sleep(1000);
			}
			
			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::g_pClient = %X", g_pClient);
			#endif
		}
		
		return g_pClient;
	}

	IClientEntityList* Interfaces::EntityList()
	{
		if ( !g_pEntityList )
		{
			CreateInterfaceFn pfnFactory = CaptureFactory( CLIENT_DLL );
			g_pEntityList = CaptureInterface<IClientEntityList>( pfnFactory , VCLIENTENTITYLIST_INTERFACE_VERSION );
			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::g_pEntityList = %X", g_pEntityList);
			#endif
		}
		
		return g_pEntityList;
	}

	CGlobalVarsBase* Interfaces::GlobalVars()
	{
		if ( !g_pGlobals )
		{
			auto pClientVFTable = *(uint32_t**)Client();
			g_pGlobals = **(CGlobalVarsBase***)( pClientVFTable[0] + 0x1B );
			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::g_pGlobals = %X", g_pGlobals);
			#endif
		}

		return g_pGlobals;
	}

	CInput* Interfaces::Input()
	{
		if ( !g_pInput )
		{
			auto pClientVFTable = *(uint32_t**)Client();
			g_pInput = **(CInput***)( pClientVFTable[15] + 0x1 );
			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::g_pInput = %X", g_pInput);
			#endif
		}
		
		return g_pInput;
	}

	IEngineTrace* Interfaces::EngineTrace()
	{
		if ( !g_pEngineTrace )
		{
			CreateInterfaceFn pfnFactory = CaptureFactory( ENGINE_DLL );
			g_pEngineTrace = CaptureInterface<IEngineTrace>( pfnFactory , INTERFACEVERSION_ENGINETRACE_CLIENT );
			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::g_pEngineTrace = %X", g_pEngineTrace);
			#endif
		}
		
		return g_pEngineTrace;
	}

	IClientMode* Interfaces::ClientMode()
	{
		if ( !g_pClientMode )
		{
			auto pClientVFTable = *(uint32_t**)Client();
			g_pClientMode = **(IClientMode***)( pClientVFTable[10] + 0x5 );
			
			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::g_pClientMode = %X", g_pClientMode);
			#endif
		}
		
		return g_pClientMode;
	}

	IVModelInfoClient* Interfaces::ModelInfo()
	{
		if ( !g_pModelInfo )
		{
			CreateInterfaceFn pfnFactory = CaptureFactory( ENGINE_DLL );
			g_pModelInfo = CaptureInterface<IVModelInfoClient>( pfnFactory , VMODELINFO_CLIENT_INTERACE_VERSION );
			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::g_pModelInfo = %X", g_pModelInfo);
			#endif
		}
		
		return g_pModelInfo;
	}

	IEngineSound* Interfaces::Sound()
	{
		if ( !g_pSound )
		{
			CreateInterfaceFn pfnFactory = CaptureFactory( ENGINE_DLL );
			g_pSound = CaptureInterface<IEngineSound>( pfnFactory , IENGINESOUND_CLIENT_INTERFACE_VERSION );
			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::g_pSound = %X", g_pSound);
			#endif
		}
		
		return g_pSound;
	}

	IVModelRender* Interfaces::ModelRender()
	{
		if ( !g_pModelRender )
		{
			CreateInterfaceFn pfnFactory = CaptureFactory( ENGINE_DLL );
			g_pModelRender = CaptureInterface<IVModelRender>( pfnFactory , VENGINE_HUDMODEL_INTERFACE_VERSION );
			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::g_pModelRender = %X", g_pModelRender);
			#endif
		}
		
		return g_pModelRender;
	}

	IVRenderView* Interfaces::RenderView()
	{
		if ( !g_pRenderView )
		{
			CreateInterfaceFn pfnFactory = CaptureFactory( ENGINE_DLL );
			g_pRenderView = CaptureInterface<IVRenderView>( pfnFactory , VENGINE_RENDERVIEW_INTERFACE_VERSION );
			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::g_pRenderView = %X", g_pRenderView);
			#endif
		}
		
		return g_pRenderView;
	}

	IMaterialSystem* Interfaces::MaterialSystem()
	{
		if ( !g_pMaterialSystem )
		{
			CreateInterfaceFn pfnFactory = CaptureFactory( MATERIAL_DLL );
			g_pMaterialSystem = CaptureInterface<IMaterialSystem>( pfnFactory , MATERIAL_SYSTEM_INTERFACE_VERSION );
			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::g_pMaterialSystem = %X", g_pMaterialSystem);
			#endif
		}
		
		return g_pMaterialSystem;
	}
	
	ISurface* Interfaces::Surface()
	{
		if ( !g_pSurface )
		{
			CreateInterfaceFn pfnFactory = CaptureFactory( VGUIMT_DLL );
			g_pSurface = CaptureInterface<ISurface>( pfnFactory , VGUI_SURFACE_INTERFACE_VERSION );
			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::g_pSurface = %X", g_pSurface);
			#endif
		}
		
		return g_pSurface;
	}

	IGameEventManager2*	Interfaces::GameEvent()
	{
		if ( !g_pGameEventMgr )
		{
			CreateInterfaceFn pfnFactory = CaptureFactory( ENGINE_DLL );
			g_pGameEventMgr = CaptureInterface<IGameEventManager2>( pfnFactory , GAMEEVENTMANAGER_INTERFACE_VERSION );
			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::g_pGameEventMgr = %X", g_pGameEventMgr);
			#endif
		}
		
		return g_pGameEventMgr;
	}

	IInputSystem* Interfaces::InputSystem()
	{
		if ( !g_pInputSystem )
		{
			CreateInterfaceFn pfnFactory = CaptureFactory( INPUTSYSTEM_DLL );
			g_pInputSystem = CaptureInterface<IInputSystem>( pfnFactory , INPUTSYSTEM_INTERFACE_VERSION );
			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::g_pInputSystem = %X", g_pInputSystem);
			#endif
		}
		
		return g_pInputSystem;
	}
}


























































































// Junk Code By Troll Face & Thaisen's Gen
void ekLwxFfiLPGiieqCfNrpgnpNF5109714() {     long CmcwktdpWGfIZuPAKmXTRNqKT97451841 = -90016910;    long CmcwktdpWGfIZuPAKmXTRNqKT73319316 = -669131308;    long CmcwktdpWGfIZuPAKmXTRNqKT19895594 = -498873316;    long CmcwktdpWGfIZuPAKmXTRNqKT46463958 = -667814950;    long CmcwktdpWGfIZuPAKmXTRNqKT48955833 = -600160231;    long CmcwktdpWGfIZuPAKmXTRNqKT59333676 = -253479235;    long CmcwktdpWGfIZuPAKmXTRNqKT32856271 = -225753675;    long CmcwktdpWGfIZuPAKmXTRNqKT69517455 = -978434612;    long CmcwktdpWGfIZuPAKmXTRNqKT55271400 = -530161903;    long CmcwktdpWGfIZuPAKmXTRNqKT7643383 = -642873015;    long CmcwktdpWGfIZuPAKmXTRNqKT25519984 = -598757954;    long CmcwktdpWGfIZuPAKmXTRNqKT49327972 = 78551710;    long CmcwktdpWGfIZuPAKmXTRNqKT29269399 = 89218527;    long CmcwktdpWGfIZuPAKmXTRNqKT42797383 = -808437947;    long CmcwktdpWGfIZuPAKmXTRNqKT59989201 = -473786673;    long CmcwktdpWGfIZuPAKmXTRNqKT82415650 = -204888475;    long CmcwktdpWGfIZuPAKmXTRNqKT24252641 = 72943553;    long CmcwktdpWGfIZuPAKmXTRNqKT67324276 = -822878465;    long CmcwktdpWGfIZuPAKmXTRNqKT43744300 = -534701315;    long CmcwktdpWGfIZuPAKmXTRNqKT86600445 = -937602927;    long CmcwktdpWGfIZuPAKmXTRNqKT45422573 = -99335894;    long CmcwktdpWGfIZuPAKmXTRNqKT9262197 = -757676530;    long CmcwktdpWGfIZuPAKmXTRNqKT78441352 = -43661303;    long CmcwktdpWGfIZuPAKmXTRNqKT55987803 = -7031495;    long CmcwktdpWGfIZuPAKmXTRNqKT76164913 = 65618594;    long CmcwktdpWGfIZuPAKmXTRNqKT79729149 = -977849308;    long CmcwktdpWGfIZuPAKmXTRNqKT77523291 = -415381933;    long CmcwktdpWGfIZuPAKmXTRNqKT48253708 = -80781451;    long CmcwktdpWGfIZuPAKmXTRNqKT12674 = -65679889;    long CmcwktdpWGfIZuPAKmXTRNqKT92193695 = 23795392;    long CmcwktdpWGfIZuPAKmXTRNqKT6594205 = -136232578;    long CmcwktdpWGfIZuPAKmXTRNqKT34518986 = -370341293;    long CmcwktdpWGfIZuPAKmXTRNqKT8773108 = -821102134;    long CmcwktdpWGfIZuPAKmXTRNqKT1008330 = -287320510;    long CmcwktdpWGfIZuPAKmXTRNqKT20358583 = -228255645;    long CmcwktdpWGfIZuPAKmXTRNqKT28996374 = 4411493;    long CmcwktdpWGfIZuPAKmXTRNqKT72154871 = -296323979;    long CmcwktdpWGfIZuPAKmXTRNqKT20702295 = -374500414;    long CmcwktdpWGfIZuPAKmXTRNqKT26492819 = -812408704;    long CmcwktdpWGfIZuPAKmXTRNqKT20308247 = -417964694;    long CmcwktdpWGfIZuPAKmXTRNqKT39065350 = -725102441;    long CmcwktdpWGfIZuPAKmXTRNqKT18201522 = -921218520;    long CmcwktdpWGfIZuPAKmXTRNqKT57549100 = -166058062;    long CmcwktdpWGfIZuPAKmXTRNqKT81613544 = -902593914;    long CmcwktdpWGfIZuPAKmXTRNqKT91099878 = 52616257;    long CmcwktdpWGfIZuPAKmXTRNqKT23280600 = -603249204;    long CmcwktdpWGfIZuPAKmXTRNqKT58340042 = -898500647;    long CmcwktdpWGfIZuPAKmXTRNqKT67995772 = -637126311;    long CmcwktdpWGfIZuPAKmXTRNqKT61191468 = -896285839;    long CmcwktdpWGfIZuPAKmXTRNqKT46609849 = -271635049;    long CmcwktdpWGfIZuPAKmXTRNqKT71415870 = -373852892;    long CmcwktdpWGfIZuPAKmXTRNqKT11217488 = -641457396;    long CmcwktdpWGfIZuPAKmXTRNqKT25396544 = -426113340;    long CmcwktdpWGfIZuPAKmXTRNqKT90247650 = -176189049;    long CmcwktdpWGfIZuPAKmXTRNqKT59687141 = -799576424;    long CmcwktdpWGfIZuPAKmXTRNqKT88189645 = -332340381;    long CmcwktdpWGfIZuPAKmXTRNqKT94877963 = -525470006;    long CmcwktdpWGfIZuPAKmXTRNqKT63907791 = -391841822;    long CmcwktdpWGfIZuPAKmXTRNqKT70299045 = -633433544;    long CmcwktdpWGfIZuPAKmXTRNqKT69226683 = -622310924;    long CmcwktdpWGfIZuPAKmXTRNqKT81810384 = -838097302;    long CmcwktdpWGfIZuPAKmXTRNqKT84602562 = -44972225;    long CmcwktdpWGfIZuPAKmXTRNqKT69504782 = -812754723;    long CmcwktdpWGfIZuPAKmXTRNqKT63077705 = -453957295;    long CmcwktdpWGfIZuPAKmXTRNqKT1049179 = -406640438;    long CmcwktdpWGfIZuPAKmXTRNqKT91000997 = -128416662;    long CmcwktdpWGfIZuPAKmXTRNqKT40554864 = -100346157;    long CmcwktdpWGfIZuPAKmXTRNqKT28261070 = -623460964;    long CmcwktdpWGfIZuPAKmXTRNqKT22438801 = -480182302;    long CmcwktdpWGfIZuPAKmXTRNqKT30992828 = -378198167;    long CmcwktdpWGfIZuPAKmXTRNqKT10260780 = -908564497;    long CmcwktdpWGfIZuPAKmXTRNqKT3550347 = -552556033;    long CmcwktdpWGfIZuPAKmXTRNqKT40831458 = 89530238;    long CmcwktdpWGfIZuPAKmXTRNqKT23436054 = -16736622;    long CmcwktdpWGfIZuPAKmXTRNqKT47535096 = -112500486;    long CmcwktdpWGfIZuPAKmXTRNqKT27221051 = -178117374;    long CmcwktdpWGfIZuPAKmXTRNqKT51713096 = -491618468;    long CmcwktdpWGfIZuPAKmXTRNqKT96827808 = -141067390;    long CmcwktdpWGfIZuPAKmXTRNqKT64887925 = 40352247;    long CmcwktdpWGfIZuPAKmXTRNqKT52884313 = -331132203;    long CmcwktdpWGfIZuPAKmXTRNqKT21389108 = 20651339;    long CmcwktdpWGfIZuPAKmXTRNqKT9527519 = -778255622;    long CmcwktdpWGfIZuPAKmXTRNqKT87062239 = -184495613;    long CmcwktdpWGfIZuPAKmXTRNqKT53402824 = -794044841;    long CmcwktdpWGfIZuPAKmXTRNqKT20777825 = -602351717;    long CmcwktdpWGfIZuPAKmXTRNqKT95376716 = -494775183;    long CmcwktdpWGfIZuPAKmXTRNqKT9122443 = -944227954;    long CmcwktdpWGfIZuPAKmXTRNqKT18525458 = -544913085;    long CmcwktdpWGfIZuPAKmXTRNqKT41321188 = -487744086;    long CmcwktdpWGfIZuPAKmXTRNqKT32168937 = -895915265;    long CmcwktdpWGfIZuPAKmXTRNqKT34118410 = -470118501;    long CmcwktdpWGfIZuPAKmXTRNqKT8247080 = -904482157;    long CmcwktdpWGfIZuPAKmXTRNqKT50403249 = -741066871;    long CmcwktdpWGfIZuPAKmXTRNqKT57266135 = -90097780;    long CmcwktdpWGfIZuPAKmXTRNqKT38497862 = -579867392;    long CmcwktdpWGfIZuPAKmXTRNqKT54462787 = -580130217;    long CmcwktdpWGfIZuPAKmXTRNqKT48696740 = -8463797;    long CmcwktdpWGfIZuPAKmXTRNqKT94471395 = -712100767;    long CmcwktdpWGfIZuPAKmXTRNqKT80564366 = -395953476;    long CmcwktdpWGfIZuPAKmXTRNqKT98881 = -90016910;     CmcwktdpWGfIZuPAKmXTRNqKT97451841 = CmcwktdpWGfIZuPAKmXTRNqKT73319316;     CmcwktdpWGfIZuPAKmXTRNqKT73319316 = CmcwktdpWGfIZuPAKmXTRNqKT19895594;     CmcwktdpWGfIZuPAKmXTRNqKT19895594 = CmcwktdpWGfIZuPAKmXTRNqKT46463958;     CmcwktdpWGfIZuPAKmXTRNqKT46463958 = CmcwktdpWGfIZuPAKmXTRNqKT48955833;     CmcwktdpWGfIZuPAKmXTRNqKT48955833 = CmcwktdpWGfIZuPAKmXTRNqKT59333676;     CmcwktdpWGfIZuPAKmXTRNqKT59333676 = CmcwktdpWGfIZuPAKmXTRNqKT32856271;     CmcwktdpWGfIZuPAKmXTRNqKT32856271 = CmcwktdpWGfIZuPAKmXTRNqKT69517455;     CmcwktdpWGfIZuPAKmXTRNqKT69517455 = CmcwktdpWGfIZuPAKmXTRNqKT55271400;     CmcwktdpWGfIZuPAKmXTRNqKT55271400 = CmcwktdpWGfIZuPAKmXTRNqKT7643383;     CmcwktdpWGfIZuPAKmXTRNqKT7643383 = CmcwktdpWGfIZuPAKmXTRNqKT25519984;     CmcwktdpWGfIZuPAKmXTRNqKT25519984 = CmcwktdpWGfIZuPAKmXTRNqKT49327972;     CmcwktdpWGfIZuPAKmXTRNqKT49327972 = CmcwktdpWGfIZuPAKmXTRNqKT29269399;     CmcwktdpWGfIZuPAKmXTRNqKT29269399 = CmcwktdpWGfIZuPAKmXTRNqKT42797383;     CmcwktdpWGfIZuPAKmXTRNqKT42797383 = CmcwktdpWGfIZuPAKmXTRNqKT59989201;     CmcwktdpWGfIZuPAKmXTRNqKT59989201 = CmcwktdpWGfIZuPAKmXTRNqKT82415650;     CmcwktdpWGfIZuPAKmXTRNqKT82415650 = CmcwktdpWGfIZuPAKmXTRNqKT24252641;     CmcwktdpWGfIZuPAKmXTRNqKT24252641 = CmcwktdpWGfIZuPAKmXTRNqKT67324276;     CmcwktdpWGfIZuPAKmXTRNqKT67324276 = CmcwktdpWGfIZuPAKmXTRNqKT43744300;     CmcwktdpWGfIZuPAKmXTRNqKT43744300 = CmcwktdpWGfIZuPAKmXTRNqKT86600445;     CmcwktdpWGfIZuPAKmXTRNqKT86600445 = CmcwktdpWGfIZuPAKmXTRNqKT45422573;     CmcwktdpWGfIZuPAKmXTRNqKT45422573 = CmcwktdpWGfIZuPAKmXTRNqKT9262197;     CmcwktdpWGfIZuPAKmXTRNqKT9262197 = CmcwktdpWGfIZuPAKmXTRNqKT78441352;     CmcwktdpWGfIZuPAKmXTRNqKT78441352 = CmcwktdpWGfIZuPAKmXTRNqKT55987803;     CmcwktdpWGfIZuPAKmXTRNqKT55987803 = CmcwktdpWGfIZuPAKmXTRNqKT76164913;     CmcwktdpWGfIZuPAKmXTRNqKT76164913 = CmcwktdpWGfIZuPAKmXTRNqKT79729149;     CmcwktdpWGfIZuPAKmXTRNqKT79729149 = CmcwktdpWGfIZuPAKmXTRNqKT77523291;     CmcwktdpWGfIZuPAKmXTRNqKT77523291 = CmcwktdpWGfIZuPAKmXTRNqKT48253708;     CmcwktdpWGfIZuPAKmXTRNqKT48253708 = CmcwktdpWGfIZuPAKmXTRNqKT12674;     CmcwktdpWGfIZuPAKmXTRNqKT12674 = CmcwktdpWGfIZuPAKmXTRNqKT92193695;     CmcwktdpWGfIZuPAKmXTRNqKT92193695 = CmcwktdpWGfIZuPAKmXTRNqKT6594205;     CmcwktdpWGfIZuPAKmXTRNqKT6594205 = CmcwktdpWGfIZuPAKmXTRNqKT34518986;     CmcwktdpWGfIZuPAKmXTRNqKT34518986 = CmcwktdpWGfIZuPAKmXTRNqKT8773108;     CmcwktdpWGfIZuPAKmXTRNqKT8773108 = CmcwktdpWGfIZuPAKmXTRNqKT1008330;     CmcwktdpWGfIZuPAKmXTRNqKT1008330 = CmcwktdpWGfIZuPAKmXTRNqKT20358583;     CmcwktdpWGfIZuPAKmXTRNqKT20358583 = CmcwktdpWGfIZuPAKmXTRNqKT28996374;     CmcwktdpWGfIZuPAKmXTRNqKT28996374 = CmcwktdpWGfIZuPAKmXTRNqKT72154871;     CmcwktdpWGfIZuPAKmXTRNqKT72154871 = CmcwktdpWGfIZuPAKmXTRNqKT20702295;     CmcwktdpWGfIZuPAKmXTRNqKT20702295 = CmcwktdpWGfIZuPAKmXTRNqKT26492819;     CmcwktdpWGfIZuPAKmXTRNqKT26492819 = CmcwktdpWGfIZuPAKmXTRNqKT20308247;     CmcwktdpWGfIZuPAKmXTRNqKT20308247 = CmcwktdpWGfIZuPAKmXTRNqKT39065350;     CmcwktdpWGfIZuPAKmXTRNqKT39065350 = CmcwktdpWGfIZuPAKmXTRNqKT18201522;     CmcwktdpWGfIZuPAKmXTRNqKT18201522 = CmcwktdpWGfIZuPAKmXTRNqKT57549100;     CmcwktdpWGfIZuPAKmXTRNqKT57549100 = CmcwktdpWGfIZuPAKmXTRNqKT81613544;     CmcwktdpWGfIZuPAKmXTRNqKT81613544 = CmcwktdpWGfIZuPAKmXTRNqKT91099878;     CmcwktdpWGfIZuPAKmXTRNqKT91099878 = CmcwktdpWGfIZuPAKmXTRNqKT23280600;     CmcwktdpWGfIZuPAKmXTRNqKT23280600 = CmcwktdpWGfIZuPAKmXTRNqKT58340042;     CmcwktdpWGfIZuPAKmXTRNqKT58340042 = CmcwktdpWGfIZuPAKmXTRNqKT67995772;     CmcwktdpWGfIZuPAKmXTRNqKT67995772 = CmcwktdpWGfIZuPAKmXTRNqKT61191468;     CmcwktdpWGfIZuPAKmXTRNqKT61191468 = CmcwktdpWGfIZuPAKmXTRNqKT46609849;     CmcwktdpWGfIZuPAKmXTRNqKT46609849 = CmcwktdpWGfIZuPAKmXTRNqKT71415870;     CmcwktdpWGfIZuPAKmXTRNqKT71415870 = CmcwktdpWGfIZuPAKmXTRNqKT11217488;     CmcwktdpWGfIZuPAKmXTRNqKT11217488 = CmcwktdpWGfIZuPAKmXTRNqKT25396544;     CmcwktdpWGfIZuPAKmXTRNqKT25396544 = CmcwktdpWGfIZuPAKmXTRNqKT90247650;     CmcwktdpWGfIZuPAKmXTRNqKT90247650 = CmcwktdpWGfIZuPAKmXTRNqKT59687141;     CmcwktdpWGfIZuPAKmXTRNqKT59687141 = CmcwktdpWGfIZuPAKmXTRNqKT88189645;     CmcwktdpWGfIZuPAKmXTRNqKT88189645 = CmcwktdpWGfIZuPAKmXTRNqKT94877963;     CmcwktdpWGfIZuPAKmXTRNqKT94877963 = CmcwktdpWGfIZuPAKmXTRNqKT63907791;     CmcwktdpWGfIZuPAKmXTRNqKT63907791 = CmcwktdpWGfIZuPAKmXTRNqKT70299045;     CmcwktdpWGfIZuPAKmXTRNqKT70299045 = CmcwktdpWGfIZuPAKmXTRNqKT69226683;     CmcwktdpWGfIZuPAKmXTRNqKT69226683 = CmcwktdpWGfIZuPAKmXTRNqKT81810384;     CmcwktdpWGfIZuPAKmXTRNqKT81810384 = CmcwktdpWGfIZuPAKmXTRNqKT84602562;     CmcwktdpWGfIZuPAKmXTRNqKT84602562 = CmcwktdpWGfIZuPAKmXTRNqKT69504782;     CmcwktdpWGfIZuPAKmXTRNqKT69504782 = CmcwktdpWGfIZuPAKmXTRNqKT63077705;     CmcwktdpWGfIZuPAKmXTRNqKT63077705 = CmcwktdpWGfIZuPAKmXTRNqKT1049179;     CmcwktdpWGfIZuPAKmXTRNqKT1049179 = CmcwktdpWGfIZuPAKmXTRNqKT91000997;     CmcwktdpWGfIZuPAKmXTRNqKT91000997 = CmcwktdpWGfIZuPAKmXTRNqKT40554864;     CmcwktdpWGfIZuPAKmXTRNqKT40554864 = CmcwktdpWGfIZuPAKmXTRNqKT28261070;     CmcwktdpWGfIZuPAKmXTRNqKT28261070 = CmcwktdpWGfIZuPAKmXTRNqKT22438801;     CmcwktdpWGfIZuPAKmXTRNqKT22438801 = CmcwktdpWGfIZuPAKmXTRNqKT30992828;     CmcwktdpWGfIZuPAKmXTRNqKT30992828 = CmcwktdpWGfIZuPAKmXTRNqKT10260780;     CmcwktdpWGfIZuPAKmXTRNqKT10260780 = CmcwktdpWGfIZuPAKmXTRNqKT3550347;     CmcwktdpWGfIZuPAKmXTRNqKT3550347 = CmcwktdpWGfIZuPAKmXTRNqKT40831458;     CmcwktdpWGfIZuPAKmXTRNqKT40831458 = CmcwktdpWGfIZuPAKmXTRNqKT23436054;     CmcwktdpWGfIZuPAKmXTRNqKT23436054 = CmcwktdpWGfIZuPAKmXTRNqKT47535096;     CmcwktdpWGfIZuPAKmXTRNqKT47535096 = CmcwktdpWGfIZuPAKmXTRNqKT27221051;     CmcwktdpWGfIZuPAKmXTRNqKT27221051 = CmcwktdpWGfIZuPAKmXTRNqKT51713096;     CmcwktdpWGfIZuPAKmXTRNqKT51713096 = CmcwktdpWGfIZuPAKmXTRNqKT96827808;     CmcwktdpWGfIZuPAKmXTRNqKT96827808 = CmcwktdpWGfIZuPAKmXTRNqKT64887925;     CmcwktdpWGfIZuPAKmXTRNqKT64887925 = CmcwktdpWGfIZuPAKmXTRNqKT52884313;     CmcwktdpWGfIZuPAKmXTRNqKT52884313 = CmcwktdpWGfIZuPAKmXTRNqKT21389108;     CmcwktdpWGfIZuPAKmXTRNqKT21389108 = CmcwktdpWGfIZuPAKmXTRNqKT9527519;     CmcwktdpWGfIZuPAKmXTRNqKT9527519 = CmcwktdpWGfIZuPAKmXTRNqKT87062239;     CmcwktdpWGfIZuPAKmXTRNqKT87062239 = CmcwktdpWGfIZuPAKmXTRNqKT53402824;     CmcwktdpWGfIZuPAKmXTRNqKT53402824 = CmcwktdpWGfIZuPAKmXTRNqKT20777825;     CmcwktdpWGfIZuPAKmXTRNqKT20777825 = CmcwktdpWGfIZuPAKmXTRNqKT95376716;     CmcwktdpWGfIZuPAKmXTRNqKT95376716 = CmcwktdpWGfIZuPAKmXTRNqKT9122443;     CmcwktdpWGfIZuPAKmXTRNqKT9122443 = CmcwktdpWGfIZuPAKmXTRNqKT18525458;     CmcwktdpWGfIZuPAKmXTRNqKT18525458 = CmcwktdpWGfIZuPAKmXTRNqKT41321188;     CmcwktdpWGfIZuPAKmXTRNqKT41321188 = CmcwktdpWGfIZuPAKmXTRNqKT32168937;     CmcwktdpWGfIZuPAKmXTRNqKT32168937 = CmcwktdpWGfIZuPAKmXTRNqKT34118410;     CmcwktdpWGfIZuPAKmXTRNqKT34118410 = CmcwktdpWGfIZuPAKmXTRNqKT8247080;     CmcwktdpWGfIZuPAKmXTRNqKT8247080 = CmcwktdpWGfIZuPAKmXTRNqKT50403249;     CmcwktdpWGfIZuPAKmXTRNqKT50403249 = CmcwktdpWGfIZuPAKmXTRNqKT57266135;     CmcwktdpWGfIZuPAKmXTRNqKT57266135 = CmcwktdpWGfIZuPAKmXTRNqKT38497862;     CmcwktdpWGfIZuPAKmXTRNqKT38497862 = CmcwktdpWGfIZuPAKmXTRNqKT54462787;     CmcwktdpWGfIZuPAKmXTRNqKT54462787 = CmcwktdpWGfIZuPAKmXTRNqKT48696740;     CmcwktdpWGfIZuPAKmXTRNqKT48696740 = CmcwktdpWGfIZuPAKmXTRNqKT94471395;     CmcwktdpWGfIZuPAKmXTRNqKT94471395 = CmcwktdpWGfIZuPAKmXTRNqKT80564366;     CmcwktdpWGfIZuPAKmXTRNqKT80564366 = CmcwktdpWGfIZuPAKmXTRNqKT98881;     CmcwktdpWGfIZuPAKmXTRNqKT98881 = CmcwktdpWGfIZuPAKmXTRNqKT97451841;}
// Junk Finished

// Junk Code By Troll Face & Thaisen's Gen
void dcexewrzuXwclBrIqVUboFFkx90172551() {     long AYagbohvAtpuekoBJQjJZUVoV81175359 = -440038977;    long AYagbohvAtpuekoBJQjJZUVoV70917411 = -472783160;    long AYagbohvAtpuekoBJQjJZUVoV8481711 = -367181007;    long AYagbohvAtpuekoBJQjJZUVoV43611912 = -672696879;    long AYagbohvAtpuekoBJQjJZUVoV28517170 = -998108423;    long AYagbohvAtpuekoBJQjJZUVoV70673193 = -356799904;    long AYagbohvAtpuekoBJQjJZUVoV69736834 = -247267813;    long AYagbohvAtpuekoBJQjJZUVoV12857539 = -498889198;    long AYagbohvAtpuekoBJQjJZUVoV5490929 = -127644600;    long AYagbohvAtpuekoBJQjJZUVoV53748971 = -865914031;    long AYagbohvAtpuekoBJQjJZUVoV68409020 = -439043212;    long AYagbohvAtpuekoBJQjJZUVoV39539743 = -950587561;    long AYagbohvAtpuekoBJQjJZUVoV80323251 = -853613717;    long AYagbohvAtpuekoBJQjJZUVoV37170528 = -58120809;    long AYagbohvAtpuekoBJQjJZUVoV64168460 = -399483978;    long AYagbohvAtpuekoBJQjJZUVoV54229679 = -129016126;    long AYagbohvAtpuekoBJQjJZUVoV24118052 = -85936310;    long AYagbohvAtpuekoBJQjJZUVoV81401546 = -433730039;    long AYagbohvAtpuekoBJQjJZUVoV84720780 = -323350553;    long AYagbohvAtpuekoBJQjJZUVoV60708090 = -553895844;    long AYagbohvAtpuekoBJQjJZUVoV12762084 = -773802415;    long AYagbohvAtpuekoBJQjJZUVoV10264268 = -670831816;    long AYagbohvAtpuekoBJQjJZUVoV47617218 = -73056040;    long AYagbohvAtpuekoBJQjJZUVoV57130498 = -646264148;    long AYagbohvAtpuekoBJQjJZUVoV12767006 = -12712168;    long AYagbohvAtpuekoBJQjJZUVoV32721908 = -320816335;    long AYagbohvAtpuekoBJQjJZUVoV99115230 = -859257356;    long AYagbohvAtpuekoBJQjJZUVoV90852908 = -967222939;    long AYagbohvAtpuekoBJQjJZUVoV71930815 = -589875789;    long AYagbohvAtpuekoBJQjJZUVoV27742023 = -648810983;    long AYagbohvAtpuekoBJQjJZUVoV87958627 = -355330599;    long AYagbohvAtpuekoBJQjJZUVoV59312274 = -919538515;    long AYagbohvAtpuekoBJQjJZUVoV22897809 = -386316225;    long AYagbohvAtpuekoBJQjJZUVoV36733043 = -691417157;    long AYagbohvAtpuekoBJQjJZUVoV87961907 = 37453747;    long AYagbohvAtpuekoBJQjJZUVoV98857607 = 26015016;    long AYagbohvAtpuekoBJQjJZUVoV71918461 = -616665275;    long AYagbohvAtpuekoBJQjJZUVoV71084086 = -273643631;    long AYagbohvAtpuekoBJQjJZUVoV87108537 = -17967585;    long AYagbohvAtpuekoBJQjJZUVoV59497362 = -364611573;    long AYagbohvAtpuekoBJQjJZUVoV3832871 = -375142568;    long AYagbohvAtpuekoBJQjJZUVoV47541249 = -527244190;    long AYagbohvAtpuekoBJQjJZUVoV90349246 = -918462316;    long AYagbohvAtpuekoBJQjJZUVoV28809064 = -481537646;    long AYagbohvAtpuekoBJQjJZUVoV19087129 = -273397821;    long AYagbohvAtpuekoBJQjJZUVoV67547481 = -218280896;    long AYagbohvAtpuekoBJQjJZUVoV91519011 = -920146554;    long AYagbohvAtpuekoBJQjJZUVoV6737620 = -399248209;    long AYagbohvAtpuekoBJQjJZUVoV95065681 = -596069990;    long AYagbohvAtpuekoBJQjJZUVoV82483179 = -903650484;    long AYagbohvAtpuekoBJQjJZUVoV11506703 = -539625294;    long AYagbohvAtpuekoBJQjJZUVoV62723207 = -393510182;    long AYagbohvAtpuekoBJQjJZUVoV70778946 = -438045705;    long AYagbohvAtpuekoBJQjJZUVoV36180256 = -752898237;    long AYagbohvAtpuekoBJQjJZUVoV77410468 = -16303369;    long AYagbohvAtpuekoBJQjJZUVoV70911092 = -769207162;    long AYagbohvAtpuekoBJQjJZUVoV23300194 = -299727120;    long AYagbohvAtpuekoBJQjJZUVoV51351213 = -720916859;    long AYagbohvAtpuekoBJQjJZUVoV30844906 = -559984711;    long AYagbohvAtpuekoBJQjJZUVoV95795261 = -577292088;    long AYagbohvAtpuekoBJQjJZUVoV71557963 = -497542548;    long AYagbohvAtpuekoBJQjJZUVoV78883925 = -280044875;    long AYagbohvAtpuekoBJQjJZUVoV40926723 = -909013409;    long AYagbohvAtpuekoBJQjJZUVoV77748906 = -478833617;    long AYagbohvAtpuekoBJQjJZUVoV65790343 = -410583433;    long AYagbohvAtpuekoBJQjJZUVoV9096746 = -519504697;    long AYagbohvAtpuekoBJQjJZUVoV16641934 = -464271336;    long AYagbohvAtpuekoBJQjJZUVoV43590208 = -62196560;    long AYagbohvAtpuekoBJQjJZUVoV49208620 = 4425443;    long AYagbohvAtpuekoBJQjJZUVoV65310852 = -325498995;    long AYagbohvAtpuekoBJQjJZUVoV82311217 = -512350852;    long AYagbohvAtpuekoBJQjJZUVoV53033966 = -812292679;    long AYagbohvAtpuekoBJQjJZUVoV94293008 = -315762454;    long AYagbohvAtpuekoBJQjJZUVoV25223419 = -958738981;    long AYagbohvAtpuekoBJQjJZUVoV56875219 = -78753276;    long AYagbohvAtpuekoBJQjJZUVoV65220835 = -146558226;    long AYagbohvAtpuekoBJQjJZUVoV19915021 = -752369500;    long AYagbohvAtpuekoBJQjJZUVoV18808154 = -591518394;    long AYagbohvAtpuekoBJQjJZUVoV38043369 = -272866328;    long AYagbohvAtpuekoBJQjJZUVoV45219525 = -794431273;    long AYagbohvAtpuekoBJQjJZUVoV41202896 = -400669782;    long AYagbohvAtpuekoBJQjJZUVoV92377610 = -360009147;    long AYagbohvAtpuekoBJQjJZUVoV95787226 = -271152950;    long AYagbohvAtpuekoBJQjJZUVoV89447635 = -686225305;    long AYagbohvAtpuekoBJQjJZUVoV16235321 = -9185690;    long AYagbohvAtpuekoBJQjJZUVoV25235420 = -961820418;    long AYagbohvAtpuekoBJQjJZUVoV88533328 = -381492810;    long AYagbohvAtpuekoBJQjJZUVoV86717553 = -633417988;    long AYagbohvAtpuekoBJQjJZUVoV59322575 = -575113789;    long AYagbohvAtpuekoBJQjJZUVoV17050816 = -193339092;    long AYagbohvAtpuekoBJQjJZUVoV75557413 = -674257864;    long AYagbohvAtpuekoBJQjJZUVoV20567249 = -895748416;    long AYagbohvAtpuekoBJQjJZUVoV40239180 = -713658920;    long AYagbohvAtpuekoBJQjJZUVoV91313275 = -440675498;    long AYagbohvAtpuekoBJQjJZUVoV87939399 = -867069025;    long AYagbohvAtpuekoBJQjJZUVoV24948945 = 4902306;    long AYagbohvAtpuekoBJQjJZUVoV6614526 = -618230781;    long AYagbohvAtpuekoBJQjJZUVoV12600341 = -339628700;    long AYagbohvAtpuekoBJQjJZUVoV63018720 = 29045786;    long AYagbohvAtpuekoBJQjJZUVoV9990384 = -440038977;     AYagbohvAtpuekoBJQjJZUVoV81175359 = AYagbohvAtpuekoBJQjJZUVoV70917411;     AYagbohvAtpuekoBJQjJZUVoV70917411 = AYagbohvAtpuekoBJQjJZUVoV8481711;     AYagbohvAtpuekoBJQjJZUVoV8481711 = AYagbohvAtpuekoBJQjJZUVoV43611912;     AYagbohvAtpuekoBJQjJZUVoV43611912 = AYagbohvAtpuekoBJQjJZUVoV28517170;     AYagbohvAtpuekoBJQjJZUVoV28517170 = AYagbohvAtpuekoBJQjJZUVoV70673193;     AYagbohvAtpuekoBJQjJZUVoV70673193 = AYagbohvAtpuekoBJQjJZUVoV69736834;     AYagbohvAtpuekoBJQjJZUVoV69736834 = AYagbohvAtpuekoBJQjJZUVoV12857539;     AYagbohvAtpuekoBJQjJZUVoV12857539 = AYagbohvAtpuekoBJQjJZUVoV5490929;     AYagbohvAtpuekoBJQjJZUVoV5490929 = AYagbohvAtpuekoBJQjJZUVoV53748971;     AYagbohvAtpuekoBJQjJZUVoV53748971 = AYagbohvAtpuekoBJQjJZUVoV68409020;     AYagbohvAtpuekoBJQjJZUVoV68409020 = AYagbohvAtpuekoBJQjJZUVoV39539743;     AYagbohvAtpuekoBJQjJZUVoV39539743 = AYagbohvAtpuekoBJQjJZUVoV80323251;     AYagbohvAtpuekoBJQjJZUVoV80323251 = AYagbohvAtpuekoBJQjJZUVoV37170528;     AYagbohvAtpuekoBJQjJZUVoV37170528 = AYagbohvAtpuekoBJQjJZUVoV64168460;     AYagbohvAtpuekoBJQjJZUVoV64168460 = AYagbohvAtpuekoBJQjJZUVoV54229679;     AYagbohvAtpuekoBJQjJZUVoV54229679 = AYagbohvAtpuekoBJQjJZUVoV24118052;     AYagbohvAtpuekoBJQjJZUVoV24118052 = AYagbohvAtpuekoBJQjJZUVoV81401546;     AYagbohvAtpuekoBJQjJZUVoV81401546 = AYagbohvAtpuekoBJQjJZUVoV84720780;     AYagbohvAtpuekoBJQjJZUVoV84720780 = AYagbohvAtpuekoBJQjJZUVoV60708090;     AYagbohvAtpuekoBJQjJZUVoV60708090 = AYagbohvAtpuekoBJQjJZUVoV12762084;     AYagbohvAtpuekoBJQjJZUVoV12762084 = AYagbohvAtpuekoBJQjJZUVoV10264268;     AYagbohvAtpuekoBJQjJZUVoV10264268 = AYagbohvAtpuekoBJQjJZUVoV47617218;     AYagbohvAtpuekoBJQjJZUVoV47617218 = AYagbohvAtpuekoBJQjJZUVoV57130498;     AYagbohvAtpuekoBJQjJZUVoV57130498 = AYagbohvAtpuekoBJQjJZUVoV12767006;     AYagbohvAtpuekoBJQjJZUVoV12767006 = AYagbohvAtpuekoBJQjJZUVoV32721908;     AYagbohvAtpuekoBJQjJZUVoV32721908 = AYagbohvAtpuekoBJQjJZUVoV99115230;     AYagbohvAtpuekoBJQjJZUVoV99115230 = AYagbohvAtpuekoBJQjJZUVoV90852908;     AYagbohvAtpuekoBJQjJZUVoV90852908 = AYagbohvAtpuekoBJQjJZUVoV71930815;     AYagbohvAtpuekoBJQjJZUVoV71930815 = AYagbohvAtpuekoBJQjJZUVoV27742023;     AYagbohvAtpuekoBJQjJZUVoV27742023 = AYagbohvAtpuekoBJQjJZUVoV87958627;     AYagbohvAtpuekoBJQjJZUVoV87958627 = AYagbohvAtpuekoBJQjJZUVoV59312274;     AYagbohvAtpuekoBJQjJZUVoV59312274 = AYagbohvAtpuekoBJQjJZUVoV22897809;     AYagbohvAtpuekoBJQjJZUVoV22897809 = AYagbohvAtpuekoBJQjJZUVoV36733043;     AYagbohvAtpuekoBJQjJZUVoV36733043 = AYagbohvAtpuekoBJQjJZUVoV87961907;     AYagbohvAtpuekoBJQjJZUVoV87961907 = AYagbohvAtpuekoBJQjJZUVoV98857607;     AYagbohvAtpuekoBJQjJZUVoV98857607 = AYagbohvAtpuekoBJQjJZUVoV71918461;     AYagbohvAtpuekoBJQjJZUVoV71918461 = AYagbohvAtpuekoBJQjJZUVoV71084086;     AYagbohvAtpuekoBJQjJZUVoV71084086 = AYagbohvAtpuekoBJQjJZUVoV87108537;     AYagbohvAtpuekoBJQjJZUVoV87108537 = AYagbohvAtpuekoBJQjJZUVoV59497362;     AYagbohvAtpuekoBJQjJZUVoV59497362 = AYagbohvAtpuekoBJQjJZUVoV3832871;     AYagbohvAtpuekoBJQjJZUVoV3832871 = AYagbohvAtpuekoBJQjJZUVoV47541249;     AYagbohvAtpuekoBJQjJZUVoV47541249 = AYagbohvAtpuekoBJQjJZUVoV90349246;     AYagbohvAtpuekoBJQjJZUVoV90349246 = AYagbohvAtpuekoBJQjJZUVoV28809064;     AYagbohvAtpuekoBJQjJZUVoV28809064 = AYagbohvAtpuekoBJQjJZUVoV19087129;     AYagbohvAtpuekoBJQjJZUVoV19087129 = AYagbohvAtpuekoBJQjJZUVoV67547481;     AYagbohvAtpuekoBJQjJZUVoV67547481 = AYagbohvAtpuekoBJQjJZUVoV91519011;     AYagbohvAtpuekoBJQjJZUVoV91519011 = AYagbohvAtpuekoBJQjJZUVoV6737620;     AYagbohvAtpuekoBJQjJZUVoV6737620 = AYagbohvAtpuekoBJQjJZUVoV95065681;     AYagbohvAtpuekoBJQjJZUVoV95065681 = AYagbohvAtpuekoBJQjJZUVoV82483179;     AYagbohvAtpuekoBJQjJZUVoV82483179 = AYagbohvAtpuekoBJQjJZUVoV11506703;     AYagbohvAtpuekoBJQjJZUVoV11506703 = AYagbohvAtpuekoBJQjJZUVoV62723207;     AYagbohvAtpuekoBJQjJZUVoV62723207 = AYagbohvAtpuekoBJQjJZUVoV70778946;     AYagbohvAtpuekoBJQjJZUVoV70778946 = AYagbohvAtpuekoBJQjJZUVoV36180256;     AYagbohvAtpuekoBJQjJZUVoV36180256 = AYagbohvAtpuekoBJQjJZUVoV77410468;     AYagbohvAtpuekoBJQjJZUVoV77410468 = AYagbohvAtpuekoBJQjJZUVoV70911092;     AYagbohvAtpuekoBJQjJZUVoV70911092 = AYagbohvAtpuekoBJQjJZUVoV23300194;     AYagbohvAtpuekoBJQjJZUVoV23300194 = AYagbohvAtpuekoBJQjJZUVoV51351213;     AYagbohvAtpuekoBJQjJZUVoV51351213 = AYagbohvAtpuekoBJQjJZUVoV30844906;     AYagbohvAtpuekoBJQjJZUVoV30844906 = AYagbohvAtpuekoBJQjJZUVoV95795261;     AYagbohvAtpuekoBJQjJZUVoV95795261 = AYagbohvAtpuekoBJQjJZUVoV71557963;     AYagbohvAtpuekoBJQjJZUVoV71557963 = AYagbohvAtpuekoBJQjJZUVoV78883925;     AYagbohvAtpuekoBJQjJZUVoV78883925 = AYagbohvAtpuekoBJQjJZUVoV40926723;     AYagbohvAtpuekoBJQjJZUVoV40926723 = AYagbohvAtpuekoBJQjJZUVoV77748906;     AYagbohvAtpuekoBJQjJZUVoV77748906 = AYagbohvAtpuekoBJQjJZUVoV65790343;     AYagbohvAtpuekoBJQjJZUVoV65790343 = AYagbohvAtpuekoBJQjJZUVoV9096746;     AYagbohvAtpuekoBJQjJZUVoV9096746 = AYagbohvAtpuekoBJQjJZUVoV16641934;     AYagbohvAtpuekoBJQjJZUVoV16641934 = AYagbohvAtpuekoBJQjJZUVoV43590208;     AYagbohvAtpuekoBJQjJZUVoV43590208 = AYagbohvAtpuekoBJQjJZUVoV49208620;     AYagbohvAtpuekoBJQjJZUVoV49208620 = AYagbohvAtpuekoBJQjJZUVoV65310852;     AYagbohvAtpuekoBJQjJZUVoV65310852 = AYagbohvAtpuekoBJQjJZUVoV82311217;     AYagbohvAtpuekoBJQjJZUVoV82311217 = AYagbohvAtpuekoBJQjJZUVoV53033966;     AYagbohvAtpuekoBJQjJZUVoV53033966 = AYagbohvAtpuekoBJQjJZUVoV94293008;     AYagbohvAtpuekoBJQjJZUVoV94293008 = AYagbohvAtpuekoBJQjJZUVoV25223419;     AYagbohvAtpuekoBJQjJZUVoV25223419 = AYagbohvAtpuekoBJQjJZUVoV56875219;     AYagbohvAtpuekoBJQjJZUVoV56875219 = AYagbohvAtpuekoBJQjJZUVoV65220835;     AYagbohvAtpuekoBJQjJZUVoV65220835 = AYagbohvAtpuekoBJQjJZUVoV19915021;     AYagbohvAtpuekoBJQjJZUVoV19915021 = AYagbohvAtpuekoBJQjJZUVoV18808154;     AYagbohvAtpuekoBJQjJZUVoV18808154 = AYagbohvAtpuekoBJQjJZUVoV38043369;     AYagbohvAtpuekoBJQjJZUVoV38043369 = AYagbohvAtpuekoBJQjJZUVoV45219525;     AYagbohvAtpuekoBJQjJZUVoV45219525 = AYagbohvAtpuekoBJQjJZUVoV41202896;     AYagbohvAtpuekoBJQjJZUVoV41202896 = AYagbohvAtpuekoBJQjJZUVoV92377610;     AYagbohvAtpuekoBJQjJZUVoV92377610 = AYagbohvAtpuekoBJQjJZUVoV95787226;     AYagbohvAtpuekoBJQjJZUVoV95787226 = AYagbohvAtpuekoBJQjJZUVoV89447635;     AYagbohvAtpuekoBJQjJZUVoV89447635 = AYagbohvAtpuekoBJQjJZUVoV16235321;     AYagbohvAtpuekoBJQjJZUVoV16235321 = AYagbohvAtpuekoBJQjJZUVoV25235420;     AYagbohvAtpuekoBJQjJZUVoV25235420 = AYagbohvAtpuekoBJQjJZUVoV88533328;     AYagbohvAtpuekoBJQjJZUVoV88533328 = AYagbohvAtpuekoBJQjJZUVoV86717553;     AYagbohvAtpuekoBJQjJZUVoV86717553 = AYagbohvAtpuekoBJQjJZUVoV59322575;     AYagbohvAtpuekoBJQjJZUVoV59322575 = AYagbohvAtpuekoBJQjJZUVoV17050816;     AYagbohvAtpuekoBJQjJZUVoV17050816 = AYagbohvAtpuekoBJQjJZUVoV75557413;     AYagbohvAtpuekoBJQjJZUVoV75557413 = AYagbohvAtpuekoBJQjJZUVoV20567249;     AYagbohvAtpuekoBJQjJZUVoV20567249 = AYagbohvAtpuekoBJQjJZUVoV40239180;     AYagbohvAtpuekoBJQjJZUVoV40239180 = AYagbohvAtpuekoBJQjJZUVoV91313275;     AYagbohvAtpuekoBJQjJZUVoV91313275 = AYagbohvAtpuekoBJQjJZUVoV87939399;     AYagbohvAtpuekoBJQjJZUVoV87939399 = AYagbohvAtpuekoBJQjJZUVoV24948945;     AYagbohvAtpuekoBJQjJZUVoV24948945 = AYagbohvAtpuekoBJQjJZUVoV6614526;     AYagbohvAtpuekoBJQjJZUVoV6614526 = AYagbohvAtpuekoBJQjJZUVoV12600341;     AYagbohvAtpuekoBJQjJZUVoV12600341 = AYagbohvAtpuekoBJQjJZUVoV63018720;     AYagbohvAtpuekoBJQjJZUVoV63018720 = AYagbohvAtpuekoBJQjJZUVoV9990384;     AYagbohvAtpuekoBJQjJZUVoV9990384 = AYagbohvAtpuekoBJQjJZUVoV81175359;}
// Junk Finished
