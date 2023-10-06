#pragma once

#include "Drawing.h"
#include "ImGui/imgui.h"
#include <io.h>
#include <xmmintrin.h>
#include <immintrin.h>

float powf_(float _X, float _Y) {
	return (_mm_cvtss_f32(_mm_pow_ps(_mm_set_ss(_X), _mm_set_ss(_Y))));
}

double GetDistance(double x1, double y1, double z1, double x2, double y2, double z2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;
	double dz = z2 - z1;
	return sqrt(dx * dx + dy * dy + dz * dz);
}

int Width = GetSystemMetrics(SM_CXSCREEN);
int Height = GetSystemMetrics(SM_CYSCREEN);

ImVec4 GetRotatingRGBColor()
{
	static float hue = 0.0f;
	hue += 0.00003f; //speed tyype shit
	if (hue > 1.0f)
		hue -= 1.0f;

	float color_red, color_green, color_blue;
	ImGui::ColorConvertHSVtoRGB(hue, 1.0f, 1.0f, color_red, color_green, color_blue);

	return ImVec4(color_red, color_green, color_blue, 1.0f);

}

void MenuWindow()
{

	auto& style = ImGui::GetStyle();

	style.WindowMinSize = ImVec2(621, 350);
	style.WindowTitleAlign = ImVec2(0.5, 0.5);
	style.FrameBorderSize = 1;
	style.ChildBorderSize = 1;
	style.WindowBorderSize = 1;
	style.WindowRounding = 10;
	style.FrameRounding = 0;
	style.ChildRounding = 5;
	style.Colors[ImGuiCol_WindowBg] = ImColor(0, 0, 0, 150);;
	style.Colors[ImGuiCol_ChildBg] = ImColor(0, 0, 0, 255);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	style.Colors[ImGuiCol_Border] = ImColor(21, 21, 21, 0);
	style.Colors[ImGuiCol_BorderShadow] = ImColor(21, 21, 21, 0);


	style.Colors[ImGuiCol_FrameBg] = ImColor(0, 0, 0, 255);
	style.Colors[ImGuiCol_FrameBgHovered] = ImColor(0, 0, 0, 255);
	style.Colors[ImGuiCol_FrameBgActive] = ImColor(0, 255, 225, 160);
	style.Colors[ImGuiCol_TitleBg] = ImColor(31, 31, 31);
	style.Colors[ImGuiCol_TitleBgActive] = ImColor(31, 31, 31);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(31, 31, 31);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImColor(0, 255, 225, 255);
	style.Colors[ImGuiCol_SliderGrab] = ImColor(0, 255, 225, 255);
	style.Colors[ImGuiCol_SliderGrabActive] = ImColor(0, 255, 225, 255);
	style.Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(255, 255, 255);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);


	ImGui::SetNextWindowSize(ImVec2(500, 300), ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::Begin("Overwatch External", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse);
	{

		ImGui::Columns(2);

		ImGui::SetColumnOffset(1, 120);
		{
			static ImVec4 Active = ImColor(0, 255, 225, 50);
			static ImVec4 InActive = ImColor(21, 21, 21, 0);

			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::PushStyleColor(ImGuiCol_Button, Tab == 1 ? Active : InActive);
			if (ImGui::Button("Aim", ImVec2(100, 50)))
				Tab = 1;

			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::PushStyleColor(ImGuiCol_Button, Tab == 2 ? Active : InActive);
			if (ImGui::Button("Visuals", ImVec2(100, 50)))
				Tab = 2;


			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::PushStyleColor(ImGuiCol_Button, Tab == 3 ? Active : InActive);
			if (ImGui::Button("Misc", ImVec2(100, 50)))
				Tab = 3;


			//Right side
			ImGui::NextColumn();
			{
				
				if (Tab == 1)
				{
					ImGui::Text("Category: "); ImGui::SameLine(); style.Colors[ImGuiCol_Text] = ImColor(0, 255, 225, 255); ImGui::Text("Aim");
					style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);

					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Checkbox("Enable Aimbot", &SonyAim);

					if (SonyAim)
					{
						ImGui::Spacing();
						ImGui::Checkbox("Display Fov", &ShowFov);
						if (ShowFov)
						{
							ImGui::Spacing();
							ImGui::SliderInt("Fov Size", &FovCircle, 10, 500);
						}
						ImGui::Spacing();
						ImGui::Combo("Aim Key", &SelectedKey, KeyNames, IM_ARRAYSIZE(KeyNames));
						ImGui::Spacing();
						ImGui::Checkbox("Enable TriggerBot", &isTriggerBot);
					}

					ImGui::Spacing(); 
					ImGui::SliderInt("X Smoothness", &Smoothnessx, 1, 50);
					ImGui::Spacing();
					ImGui::SliderInt("Y Smoothness", &Smoothnessy, 1, 50);
					ImGui::Spacing();
				}

				if (Tab == 2)
				{
					ImGui::Text("Category: "); ImGui::SameLine(); style.Colors[ImGuiCol_Text] = ImColor(0, 255, 225, 255); ImGui::Text("Visuals");
					style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Checkbox("Display 2D Box", &twodBox);
					ImGui::Spacing();
					ImGui::Checkbox("Display Snaplines", &Snaplines);
					ImGui::Spacing();
					ImGui::Checkbox("Display Head Circle", &HeadVisual);
				}

				if (Tab == 3)
				{
					ImGui::Text("Category: "); ImGui::SameLine(); style.Colors[ImGuiCol_Text] = ImColor(0, 255, 225, 255); ImGui::Text("Misc");
					style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Checkbox("Display FPS", &ShowFps);
					ImGui::Spacing();
					ImGui::Checkbox("Display Watermark", &Watermark);
					ImGui::Spacing();
					ImGui::Checkbox("Refresh Team Check", &ChangeTeam);
				}
			}
		}
	}
}

