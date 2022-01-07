#include "Draw.h"

void Draw::Draw3DBox(Vec3 HeadPos, Vec3 Pos, ImColor color) {
	Vec3 tfl = Vec3{ HeadPos.x + 15, HeadPos.y - 15, HeadPos.z };
	Vec3 tfr = Vec3{ HeadPos.x + 15, HeadPos.y + 15, HeadPos.z };
	Vec3 tbl = Vec3{ HeadPos.x - 15, HeadPos.y + 15, HeadPos.z };
	Vec3 tbr = Vec3{ HeadPos.x - 15, HeadPos.y - 15, HeadPos.z  };

	ImVec2 tfl2D, tfr2D, tbl2D, tbr2D;
	if (!WorldToScreen(tfl, tfl2D)) { return; }
	if (!WorldToScreen(tfr, tfr2D)) { return; }
	if (!WorldToScreen(tbl, tbl2D)) { return; }
	if (!WorldToScreen(tbr, tbr2D)) { return; }

	Vec3 bfl = Vec3{ Pos.x + 15, Pos.y - 15, Pos.z };
	Vec3 bfr = Vec3{ Pos.x + 15, Pos.y + 15, Pos.z };
	Vec3 bbl = Vec3{ Pos.x - 15, Pos.y + 15, Pos.z };
	Vec3 bbr = Vec3{ Pos.x - 15, Pos.y - 15, Pos.z };

	ImVec2 bfl2D, bfr2D, bbl2D, bbr2D;
	if (!WorldToScreen(bfl, bfl2D)) { return; }
	if (!WorldToScreen(bfr, bfr2D)) { return; }
	if (!WorldToScreen(bbl, bbl2D)) { return; }
	if (!WorldToScreen(bbr, bbr2D)) { return; }

	ImGui::GetBackgroundDrawList()->AddLine(tbl2D, tfr2D, color, 1.f);
	ImGui::GetBackgroundDrawList()->AddLine(tfl2D, tfr2D, color, 1.f);
	ImGui::GetBackgroundDrawList()->AddLine(tfl2D, tbr2D, color, 1.f);
	ImGui::GetBackgroundDrawList()->AddLine(tbl2D, tbr2D, color, 1.f);

	ImGui::GetBackgroundDrawList()->AddLine(bbl2D, bfr2D, color, 1.f);
	ImGui::GetBackgroundDrawList()->AddLine(bfr2D, bfl2D, color, 1.f);
	ImGui::GetBackgroundDrawList()->AddLine(bfl2D, bbr2D, color, 1.f);
	ImGui::GetBackgroundDrawList()->AddLine(bbr2D, bbl2D, color, 1.f);

	ImGui::GetBackgroundDrawList()->AddLine(bbr2D, tbr2D, color, 1.f);
	ImGui::GetBackgroundDrawList()->AddLine(bbl2D, tbl2D, color, 1.f);
	ImGui::GetBackgroundDrawList()->AddLine(bfr2D, tfr2D, color, 1.f);
	ImGui::GetBackgroundDrawList()->AddLine(bfl2D, tfl2D, color, 1.f);
}

void Draw::Draw2DBox(Vec3 HeadPos, Vec3 Pos, ImColor color){
	ImVec2 Head2D;
	if (!WorldToScreen(HeadPos, Head2D)) { return; }
	ImVec2 Pos2D;
	if (!WorldToScreen(Pos, Pos2D)) { return; }

	float Height = Head2D.y - Pos2D.y;
	Height /= 4;
	ImVec2 tl, tr, bl, br;
	tl = ImVec2{ Head2D.x - Height, Head2D.y };
	tr = ImVec2{ Head2D.x + Height, Head2D.y };

	bl = ImVec2{ Pos2D.x - Height, Pos2D.y };
	br = ImVec2{ Pos2D.x + Height, Pos2D.y };

	ImGui::GetBackgroundDrawList()->AddLine(tl, tr, color);
	ImGui::GetBackgroundDrawList()->AddLine(tr, br, color);
	ImGui::GetBackgroundDrawList()->AddLine(br, bl, color);
	ImGui::GetBackgroundDrawList()->AddLine(bl, tl, color);
}

void Draw::DrawHealth(Vec3 HeadPos, Vec3 Pos, int Health){
	ImVec2 Head2D;
	if (!WorldToScreen(HeadPos, Head2D)) { return; }
	ImVec2 Pos2D;
	if (!WorldToScreen(Pos, Pos2D)) { return; }

	float Height = Head2D.y - Pos2D.y;
	Height /= 4;
	ImVec2 tl, bl;
	tl = ImVec2{ Head2D.x - Height, Head2D.y };
	bl = ImVec2{ Pos2D.x - Height, Pos2D.y };

	float HealthDrawAmout = ((bl.y - tl.y) / 100) * Health;

	ImGui::GetBackgroundDrawList()->AddLine(ImVec2{ bl.x - 3, bl.y }, ImVec2{ bl.x - 3, tl.y }, ImColor{ 0,0,0,50 }, 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2{ bl.x - 3, bl.y }, ImVec2{ bl.x - 3, bl.y - HealthDrawAmout }, ImColor{ 255.f - ((float)Health * 2.55f),(float)Health * 2.55f,0.f,100.f }, 3.f);
}

void Draw::DrawTopSnapLine(Vec3 HeadPos, ImColor color){
	HeadPos.z + 25;
	ImVec2 Head2D;
	if (!WorldToScreen(HeadPos, Head2D)) { return; }
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2{ RefDef->Screen.x / 2, 0 }, Head2D, color, 1.f);
}

void Draw::DrawBottomSnapLine(Vec3 Pos, ImColor color){
	ImVec2 Pos2D;
	if (!WorldToScreen(Pos, Pos2D)) { return; }
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2{ RefDef->Screen.x / 2, RefDef->Screen.y }, Pos2D, color, 1.f);
}

void Draw::DrawName(Vec3 HeadPos, ImColor color, const char* Name){
	HeadPos.z += 40;
	ImVec2 Head2D;
	if (!WorldToScreen(HeadPos, Head2D)) { return; }
	ImGui::GetBackgroundDrawList()->AddText(Head2D, color, Name);
}