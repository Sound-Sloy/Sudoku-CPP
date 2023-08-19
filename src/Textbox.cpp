#include "Textbox.h"


TextBox::TextBox(Vector2 Pos, Vector2 Size, std::string PlaceholderText, std::string Mask, uint32_t MaxChars, TextBoxProperties Properties) {
    this->m_Pos = Pos;
    this->m_Size = Size;
    this->m_PlaceholderText = PlaceholderText;
    this->m_Mask = Mask;
    this->m_MaxChars = MaxChars;
    this->m_bIsActive = false;
    this->m_Properties = Properties;
}

TextBox::TextBox() {
    this->m_Pos = Vector2();
    this->m_Size = Vector2();
    this->m_PlaceholderText = "";
    this->m_Mask = "";
    this->m_MaxChars = 20;
    this->m_bIsActive = false;
    this->m_Properties = TextBoxProperties();
}

void TextBox::Draw() {

    DrawRectangleV(this->m_Pos, this->m_Size, this->m_Properties.Style.Colors.BorderColor);
    DrawRectangleV(SumVector2(this->m_Pos, Vector2(this->m_Properties.Options.BorderSize, this->m_Properties.Options.BorderSize)), SubVector2(this->m_Size, Vector2(2 * this->m_Properties.Options.BorderSize, 2 * this->m_Properties.Options.BorderSize)), this->m_Properties.Style.Colors.BgColor);

    bool Cond = this->m_Text.length() > 0;
    
    // ugly way of getting str of max len that fits in textbox
    int32_t l = 0, r = this->m_Text.length(), s=0;
    while (l <= r) {
        int32_t m = l + (r - l) / 2;
        auto x = MeasureTextEx(this->m_Properties.Style.Font.Font, this->m_Text.substr(m, this->m_Text.length() - m + 1).c_str(), this->m_Properties.Style.Font.Size, this->m_Properties.Style.Font.Spacing);
        if (x.x <= this->m_Size.x - 5) {
            r = m - 1;
            s = m;
        }
        else {
            l = m + 1;
        }
    }

    this->m_ShowText = Cond ? GetPasswordText().substr(s) : this->m_PlaceholderText.substr(s);

    //DrawTextEx(this->m_Properties.Style.Font.Font, Cond ? TextFormat("%s", GetPasswordText().c_str()) : this->m_PlaceholderText.c_str(), Vector2(this->m_Pos.x + 5, this->m_Pos.y + 5), 20.f, 1.f, Cond ? this->m_Properties.Style.Colors.FgColor : this->m_Properties.Style.Colors.PlaceholderColor);
    DrawTextEx(this->m_Properties.Style.Font.Font, Cond ? TextFormat("%s", GetPasswordText().substr(s).c_str()) : this->m_PlaceholderText.substr(s).c_str(), Vector2(this->m_Pos.x + 5, this->m_Pos.y + 5), this->m_Properties.Style.Font.Size, this->m_Properties.Style.Font.Spacing, Cond ? this->m_Properties.Style.Colors.FgColor : this->m_Properties.Style.Colors.PlaceholderColor);

    if (this->m_bIsActive) {
        this->DrawLineCursor();
    }
}

void TextBox::Update() {
    // Check for keyboard input
    if (this->IsClicked()) {
        this->m_bIsActive = !this->m_bIsActive;
    }
    if (this->m_bIsActive) {
        int32_t chr = GetCharPressed();
        int32_t key = GetKeyPressed();
        if (key) {
            // Check for ESC or ENTER
            if (key == KEY_ESCAPE or key == KEY_ENTER or key == KEY_KP_ENTER) {
                this->m_bIsActive = false;
            }

            // Check if mouse click outside boudaries
            if (this->IsClickedOutsideBoundaries()) {
                this->m_bIsActive = false;
            }

            // Check for backspace
            if (key == KEY_BACKSPACE && this->m_Text.length() >= 1) {
                this->m_Text.pop_back();
            }
            // Check for max characters
            else if (this->m_Text.length() <= (m_MaxChars != 0 ? m_MaxChars : this->m_Text.length() + 1) and chr >= 32 and chr <= 126) {
                this->m_Text += (char)chr;
                std::cout << this->m_Text << " \n";
            }
            
        }
    }
}

std::string TextBox::GetPasswordText() const {
    if (this->m_Mask == "") {
        return this->m_Text;
    }
    return std::string(this->m_Text.length(), this->m_Mask[0]);
}

Rectangle TextBox::GetTextBoxRectangle() const {
    return Rectangle(this->m_Pos.x, this->m_Pos.y, this->m_Pos.x + this->m_Size.x, this->m_Pos.y + this->m_Size.y);
}

bool TextBox::IsHovered() const {
    Vector2 mousePos = GetMousePosition();
    mousePos = Vector2(mousePos.x - this->m_MouseOffset.x, mousePos.y - this->m_MouseOffset.y);

    if (CheckCollisionPointRec(mousePos, this->GetTextBoxRectangle())) {
        return true;
    }
    return false;
}

bool TextBox::IsClicked() const {
    if (this->IsHovered() and IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        return true;
    }
    return false;
}

Color TextBox::InvertColor(Color Col) const {
    return Color(255 - Col.r, 255 - Col.g, 255 - Col.b, 255);
}

void TextBox::DrawLineCursor() const {
    uint32_t Time = uint32_t(GetTime() * 1000);
    if (Time % (this->m_Properties.Options.CursorBlinkHideTimeMilli + this->m_Properties.Options.CursorBlinkShowTimeMilli) <= this->m_Properties.Options.CursorBlinkShowTimeMilli) {
        Vector2 TextSize = this->m_Text.length() > 0 ? MeasureTextEx(this->m_Properties.Style.Font.Font, this->m_ShowText.c_str(), this->m_Properties.Style.Font.Size, this->m_Properties.Style.Font.Spacing) : MeasureTextEx(this->m_Properties.Style.Font.Font, this->m_Text.c_str(), this->m_Properties.Style.Font.Size, this->m_Properties.Style.Font.Spacing);
        DrawRectangleV(Vector2(this->m_Pos.x + TextSize.x + 5, this->m_Pos.y + (this->m_Size.y - TextSize.y) / 2), Vector2(4, TextSize.y), InvertColor(this->m_Properties.Style.Colors.BgColor));
    }
    else {

    }
}

bool TextBox::IsClickedOutsideBoundaries() const {
    if (this->IsHovered() == false and IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        std::cout << "YES";
        return true;
    }
    return false;
}

std::string TextBox::GetText() const {
    return this->m_Text;
}

Vector2 TextBox::GetMouseOffset() const {
    return this->m_MouseOffset;
}

void TextBox::SetMouseOffset(Vector2 MouseOffset) {
    this->m_MouseOffset = MouseOffset;
}