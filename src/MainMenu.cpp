#include "MainMenu.h"


MainMenu::MainMenu(ButtonProperties::ButtonStyle buttonStyle) {
	this->m_ButtonStyle = buttonStyle;
	this->m_Buttons.push_back(Button("Play", "1#ButtPlay", Vector2(static_cast<float>((GetRenderWidth() - 150) / 2), static_cast<float>((GetRenderHeight() - 50 - 50 + 20) / 2)), Vector2(150.f, 50.f), this->m_ButtonStyle));
	this->m_Buttons.push_back(Button("Stats", "1#ButtStats", Vector2(static_cast<float>((GetRenderWidth() - 100) / 2), static_cast<float>((GetRenderHeight() - 50 + 50 + 30) / 2)), Vector2(100.f, 50.f), this->m_ButtonStyle));

	TextBoxProperties Properties;
	Properties.Style.Colors.FgColor = Color(150, 0, 150, 255);
	Properties.Style.Colors.BorderColor = Color(150, 0, 0, 255);
	Properties.Options.BorderSize = 2;
	this->m_TextBox = TextBox(Vector2(200, 200), Vector2(150, 30), "Name", "", 0, Properties);
	

}

MainMenu::~MainMenu() {
	//delete m_TextBox;
}

void MainMenu::Draw() {
	if (!m_bShouldDraw) return;

	ClearBackground(Color(255, 255, 255, 255));
	for (auto& button : this->m_Buttons) {
		button.Draw();
	}
	m_TextBox.Update();
	m_TextBox.Draw();
	
}

void MainMenu::Tick() {
	
	for (auto& button : this->m_Buttons) {
		if (button.IsClicked() and button.GetID() == "1#ButtPlay") {
			this->m_bShouldDraw = false;
		}
	}
	
	if (this->m_bShouldDraw) {
		this->Draw();
	}
}

bool MainMenu::ShouldBeDrawn() {
	return this->m_bShouldDraw;
}