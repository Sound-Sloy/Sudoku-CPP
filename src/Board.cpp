#include "Board.h"


Board::Board(SudokuGenerator* Sudoku, Font font) {
    this->m_Tiles.resize(81);
    this->m_CorrectValues.resize(81);
    this->m_CorrectValues = Sudoku->GetFullBoard();
    for (int32_t i = 0; i < 81; ++i) {
        this->m_Tiles[i].SetCorrectValue(this->m_CorrectValues[i]);
        this->m_Tiles[i].SetFont(font);
        this->m_Tiles[i].SetID(i);
        if (Sudoku->GetCell(i) != 0) {
            this->m_Tiles[i].SetText(std::to_string(Sudoku->GetCell(i)).c_str());
            this->m_Tiles[i].SetTextLock(true);
        }
    }
    
    this->m_SaveWindow = std::make_unique<SaveChildWindow>(std::make_shared<Stats>(this->Statistics));

    int8_t CurrMaxLives = static_cast<int8_t>(this->m_MaxLives);
    this->Statistics.AddData(reinterpret_cast<char*>(&CurrMaxLives), sizeof(CurrMaxLives), false, Statistics.C_MAXLIVESPOS);

    //auto CorrVals = this->m_CorrectValues.data();
    std::vector<int8_t> VCorrVals;
    for (auto data : this->m_CorrectValues) {
        VCorrVals.push_back(~(int8_t)data);
    }
    auto CorrVals = VCorrVals.data();
    this->Statistics.AddData(reinterpret_cast<char*>(CorrVals), VCorrVals.size() * sizeof(VCorrVals.front()), false, Statistics.C_CORRECTVALUESPOS);
    //delete[] CorrVals;
}

void Board::SetOffset(Vector2 offset) {
    this->m_Offset = offset;
}

Vector2 Board::GetOffset() { 
    return this->m_Offset; 
}

Vector2 Board::GetSize() { 
    return Vector2(this->m_Tiles[8].GetPos().x + this->m_Tiles[8].GetSize().x, this->m_Tiles[80].GetPos().y + this->m_Tiles[80].GetSize().y); 
}

//std::map<std::string, Texture2D> Board::GetTextures() {
//    return this->m_Textures;
//}

void Board::RefreshResources() {
    for (auto& tile : this->m_Tiles) {
        tile.SetSize(Vector2(static_cast<float>(ResPack.Textures["cell_normal.png"].width), static_cast<float>(ResPack.Textures["cell_normal.png"].height)));

        tile.SetPos(
            Vector2(tile.GetID() % 9 * tile.GetSize().x + tile.GetID() % 9 * this->m_OffsetTile.x + tile.GetID() % 9 / 3 * this->m_OffsetTileGroup.x + this->m_Offset.x,
                    tile.GetID() / 9 * tile.GetSize().y + tile.GetID() / 9 * this->m_OffsetTile.y + tile.GetID() / 9 / 3 * this->m_OffsetTileGroup.y + this->m_Offset.y)
        );
    }
}

void Board::DrawHearts() {
    for (int32_t i = 1; i <= this->m_MaxLives; ++i) {
        Texture2D texture = i <= m_Lives ? ResPack.Textures["heart_full.png"] : ResPack.Textures["heart_empty.png"];
        DrawTextureV(texture, Vector2(this->m_Tiles[8].GetPos().x + this->m_Tiles[8].GetSize().x + this->GetOffset().x, this->m_Tiles[8].GetPos().y + i*(texture.height + this->GetOffset().y/2)), Color(255, 255, 255, 255));
    }
}

void Board::DrawTileTextures() {
    for (auto& tile : this->m_Tiles)
        tile.Draw();
}

void Board::DrawSaveIcon() {
    Texture2D texture = ResPack.Textures["save_icon.png"];
    DrawTextureV(texture, Vector2(this->m_Tiles[8].GetPos().x + this->m_Tiles[8].GetSize().x + this->GetOffset().x, this->m_Tiles[80].GetPos().y + (this->m_Tiles[80].GetSize().y - texture.height) / 2), Color(255,255,255,255));
}

std::vector<int32_t> Board::GetValues() {
    std::vector<int32_t> R;
    for (auto& tile : this->m_Tiles) {
        R.push_back(std::atoi(tile.GetText().c_str()));
    }
    return R;
}

std::vector<int32_t> Board::GetCorrectValues() {
    std::vector<int32_t> R;
    for (auto& tile : this->m_Tiles) {
        R.push_back(tile.GetCorrectValue());
    }
    return R;
}

