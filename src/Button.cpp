#include "Button.h"


Button::Button(std::string text, std::string ID, Vector2 pos, Vector2 size, ButtonProperties::ButtonStyle buttonStyle) {
	this->m_Text = text;
	this->m_ID = ID != "" ? ID : text;
	this->m_Pos = pos;
	this->m_Size = size;
	this->m_ButtonStyle = buttonStyle;
}

void Button::Draw() {
	DrawRectangleV(this->m_Pos, this->m_Size, this->m_ButtonStyle.Colors.BorderColor);

	DrawRectangleV(Vector2(this->m_Pos.x + this->m_ButtonStyle.BorderWidth, this->m_Pos.y + this->m_ButtonStyle.BorderWidth), Vector2(this->m_Size.x - 2 * this->m_ButtonStyle.BorderWidth, this->m_Size.y - 2 * this->m_ButtonStyle.BorderWidth), this->m_ButtonStyle.Colors.BgColor);
	
	if (this->IsHovered()) {
		DrawRectangleV(this->m_Pos, this->m_Size, this->m_ButtonStyle.Colors.HighlightColor);
	}

	Vector2 textSize = MeasureTextEx(this->m_ButtonStyle.Font.Font, this->m_Text.c_str(), this->m_ButtonStyle.Font.Size, this->m_ButtonStyle.Font.Spacing);
	
	Vector2 textAligment = Vector2(this->m_Pos.x + this->m_Size.x / 2 - textSize.x / 2, this->m_Pos.y + this->m_Size.y / 2 - textSize.y / 2);
	if (this->m_ButtonStyle.Alignment == ButtonProperties::ButtonAlignment::LEFT) {
		textAligment = Vector2(this->m_Pos.x + this->m_ButtonStyle.BorderWidth, this->m_Pos.y + this->m_Size.y / 2 - textSize.y / 2);
	}
	if (this->m_ButtonStyle.Alignment == ButtonProperties::ButtonAlignment::RIGHT) {
		textAligment = Vector2(this->m_Pos.x + this->m_Size.x - textSize.x - this->m_ButtonStyle.BorderWidth, this->m_Pos.y + this->m_Size.y / 2 - textSize.y / 2);
	}

	DrawTextEx(this->m_ButtonStyle.Font.Font, this->m_Text.c_str(), textAligment, this->m_ButtonStyle.Font.Size, this->m_ButtonStyle.Font.Spacing, this->m_ButtonStyle.Colors.FgColor);

}

void Button::Tick() {

}

// TO REMOVE v3.12a2
//inline ButtonFlags operator|(ButtonFlags a, ButtonFlags b) {
//	return static_cast<ButtonFlags>(static_cast<int32_t>(a) | static_cast<int32_t>(b));
//}

bool Button::IsHovered() {
	Vector2 mousePos = GetMousePosition();
	mousePos = Vector2(mousePos.x - this->m_MouseOffset.x, mousePos.y - this->m_MouseOffset.y);
	if (mousePos.x >= this->m_Pos.x and mousePos.x <= this->m_Pos.x + this->m_Size.x and mousePos.y >= this->m_Pos.y and mousePos.y <= this->m_Pos.y + this->m_Size.y) {
		return true;
	}
	return false;
}

bool Button::IsClicked() {
	if (this->IsHovered() and IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		std::cout << 'a';
		return true;
	}
	return false;
}

std::string Button::GetText() {
	return this->m_Text;
}

std::string Button::GetID() {
	return this->m_ID;
}

Vector2 Button::GetMouseOffset() const {
	return this->m_MouseOffset;
}

void Button::SetMouseOffset(Vector2 MouseOffset) {
	this->m_MouseOffset = MouseOffset;
}