#pragma once
#include <raylib.h>
#include <string>
#include <map>
#include "SudokuGenerator.h"
#include "Resources.h"

extern Resources::ResourcePack ResPack;

class Tile {
private:
    Vector2 m_Pos = Vector2(0, 0);
    Vector2 m_Size = Vector2(0, 0);
    bool m_Focused = false;
    //std::map<std::string, Texture2D> m_Textures;
    Font m_Font = GetFontDefault();
    float m_TextSize = 48.f;
    Color m_TextColor = Color(0, 0, 0, 255);
    bool m_TextLock = false;
    std::string m_Text = "";
    int32_t m_CorrectValue = 0;
    int32_t m_ID = 0;
public:
    void Draw();
    Vector2 GetPos();
    Vector2 GetSize();
    void SetPos(Vector2 pos);
    void SetSize(Vector2 size);
    void SetFocused(bool focused);
    void SetText(std::string text);
    void SetTextColor(Color color);
    void SetTextLock(bool isLocked);
    void SetFont(Font font);
    void SetID(int32_t ID);
    int32_t GetID();
    //void SetTextures(std::map<std::string, Texture2D> map);
    void SetCorrectValue(int32_t Value);
    int32_t GetCorrectValue();
    std::string GetText();
    bool IsTextLocked();
    bool IsFocused();
    bool IsHovered();
    bool IsClicked();
};