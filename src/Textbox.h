#pragma once
#include <iostream>
#include <string>
#include <raylib.h>
#include "Utils.h"


namespace {
    struct TBOptions {
        uint32_t CursorBlinkShowTimeMilli = 500;
        uint32_t CursorBlinkHideTimeMilli = 500;
        uint32_t BorderSize = 0;
    };

    struct TBFont {
        Font Font = GetFontDefault();
        float Size = 20.f;
        float Spacing = 1.f;
    };

    struct TBColors {
        Color BgColor = Color(200, 200, 200, 255);
        Color FgColor = Color(0, 0, 0, 255);
        Color PlaceholderColor = Color(130, 130, 130, 255);
        Color CursorColor = Color(55, 55, 55, 255);
        Color BorderColor = Color(0, 0, 0, 255);
        //Color ScrollBgColor = Color(150, 150, 150, 255);
        //Color ScrollDragColor = Color(0, 0, 0, 255);
    };

    struct TBStyle {
        TBFont Font;
        TBColors Colors;
    };
}

struct TextBoxProperties {
    ::TBStyle Style;
    ::TBOptions Options;
};

class TextBox {
private:
    Vector2 m_Pos;
    Vector2 m_Size;
    uint32_t m_MaxChars;
    std::string m_Text = "";
    std::string m_ShowText = "";
    std::string m_PlaceholderText;
    std::string m_Mask;
    bool m_bIsActive;
    TextBoxProperties m_Properties;
    uint32_t m_CursorTimer = static_cast<uint32_t>(GetTime() * 1000);
    bool m_ShowCursor = false;
    Vector2 m_MouseOffset = Vector2(0.f, 0.f);

    std::string GetPasswordText() const;
    Rectangle GetTextBoxRectangle() const;

    Color InvertColor(Color Col) const;
    void DrawLineCursor() const;

    bool IsClickedOutsideBoundaries() const;

public:
    TextBox(Vector2 Pos, Vector2 Size, std::string PlaceholderText, std::string Mask, uint32_t MaxChars, TextBoxProperties Properties);
    TextBox();

    void Draw();

    void Update();

    bool IsHovered() const;
    bool IsClicked() const;

    std::string GetText() const;

    Vector2 GetMouseOffset() const;
    void SetMouseOffset(Vector2 MouseOffset);
};
