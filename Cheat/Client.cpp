#include "Client.h"

//[enc_string_enable /]
//[junk_enable /]

namespace Client
{
	//[swap_lines]
	int	iScreenWidth = 0;
	int	iScreenHeight = 0;

	string BaseDir = "";
	string LogFile = "";
	string GuiFile = "";
	string IniFile = "";

	vector<string> ConfigList;

	Vector2D	g_vCenterScreen = Vector2D(0.f, 0.f);

	CPlayers*	g_pPlayers = nullptr;
	CRender*	g_pRender = nullptr;
	CGui*		g_pGui = nullptr;

	CEsp*		g_pEsp = nullptr;
	CMisc*		g_pMisc = nullptr;

	//[/swap_lines]
	bool Initialize(IDirect3DDevice9* pDevice)
	{
		g_pPlayers = new CPlayers();
		g_pRender = new CRender(pDevice);
		g_pGui = new CGui();

		g_pEsp = new CEsp();
		g_pMisc = new CMisc();

		g_pGui->GUI_Init(pDevice);

		return true;
	}
	//
	void Shutdown()
	{
		DELETE_MOD(g_pPlayers);
		DELETE_MOD(g_pRender);
		DELETE_MOD(g_pGui);

		DELETE_MOD(g_pEsp);
		DELETE_MOD(g_pMisc);
	}
	//cracked by |Konders,IkFakof |
	void OnRender()
	{
		if (g_pRender && !Interfaces::Engine()->IsTakingScreenshot() && Interfaces::Engine()->IsActiveApp())
		{
			g_pRender->BeginRender();

			if (g_pGui)
				g_pGui->GUI_Draw_Elements();

			Interfaces::Engine()->GetScreenSize(iScreenWidth, iScreenHeight);

			g_vCenterScreen.x = iScreenWidth / 2.f;
			g_vCenterScreen.y = iScreenHeight / 2.f;

			if (!Interfaces::Engine()->IsConnected())
			{
				g_pRender->Text(5, 3, false, true, Color::LightGray(), HACK_NAME);
				g_pRender->Text(5, 13, false, true, Color::LightGray(), "UnknownCheats");
			}

			if (Client::g_pPlayers && Client::g_pPlayers->GetLocal() && Interfaces::Engine()->IsInGame())
			{
				if (g_pEsp)
					g_pEsp->OnRender();

			}

			g_pRender->EndRender();
		}
	}


	void OnLostDevice()
	{
		if (g_pRender)
			g_pRender->OnLostDevice();

		if (g_pGui)
			ImGui_ImplDX9_InvalidateDeviceObjects();
	}

	void OnResetDevice()
	{
		if (g_pRender)
			g_pRender->OnResetDevice();

		if (g_pGui)
			ImGui_ImplDX9_CreateDeviceObjects();
	}

	void OnCreateMove(CUserCmd* pCmd)
	{
		if (g_pPlayers && Interfaces::Engine()->IsInGame())
		{
			g_pPlayers->Update();

			if (g_pEsp)
				g_pEsp->OnCreateMove(pCmd);

			if (IsLocalAlive())
			{
				//if ( !bIsGuiVisible )
				//{
				//	int iWeaponSettingsSelectID = GetWeaponSettingsSelectID();

				//	if ( iWeaponSettingsSelectID >= 0 )
				//		iWeaponID = iWeaponSettingsSelectID;
				//}

				if (g_pMisc)
					g_pMisc->OnCreateMove(pCmd);
			}
		}
	}

	void OnFireEventClientSideThink(IGameEvent* pEvent)
	{
		if (!strcmp(pEvent->GetName(), "player_connect_full") ||
			!strcmp(pEvent->GetName(), "round_start") ||
			!strcmp(pEvent->GetName(), "cs_game_disconnected"))
		{
			if (g_pPlayers)
				g_pPlayers->Clear();

		}
	}

	//void OnFrameStageNotify( ClientFrameStage_t Stage )
	//{
	//	if ( Interfaces::Engine()->IsInGame() )
	//	{
	//		Skin_OnFrameStageNotify( Stage );
	//		Gloves_OnFrameStageNotify( Stage );
	//	}
	//}

	void OnDrawModelExecute(IMatRenderContext* ctx, const DrawModelState_t &state,
		const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
	{
		if (Interfaces::Engine()->IsInGame() && ctx && pCustomBoneToWorld)
		{
			if (g_pEsp)
				g_pEsp->OnDrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);


		}
	}



