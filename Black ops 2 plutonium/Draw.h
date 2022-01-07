#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include "ImGui/imgui.h"

#include "Vector.h"
#include "W2S.h"

class Draw {
public:
	static void Draw3DBox(Vec3 HeadPos, Vec3 Pos, ImColor color);
	static void Draw2DBox(Vec3 HeadPos, Vec3 Pos, ImColor color);
	static void DrawHealth(Vec3 HeadPos, Vec3 Pos, int Health);
	static void DrawTopSnapLine(Vec3 HeadPos, ImColor color);
	static void DrawBottomSnapLine(Vec3 Pos, ImColor color);
	static void DrawName(Vec3 Pos, ImColor color, const char* Name);
};