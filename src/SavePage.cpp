#include "SavePage.h"

SaveChildWindow::SaveChildWindow()
    : ChildWindow("Save Game", Vector2((GetRenderWidth() - 400) / 2, (GetRenderHeight() - 400) / 2), Vector2(400.f, 400.f))
{
    TextureButtonProperties::TextureButtonStyle CloseButtStyle;
    CloseButtStyle.Alignment = TextureButtonProperties::TextureButtonAlignment::CENTER;
    CloseButtStyle.Colors.HighlightColor = Color(255, 150, 150, 50);
    this->m_CloseButton = std::make_unique<TextureButton>(ResPack.Textures["close.png"], "", Vector2(this->GetSize().x - 25, 5), Vector2(0, 0), CloseButtStyle);
    
    ButtonProperties::ButtonStyle SaveButtStyle;
    SaveButtStyle.Alignment = ButtonProperties::ButtonAlignment::CENTER;
    SaveButtStyle.Colors.HighlightColor = Color(255, 150, 150, 50);
    this->m_SaveButton = std::make_unique<Button>("Save", "", Vector2(this->GetPos().x+(this->GetSize().x-100)/2, this->GetPos().y+this->GetSize().y-100), Vector2(100.f, 30.f), SaveButtStyle);
    //Vector2 Pos, Vector2 Size, std::string PlaceholderText, std::string Mask, uint32_t MaxChars, TextBoxProperties Properties
    TextBoxProperties Properties;
    Properties.Style.Colors.FgColor = Color(150, 0, 150, 255);
    Properties.Style.Colors.BorderColor = Color(150, 0, 0, 255);
    Properties.Options.BorderSize = 2;
    Properties.Style.Font.Size = 20.f;
    Properties.Style.Font.Spacing = 1.f;
    Properties.Style.Font.Font = LoadFontEx(ResPack.Fonts["ubuntu-regular.ttf"].c_str(), Properties.Style.Font.Size, NULL, 0);
    this->m_TextBox = TextBox(Vector2(20.f,50.f), Vector2(300.f, 30.f), "Save Name", "", 32, Properties);
}

void SaveChildWindow::DrawContents() {
    this->m_CloseButton->SetMouseOffset(this->GetPos());
    this->m_SaveButton->Draw();
    this->m_TextBox.SetMouseOffset(this->GetPos());
    ClearBackground(Color(200, 255, 255, 255));
    //DrawText("Hello, world!", 10, 30, 20, DARKGRAY);
    this->m_CloseButton->Draw();
    this->m_TextBox.Update();
    this->m_TextBox.Draw();
    if (this->m_SaveButton->IsClicked()) {
        std::cout << "Saved" << std::endl;
        this->m_Statistics->Save(this->m_TextBox.GetText());
    }
}