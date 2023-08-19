#pragma once
#include <iostream>
#include <string>
#include <raylib.h>
#include "Utils.h"
#include "Button.h"

class ChildWindow {
public:
    explicit ChildWindow(const std::string& Title, const Vector2& Pos, const Vector2& Size);

    virtual ~ChildWindow();

    // Set the window's position and size
    void SetPos(const Vector2& Pos);
    void SetSize(const Vector2& Size);

    // Get the window's position and size
    Vector2 GetPos() const;
    Vector2 GetSize() const;

    // Draw the window, including the contents of the derived class
    virtual void Draw();

    // Handle mouse input for the window
    void HandleInput();

    // Close the window
    void Close();

    // Open the window
    void Show();

    // Maximize the window
    void Maximize();

    // Check if the window is closed
    bool IsClosed() const;

protected:
    // Draw the contents of the derived class
    virtual void DrawContents();

private:
    std::string m_Title = "ChildWindow";
    //Rectangle m_Rect = Rectangle(10, 10, 200, 200);
    Vector2 m_Pos = Vector2(0.f, 0.f);
    Vector2 m_Size = Vector2(200.f, 200.f);
    Vector2 m_TitleBarSize = Vector2(0.f, 20.f);
    bool m_bIsMaximized = false;
    bool m_bIsResizing = false;
    bool m_bIsDragging = false;
    Vector2 m_DragOffset = Vector2(0.f, 0.f);
    //Rectangle m_CloseButton = Rectangle(0, 0, 0, 0);
    Rectangle m_MaximizeButton = Rectangle(0, 0, 0, 0);
    //Rectangle m_LastRect = Rectangle(10, 10, 200, 200);
    Vector2 m_LastPos = Vector2(0.f, 0.f);
    bool m_bIsClosed = true;
    RenderTexture2D m_WindowTexture;
};