void Board::Draw() {
    if (ResourceLoader.ShouldReload()) {
        this->RefreshResources();
        ResourceLoader.Set_bRecentlyLoaded_to_False();
    }
    this->DrawHearts();
    this->DrawTileTextures();
    //this->DrawSaveIcon();
    TextureButtonProperties::TextureButtonStyle SaveButtStyle;
    SaveButtStyle.Alignment = TextureButtonProperties::TextureButtonAlignment::CENTER;
    this->m_SaveButton = std::make_unique<TextureButton>(ResPack.Textures["save_icon.png"], "", Vector2(this->m_Tiles[80].GetPos().x + this->m_Tiles[80].GetSize().x + this->m_Offset.x, this->m_Tiles[80].GetPos().y + (this->m_Tiles[80].GetSize().y - ResPack.Textures["save_icon.png"].height) / 2), Vector2(0,0), SaveButtStyle);
    this->m_SaveButton->Draw();
    
    if (this->m_SaveButton->IsClicked() and !this->m_SaveWindow->IsClosed()) {
        this->m_SaveWindow->Close();
        return;
    }

    if (this->m_SaveButton->IsClicked() and this->m_SaveWindow->IsClosed()) {
        std::cout << "Save Clicked\n";
        this->m_SaveWindow = std::make_unique_for_overwrite<SaveChildWindow>();
        this->m_SaveWindow->Show();
        //this->m_SaveWindow->Render();
    }

    if (!this->m_SaveWindow->IsClosed()) {
        this->m_SaveWindow->Draw();
        return;
    }

    if (!ImGui::GetIO().WantCaptureMouseUnlessPopupClose) {
        static std::string ToHighlight = "";
        for (auto& tile : this->m_Tiles) {
            if (tile.IsHovered()) {
                DrawTextureV(ResPack.Textures["cell_focused.png"], tile.GetPos(), Color(255, 255, 255, 100));
            }
            if (tile.IsClicked()) {
                if (tile.IsFocused()) {
                    tile.SetFocused(false);
                }
                else {
                    for (auto& tile2 : this->m_Tiles) {
                        tile2.SetFocused(false);
                    }
                    tile.SetFocused(true);
                }
            }

            //Highlight similar tiles
            if (tile.IsFocused()) {
                ToHighlight = tile.GetText();
            }
            if (tile.GetText() == ToHighlight and tile.GetText() != "") {
                DrawTextureV(ResPack.Textures["cell_focused.png"], tile.GetPos(), Color(255, 255, 255, 100));
            }
            //END

            if (tile.IsFocused() and !tile.IsTextLocked()) {
                int32_t key = GetKeyPressed();
                tile.SetTextColor(Color(100, 100, 100, 255));
                if (key == KEY_KP_0 or key == KEY_ZERO) {
                    tile.SetText("");
                }
                else {
                    bool cond_1 = (KEY_KP_0 < key and key <= KEY_KP_9);
                    bool cond_2 = (KEY_ZERO < key and key <= KEY_NINE);
                    if (cond_1 or cond_2) {
                        cond_1 == true ? key = key : key = key + KEY_KP_0 - KEY_ZERO;
                        if (key-KEY_KP_0 != std::atoi(tile.GetText().c_str())) {
                            if (key != KEY_KP_0 and key != KEY_ZERO) {
                                tile.SetText(std::to_string(key - KEY_KP_0).c_str());
                                if (std::atoi(tile.GetText().c_str()) != tile.GetCorrectValue()) {
                                    this->m_Lives = this->m_Lives > 0 ? this->m_Lives - 1 : 0;
                                }
                            }
                            else tile.SetText("");

                            // TODO: Add here game preview (save move to file with gameID + HASH_SHA256) [See save-schem.txt from ./]

                            uint64_t MoveTime = Statistics.GetMilliSinceInit();
                            Statistics.AddData(reinterpret_cast<char*>(&MoveTime), sizeof(MoveTime), false);
                            std::cout << MoveTime << std::endl;

                            int8_t CurrLives = static_cast<int8_t>(this->m_Lives);
                            Statistics.AddData(reinterpret_cast<char*>(&CurrLives), sizeof(CurrLives), false);

                            std::vector<int8_t> Vals;
                            for (auto val : this->GetValues()) {
                                Vals.push_back(~static_cast<int8_t>(val));
                            }

                            Statistics.AddData(reinterpret_cast<char*>(Vals.data()), Vals.size() * sizeof(Vals.front()), true);
                        }

                    }
                }
                int32_t current_value = std::atoi(tile.GetText().c_str());
                if (current_value == tile.GetCorrectValue()) {
                    tile.SetTextColor(Color(100, 100, 100, 255));
                }
                else {
                    tile.SetTextColor(Color(150, 0, 0, 255));
                }
            }
        }
    }
}

void Board::CallSave(std::string SaveName) {
    this->Statistics.Save(SaveName);
}