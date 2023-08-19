#include "Tile.h"


void Tile::Draw() {
    Texture2D texture = this->m_Focused ? ResPack.Textures["cell_focused.png"] : ResPack.Textures["cell_normal.png"];
    DrawTextureV(texture, this->m_Pos, Color(255, 255, 255, 255));
    Vector2 textSize = MeasureTextEx(this->m_Font, this->m_Text.c_str(), m_TextSize, 1.f);
    DrawTextEx(this->m_Font, this->m_Text.c_str(), Vector2(this->m_Pos.x + this->m_Size.x / 2 - textSize.x / 2, this->m_Pos.y + this->m_Size.y / 2 - textSize.y / 2), m_TextSize, 1.f, m_TextColor);
}

Vector2 Tile::GetPos() {
    return this->m_Pos;
}

Vector2 Tile::GetSize() {
    return this->m_Size; 
}

void Tile::SetPos(Vector2 pos) {
    this->m_Pos = pos; 
}

void Tile::SetSize(Vector2 size) {
    this->m_Size = size; 
}

void Tile::SetFocused(bool focused) { 
    this->m_Focused = focused; 
}

void Tile::SetText(std::string text) { 
    if (!this->m_TextLock) 
        this->m_Text = text; 
}

void Tile::SetTextColor(Color color) { 
    this->m_TextColor = color; 
}

void Tile::SetTextLock(bool isLocked) {
    this->m_TextLock = isLocked; 
}

void Tile::SetFont(Font font) { 
    this->m_Font = font; 
}

//void Tile::SetTextures(std::map<std::string, Texture2D> map) { 
//    this->m_Textures = map; 
//}

void Tile::SetCorrectValue(int32_t Value) { 
    this->m_CorrectValue = Value; 
}

int32_t Tile::GetCorrectValue() { 
    return this->m_CorrectValue; 
}

std::string Tile::GetText() { 
    return this->m_Text; 
}

bool Tile::IsTextLocked() { 
    return this->m_TextLock; 
}

bool Tile::IsFocused() { 
    return this->m_Focused; 
}

bool Tile::IsHovered() {
    Vector2 mousePos = GetMousePosition();
    if (this->m_Pos.x <= mousePos.x and mousePos.x < this->m_Pos.x + this->m_Size.x and this->m_Pos.y <= mousePos.y and mousePos.y < this->m_Pos.y + this->m_Size.y)
        return true;
    return false;
}

bool Tile::IsClicked() {
    if (IsMouseButtonPressed(0) and this->IsHovered())
        return true;
    return false;
}

void Tile::SetID(int32_t ID) {
    this->m_ID = ID;
}

int32_t Tile::GetID() {
    return this->m_ID;
}