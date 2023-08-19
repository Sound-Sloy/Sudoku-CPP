#pragma once
#include <iostream>
#include <string>
#include <raylib.h>
#include <map>
#include <fstream>
#include <vector>
#include "Button.h"
#include "Textbox.h"
#include "Resources.h"

extern Resources::ResourcePack ResPack;
extern Resources::Resources ResourceLoader;

class MainMenu {
private:
	bool m_bShouldDraw = true;
	std::vector<Button> m_Buttons;
	TextBox m_TextBox;
	ButtonProperties::ButtonStyle m_ButtonStyle;

public:
	MainMenu(ButtonProperties::ButtonStyle buttonStyle);
	~MainMenu();
	void Draw();
	void Tick();
	bool ShouldBeDrawn();
};