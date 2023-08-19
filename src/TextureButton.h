#pragma once
#include <iostream>
#include <string>
#include <map>
#include <raylib.h>


namespace TextureButtonProperties {
	struct TextureButtonColors;
	enum class TextureButtonAlignment;
	struct TextureButtonStyle;
}

struct TextureButtonProperties::TextureButtonColors {
	Color HighlightColor = Color(197, 157, 219, 100);
	Color FocusedColor = Color(197, 157, 219, 255);
};

enum class TextureButtonProperties::TextureButtonAlignment {
	CENTER,
	LEFT,
	RIGHT
};


struct TextureButtonProperties::TextureButtonStyle {
	TextureButtonProperties::TextureButtonAlignment Alignment = TextureButtonProperties::TextureButtonAlignment::CENTER;
	TextureButtonProperties::TextureButtonColors Colors;
};


class TextureButton {
private:
	Texture2D m_Texture;
	Vector2 m_Pos;
	Vector2 m_Size;
	TextureButtonProperties::TextureButtonStyle m_ButtonStyle;
	std::string m_ID;
	Vector2 m_MouseOffset = Vector2(0.f, 0.f);
	void Tick();

public:
	TextureButton(Texture2D Texture, std::string ID, Vector2 pos, Vector2 size, TextureButtonProperties::TextureButtonStyle style);
	void Draw();
	bool IsHovered();
	bool IsClicked();
	std::string GetID();
	Vector2 GetMouseOffset() const;
	void SetMouseOffset(Vector2 MouseOffset);
};