	void OnRenderGUI()
	{

		if (ImGui::Begin(HACK_NAME, &bIsGuiVisible, ImVec2(450.f, 275.f), ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
		{
			ImGuiWindowFlags flags;
			flags == ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
			const char* tabNames[] = { VISUAL_TEXT , COLORMENU_TEXT };

			static int tabOrder[] = { 0 , 1 };
			static int tabSelected = 0;
			const bool tabChanged = ImGui::TabLabels(tabNames,
				sizeof(tabNames) / sizeof(tabNames[0]),
				tabSelected, tabOrder);

			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();

			float SpaceLineOne = 120.f;
			float SpaceLineTwo = 220.f;
			float SpaceLineThr = 320.f;

			if (tabSelected == 0) // Visuals 
			{

				flags ==  ImGuiWindowFlags_NoResize;
				ImGui::SetWindowSize(ImVec2(353.f, 250.f));
				ImVec2 siz = ImGui::GetWindowSize();
				ImVec2 pos = ImGui::GetWindowPos();
				ImDrawList* windowDrawList = ImGui::GetWindowDrawList();

				static float rainbow;
				rainbow += 0.00200f;
				if (rainbow > 1.f) {
					rainbow = 0.f;
				}

				for (int i = 0; i < siz.x; i++)
				{
					float flvalue = (1.f / (float)siz.x) * i;
					flvalue -= rainbow;
					if (flvalue < 0.f)
						flvalue += 1.f;

					windowDrawList->AddRectFilled(ImVec2(pos.x + i, pos.y), ImVec2(pos.x + siz.x, pos.y + 22), ImColor().HSV(flvalue, 1.f, 1.f));
				}

				ImGui::Checkbox("Chams", &Settings::Esp::esp_chams); 
				if (Settings::Esp::esp_chams)
					Settings::Esp::esp_Chams = 1;
				else
					Settings::Esp::esp_Chams = 0;

				ImGui::PushItemWidth(339.f);
				
				ImGui::Checkbox("Esp box", &Settings::Esp::espb);
				ImGui::PopItemWidth();

				ImGui::Spacing();
				ImGui::Separator();
				ImGui::Spacing();

				ImGui::Checkbox("Esp Health", &Settings::Esp::esp_Health);


				ImGui::Checkbox("Esp Armor", &Settings::Esp::esp_Armor);
				ImGui::Spacing();
				ImGui::Separator();
				ImGui::Spacing();

				ImGui::Checkbox("Name", &Settings::Esp::esp_Name);
				ImGui::SameLine(SpaceLineOne);
				ImGui::Checkbox("Weapon", &Settings::Esp::esp_Weapon);
				ImGui::SameLine(SpaceLineTwo);
				ImGui::Checkbox("Skeleton", &Settings::Esp::esp_Skeleton);

				ImGui::Checkbox("Distance", &Settings::Esp::esp_Distance);
				ImGui::SameLine(SpaceLineOne);
				ImGui::Checkbox("Rank hack", &Settings::Esp::esp_Rank);

				ImGui::Spacing();
				ImGui::Separator();
				ImGui::Spacing();

				ImGui::Checkbox("Esp Weapon", &Settings::Esp::esp_WorldWeapons);
				ImGui::Checkbox("Esp Grenade", &Settings::Esp::esp_WorldGrenade);



			}

			else if (tabSelected == 1) // Colors 
			{
				flags == ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
				ImGui::SetWindowSize(ImVec2(353.f, 250.f));

				ImVec2 siz = ImGui::GetWindowSize();
				ImVec2 pos = ImGui::GetWindowPos();

				ImDrawList* windowDrawList = ImGui::GetWindowDrawList();

				static float rainbow;
				rainbow += 0.00200f;
				if (rainbow > 1.f) {
					rainbow = 0.f;
				}

				for (int i = 0; i < siz.x; i++)
				{
					float flvalue = (1.f / (float)siz.x) * i;
					flvalue -= rainbow;
					if (flvalue < 0.f)
						flvalue += 1.f;

					windowDrawList->AddRectFilled(ImVec2(pos.x + i, pos.y), ImVec2(pos.x + siz.x, pos.y + 22), ImColor().HSV(flvalue, 1.f, 1.f));
				}
			
				ImGui::ColorEdit3("Esp Color CT", Settings::Esp::esp_Color_CT);
				ImGui::ColorEdit3("Esp Color TT", Settings::Esp::esp_Color_TT);
				ImGui::ColorEdit3("Esp Color Visible CT", Settings::Esp::esp_Color_VCT);
				ImGui::ColorEdit3("Esp Color Visible TT", Settings::Esp::esp_Color_VTT);
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::ColorEdit3("Chams Color CT", Settings::Esp::chams_Color_CT);
				ImGui::ColorEdit3("Chams Color TT", Settings::Esp::chams_Color_TT);
				ImGui::ColorEdit3("Chams Color Visible CT", Settings::Esp::chams_Color_VCT);
				ImGui::ColorEdit3("Chams Color Visible TT", Settings::Esp::chams_Color_VTT);

				ImGui::Spacing(); 
				ImGui::Spacing(); 
				ImGui::ColorEdit3("Skeleton Color",Settings::Esp::esp_Color_Skeleton); 
				ImGui::ColorEdit3("Esp Text Color", Settings::Esp::esp_Color_Text);


			}

			ImGui::End();
		}
	}	
}
	






















































































