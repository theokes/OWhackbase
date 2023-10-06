#pragma once

#include <windows.h>
#include <thread>
#include "Offsets.h"
#include "Structures.h"



void mouse_click() {
	mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, 0, 0); 
	Sleep(10);
}

bool isInsideFov(int x, int y, int ScreenWidth, int ScreenHeight, int Fov) {
	int centerx = ScreenWidth / 2;
	int centery = ScreenHeight / 2;
	if ((x - centerx) * (x - centerx) + (y - centery) * (y - centery) <= Fov * Fov)
		return true;
	else
		return false;
}

float CenterDist(int x, int y, int ScreenWidth, int ScreenHeight) {
	int centerx = ScreenWidth / 2;
	int centery = ScreenHeight / 2;
	return (x - centerx) * (x - centerx) + (y - centery) * (y - centery);
}



void mouse_move(DWORD x, DWORD y)
{
	INPUT inputLOL = { 1 };
	inputLOL.type = INPUT_MOUSE;
	inputLOL.mi.dwFlags = TOUCHEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK;
	inputLOL.mi.dx = x;
	inputLOL.mi.dy = y;
	SendInput(1, &inputLOL, sizeof(inputLOL));
}



void FlickBot(int ScreenWidth, int ScreenHeight, float x, float y, int AimSpeed, int smoothness) {
	int ScreenCenterX = ScreenWidth / 2, ScreenCenterY = ScreenHeight / 2;

	float TargetX = 0;
	float TargetY = 0;

	if (x != 0) {
		if (x > ScreenCenterX) {
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX) {
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (y != 0) {
		if (y > ScreenCenterY) {
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY) {
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}
	TargetX /= smoothness;
	TargetY /= smoothness;


	mouse_move((int)TargetX, (int)(TargetY));
	//SonyDriverHelper::api::MouseMove(TargetX, TargetY);
	mouse_click();
	Sleep(50);
	//SonyDriverHelper::api::MouseMove(TargetX, TargetY);
	mouse_move((int)TargetX, (int)(TargetY));
}