void ActorLoop()
{
	float closestDistance = FLT_MAX;
	DWORD_PTR closestPawn = NULL;

	if (GetAsyncKeyState(VK_F2) & 1) //panic/exit key
	{
		CloseHandle(ProcessHandle);
		exit(0);
	}

	if (ShowFov)
	{
		DrawCircle(Vector2(Width / 2, Height / 2), FovCircle, Color(0, 255, 217));
	}


	Matrix ViewMatrix = Read<Matrix>(Read<uintptr_t>(ModuleBase + Offsets::ViewMatrix) + Offsets::ViewMatrix_Ptr);


	for (int i = 0; i < Entity.size(); i++)
	{
		Vector3 Origin = Read<Vector3>(Entity[i] - Offsets::Origin); Origin.y -= 0.5;
		Vector3 Head = Read<Vector3>(Entity[i] - Offsets::Head); Head.x -= 0.8; Head.y -= 0.2;

		bool isAive = Read<BYTE>(Entity[i] - Offsets::Alive) == Offsets::Alive_Ret; if (isAive == false) continue;

		if (!ChangeTeam)
		{
			bIsTeam = Read<BYTE>(Entity[i] - Offsets::Team) != Offsets::OwnTeam;
		}
		else
		{
			bIsTeam = Read<BYTE>(Entity[i] - Offsets::Team) != Offsets::EnemyTeam;
		}

		if (!bIsTeam) continue;

		Vector2 OriginPos = WorldToScreen(Origin, ViewMatrix, Width, Height);
		Vector2 HeadPos = WorldToScreen(Head, ViewMatrix, Width, Height);


		if (OutsideBorder(OriginPos, Vector2(Width, Height)) != 0) continue;

		float BoxHeight = abs(HeadPos.y - OriginPos.y);
		float BoxWidth = BoxHeight * 0.65f;
		Rect PlayerRect(HeadPos.x - (BoxWidth / 2), HeadPos.y, BoxWidth, BoxHeight);

		//if (bIsTeam)
		//{
		//	ImVec2 playtextPos(PlayerRect.x, PlayerRect.y - 20);
		//	ImVec4 rotatingColor = GetRotatingRGBColor();
		//	ImGui::GetBackgroundDrawList()->AddText(playtextPos, ImColor(rotatingColor.x * 255, rotatingColor.y * 255, rotatingColor.z * 255), "Team");
		//}

		//if (!bIsTeam)
		//{
		//	ImVec2 playtextPos(PlayerRect.x, PlayerRect.y - 20);
		//	ImVec4 rotatingColor = GetRotatingRGBColor();
		//	ImGui::GetBackgroundDrawList()->AddText(playtextPos, ImColor(rotatingColor.x * 255, rotatingColor.y * 255, rotatingColor.z * 255), "Ememy");
		//}

		if (twodBox)
		{
			ImVec4 rotatingColor = GetRotatingRGBColor();
			DrawCornerBox(PlayerRect, Color(0, 0, 0), Color(rotatingColor.x * 255, rotatingColor.y * 255, rotatingColor.z * 255), 2);
		}


		if (ShowFps)
		{
			ImVec4 rotatingColor = GetRotatingRGBColor();
			char dist[128];
			sprintf_s(dist, 128, "FPS: %.f\n", ImGui::GetIO().Framerate);
			auto sizeC = ImGui::CalcTextSize(dist);
			ImGui::GetBackgroundDrawList()->AddText(ImVec2((float)(Width / 2) - (sizeC.x / 2), 1), ImColor(rotatingColor.x * 255, rotatingColor.y * 255, rotatingColor.z * 255), dist);
		}

		if (Watermark)
		{
			ImVec2 textPos(15, 15);
			ImVec4 rotatingColor = GetRotatingRGBColor();
			ImGui::GetBackgroundDrawList()->AddText(textPos, ImColor(rotatingColor.x * 255, rotatingColor.y * 255, rotatingColor.z * 255), "OW2 External");
		}


		if (Snaplines)
		{
			Vector2 middleOfScreen = Vector2(Width / 2, Height / 2);
			DrawLine(middleOfScreen, HeadPos, Color(0, 0, 0), 1.25);
		}

		if (HeadVisual)
		{
			ImGui::GetForegroundDrawList()->AddCircle(ImVec2(HeadPos.x, HeadPos.y), BoxWidth / 15, ImColor(0, 0, 0), 50);
		}

	}
}


