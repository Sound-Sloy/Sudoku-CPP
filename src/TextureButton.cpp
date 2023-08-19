#include "TextureButton.h"


TextureButton::TextureButton(Texture2D Texture, std::string ID, Vector2 pos, Vector2 size, TextureButtonProperties::TextureButtonStyle style) {
	this->m_Texture = Texture;
	this->m_ID = ID != "" ? ID : std::to_string(Texture.id);
	this->m_Pos = pos;
	this->m_Size = Vector2( size.x ? size.x : Texture.width , size.y ? size.y : Texture.height );
	this->m_ButtonStyle = style;
}

void TextureButton::Draw() {
	if (this->IsHovered()) {
		DrawRectangleV(this->m_Pos, this->m_Size, this->m_ButtonStyle.Colors.HighlightColor);
	}

	float Scale = 1.f;
	if (this->m_Size.x < this->m_Texture.width or this->m_Size.y < this->m_Texture.height) {
		if (this->m_Size.x < this->m_Size.y) {
			Scale = this->m_Size.x / this->m_Texture.width;
		}
		if (this->m_Size.y < this->m_Size.x) {
			Scale = this->m_Size.y / this->m_Texture.height;
		}
	}

	Vector2 TextureAligment = Vector2(this->m_Pos.x + this->m_Size.x / 2 - this->m_Texture.width * Scale / 2, this->m_Pos.y + this->m_Size.y / 2 - this->m_Texture.height * Scale / 2);
	if (this->m_ButtonStyle.Alignment == TextureButtonProperties::TextureButtonAlignment::LEFT) {
		TextureAligment = Vector2(this->m_Pos.x, this->m_Pos.y + this->m_Size.y / 2 - this->m_Texture.height * Scale / 2);
	}

	if (this->m_ButtonStyle.Alignment == TextureButtonProperties::TextureButtonAlignment::RIGHT) {
		TextureAligment = Vector2(this->m_Pos.x + this->m_Size.x - this->m_Texture.width * Scale, this->m_Pos.y + this->m_Size.y / 2 - this->m_Texture.height * Scale / 2);
	}

	DrawTextureEx(this->m_Texture, TextureAligment, 0.f, Scale, Color(255, 255, 255, 255));
}

void TextureButton::Tick() {

}

bool TextureButton::IsHovered() {
	Vector2 mousePos = GetMousePosition();
	mousePos = Vector2(mousePos.x - this->m_MouseOffset.x, mousePos.y - this->m_MouseOffset.y);

	if (mousePos.x >= this->m_Pos.x and mousePos.x <= this->m_Pos.x + this->m_Size.x and mousePos.y >= this->m_Pos.y and mousePos.y <= this->m_Pos.y + this->m_Size.y) {
		return true;
	}
	return false;
}

bool TextureButton::IsClicked() {
	if (this->IsHovered() and IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		std::cout << 'a';
		return true;
	}
	return false;
}

std::string TextureButton::GetID() {
	return this->m_ID;
}

Vector2 TextureButton::GetMouseOffset() const {
	return this->m_MouseOffset;
}

void TextureButton::SetMouseOffset(Vector2 MouseOffset) {
	this->m_MouseOffset = MouseOffset;
}