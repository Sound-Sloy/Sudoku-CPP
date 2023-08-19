#pragma once
#include <raylib.h>
#include <string>
#include <map>
#include <fstream>
#include <imgui.h>
#include "SudokuGenerator.h"
#include "Tile.h"
#include "Resources.h"
#include "Stats.h"
#include "TextureButton.h"
#include "SavePage.h"

extern Resources::Resources ResourceLoader;
extern Resources::ResourcePack ResPack;

class Board {
private:
    Vector2 m_Offset = Vector2(30, 30);
    Vector2 m_OffsetTile = Vector2(2, 2);
    Vector2 m_OffsetTileGroup = Vector2(8, 8);
    std::vector<Tile> m_Tiles;
    //std::map<std::string, Texture2D> m_Textures;
    std::vector<int32_t> m_CorrectValues;
    int32_t m_MaxLives = 5;
    int32_t m_Lives = 5;
    std::unique_ptr<TextureButton> m_SaveButton;
    Stats Statistics;
    std::unique_ptr<SaveChildWindow> m_SaveWindow;


    std::vector<int32_t> GetValues();
    std::vector<int32_t> GetCorrectValues();
    void DrawHearts();
    void DrawTileTextures();
    void DrawSaveIcon();
public:
    Board(SudokuGenerator* Sudoku, Font font);
    void SetOffset(Vector2 offset);
    Vector2 GetOffset();
    Vector2 GetSize();
    //std::map<std::string, Texture2D> GetTextures();
    void RefreshResources();
    void Draw();
    void CallSave(std::string SaveName);
};