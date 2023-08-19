#pragma once
#include "ChildWindow.h"
#include "TextureButton.h"
#include "Textbox.h"
#include "Resources.h"
#include "Stats.h"

extern Resources::ResourcePack ResPack;
extern Resources::Resources ResourceLoader;

class SaveChildWindow : public ChildWindow {
public:
    //explicit SaveChildWindow();
    explicit SaveChildWindow();

protected:
    void DrawContents() override;
private:
    std::unique_ptr<TextureButton> m_CloseButton;
    std::unique_ptr<Button> m_SaveButton;
    TextBox m_TextBox;
    std::shared_ptr<Stats> m_Statistics;

};