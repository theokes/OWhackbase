#pragma once

#include <Windows.h>
#include <vector>
#include <string>

namespace SonyDriverHelper
{
	class api 
	{
	public:
		static void Init();

		static void MouseMove(float x, float y);

		static bool GetKey(int id);
	};
}
;

std::vector<uintptr_t> Entity{};

int index = -1;

int Tab = 0;
int SelectedKey = 0;

bool DisplayMenu = true;
bool CreateConsole = true;


bool AutoUpdate = true;
bool bIsTeam;

bool ChangeTeam = true;
bool Snaplines = false;
bool twodBox = true;
bool HeadVisual = false;
bool ShowFps = false;
bool Watermark = true;
bool ShowFov = true;
bool fastoverlay = false;

const char* BoxTypeName = "Box Type";
const char* LineTypeName = "Default";

int LineType = 1;
int BoxType = 1;

int FovCircle = 100;
int Smoothnessx = 10;
int Smoothnessy = 10;
int Bone = 1;

const char* BoneName = "Head";

bool SonyAim = false;
bool RandomAim = false;
bool isTriggerBot = false;

namespace Offsets
{
	BYTE AOB[] = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFF\x02\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00";
	std::string MASK = "??xx??xx?xxx?xxxxxxxxxxxxxxx???";

	enum Offsets {
		EntitySize = 0x180000,

		ViewMatrix = 0x3D5EED8,
		ViewMatrix_Ptr = 0x7E0,

		Origin = 0x9C,
		Head = 0x8C,

		Alive = 0x1,
		Alive_Ret = 0x14,

		Team = 0x21,
		EnemyTeam = 0x8,
		OwnTeam = 0x10,
	};
}