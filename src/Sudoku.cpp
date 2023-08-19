#include <iostream>
#include <fstream>

#include <raylib.h>
#include <raymath.h>

#include <imgui.h>
#include <rlImGui.h>

#include <GLFW/glfw3.h>

#include <string>
#include <sstream>
#include <random>
#include <vector>
#include <map>
#include <any>

#include "SudokuGenerator.h"
#include "Tile.h"
#include "Board.h"
#include "UI.h"
#include "MainMenu.h"
#include "Resources.h"

#include "Stats.h"
#include "MultiLineTextBox.cpp"


Resources::Resources ResourceLoader;
Resources::ResourcePack ResPack;


int main()
{
    //stats.AddData(reinterpret_cast<char*>(arr), sizeof(arr));

    InitWindow(512, 512, "Sudoku - iSound");
    SetWindowPosition(GetWindowPosition().x, 32);
    SetExitKey(NULL);
    
    SetTargetFPS(144);
    rlImGuiSetup(true);

    SudokuGenerator* sudoku = new SudokuGenerator;
    sudoku->Generate();


    ResourceLoader.Load("Default");
    ResPack = ResourceLoader.Get();

    Font sudoku_font = LoadFontEx(ResPack.Fonts["ubuntu-bold.ttf"].c_str(), 48.0f, NULL, 0);

    //Board* board = new Board(sudoku, sudoku_font);
    Board* board = new Board(sudoku, sudoku_font);
    board->SetOffset(Vector2(30.f,30.f));
    board->RefreshResources();
    
    SetWindowSize(board->GetSize().x + board->GetOffset().x + ResPack.Textures["heart_full.png"].width + board->GetOffset().x, board->GetSize().y + board->GetOffset().y);
    
    UI* ui = new UI(board);
    
    ButtonProperties::ButtonStyle buttonStyle;
    buttonStyle.Alignment = ButtonProperties::ButtonAlignment::CENTER;
    buttonStyle.Colors.BgColor = Color(150, 207, 239, 255);
    buttonStyle.Colors.BorderColor = Color(0, 105, 181, 255);
    buttonStyle.BorderWidth = 4;
    buttonStyle.Font.Size = 32.0f;
    buttonStyle.Font.Spacing = 0.0f;
    buttonStyle.Font.Font = LoadFontEx(ResPack.Fonts["ubuntu-bold.ttf"].c_str(), buttonStyle.Font.Size, NULL, buttonStyle.Font.Spacing);

    MainMenu mainMenu = MainMenu(buttonStyle);
    MultiLineTextBox mltextbox(10,10, 500,500, 20, 200);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(Color(50, 50, 50, 50));

        mltextbox.Update();
        mltextbox.Draw();
        continue;
        mainMenu.Tick();
        if (!mainMenu.ShouldBeDrawn()) {
            board->Draw();
        }

        DrawText(std::to_string(GetFPS()).c_str(), 10, 10, 32, Color(255, 0, 0, 255));
        
        //board->Draw();
        ui->Tick();
        ui->Render();

        EndDrawing();
    }

    rlImGuiShutdown();
    
    CloseWindow();
}

int WinMain() {
    main();
}