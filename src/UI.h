#pragma once
#include <iostream>
#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>
#include <vector>
#include <filesystem>

#include "Board.h"
#include "Resources.h"

extern Resources::Resources ResourceLoader;
extern Resources::ResourcePack ResPack;

class UI {
private:
	bool m_MenuBarToggle = false;
	ImGuiIO m_IO = ImGui::GetIO();
	ImFont* m_Font = m_IO.Fonts->AddFontDefault();
	std::vector<std::string> m_Texturepacks;
	Board* m_Board;

	void SetStyle();
	void RefreshTexturepackList();
public:
	UI(Board* board);
	void Render();
	void Tick();
	ImGuiIO GetIO();
};