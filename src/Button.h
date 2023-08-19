#pragma once
#include <iostream>
#include <string>
#include <map>
#include <raylib.h>


namespace ButtonProperties {
	struct ButtonColors;
	enum class ButtonAlignment;
	struct ButtonStyle;
	struct ButtonFont;
}

struct ButtonProperties::ButtonColors {
	bool IsTransparent = false;
	Color BgColor = Color(150, 150, 255, 255);
	Color FgColor = Color(0, 0, 0, 255);
	Color HighlightColor = Color(197, 157, 219, 100);
	Color FocusedColor = Color(197, 157, 219, 255);
	Color BorderColor = Color(0, 0, 0, 255);
};

enum class ButtonProperties::ButtonAlignment {
	CENTER,
	LEFT,
	RIGHT
};

struct ButtonProperties::ButtonFont {
	Font Font = GetFontDefault();
	float Size = 32.0f;
	float Spacing = 1.0f;
};

struct ButtonProperties::ButtonStyle {
	int32_t BorderWidth = 2;
	ButtonProperties::ButtonAlignment Alignment = ButtonProperties::ButtonAlignment::CENTER;
	ButtonProperties::ButtonColors Colors;
	ButtonProperties::ButtonFont Font;
};


class Button {
private:
	std::string m_Text;
	Vector2 m_Pos;
	Vector2 m_Size;
	Font m_Font;
	ButtonProperties::ButtonStyle m_ButtonStyle;
	std::string m_ID;
	Vector2 m_MouseOffset = Vector2(0.f, 0.f);
	void Tick();

public:
	Button(std::string text, std::string ID, Vector2 pos, Vector2 size, ButtonProperties::ButtonStyle style);
	void Draw();
	bool IsHovered();
	bool IsClicked();
	std::string GetText();
	std::string GetID();
	Vector2 GetMouseOffset() const;
	void SetMouseOffset(Vector2 MouseOffset);
};