void AimbotLoop()
{
	Matrix ViewMatrix = Read<Matrix>(Read<uintptr_t>(ModuleBase + Offsets::ViewMatrix) + Offsets::ViewMatrix_Ptr);
	float closestDistance = FLT_MAX;
	DWORD_PTR closestPawn = NULL;

	for (int i = 0; i < Entity.size(); i++)
	{
		Vector3 aiboner = Read<Vector3>(Entity[i] - Offsets::Head); aiboner.x -= 0.8; aiboner.y -= 0.2;

		Vector2 Aimposition = WorldToScreen(aiboner, ViewMatrix, Width, Height);

		auto dx = Aimposition.x - (Width / 2);
		auto dy = Aimposition.y - (Height / 2);
		auto dist = sqrtf(dx * dx + dy * dy);

		if (dist < FovCircle && dist < closestDistance)
		{
			closestDistance = dist;
			closestPawn = Entity[i]; //player logic
		}
		else
		{

		}


		if (SonyAim)
		{
			if (closestPawn && GetAsyncKeyState(KeyCodes(SelectedKey)))
			{
				Vector3 AimPos = Read<Vector3>(Entity[i] - Offsets::Head); AimPos.x -= 0.8;

				if (AimPos.x != 0 || AimPos.y != 0 || AimPos.z != 0)
				{
					AimPos.y -= 0.5;
					Vector2 Headboxy = WorldToScreen(AimPos, ViewMatrix, Width, Height);

					double distanceToCenter = GetDistance(Headboxy.x, Headboxy.y, 0, Width / 2, Height / 2, 0);

					if (distanceToCenter <= FovCircle)
					{
						AimBot(Headboxy.x, Headboxy.y);
					}
				}
				else
				{
					closestDistance = FLT_MAX;
					closestPawn = NULL;
				}
			}
		}
	}
}