#include "ChildWindow.h"


ChildWindow::ChildWindow(const std::string& Title, const Vector2& Pos, const Vector2& Size)
    : m_Title(Title), m_Pos(Pos), m_Size(Size), m_bIsMaximized(false), m_bIsResizing(false),
    m_bIsDragging(false), m_MaximizeButton(Rectangle(0, 0, 0, 0))
{
    this->m_WindowTexture = LoadRenderTexture(static_cast<int32_t>(this->m_Size.x), static_cast<int32_t>(this->m_Size.y));
}

ChildWindow::~ChildWindow()
{
    UnloadRenderTexture(this->m_WindowTexture);
}

void ChildWindow::SetPos(const Vector2& Pos) {
    this->m_Pos = Pos;
}

void ChildWindow::SetSize(const Vector2& Size) {
    this->m_Size = Size;
}

// Get the window's position and size
Vector2 ChildWindow::GetPos() const {
    return this->m_Pos;
}

Vector2 ChildWindow::GetSize() const {
    return this->m_Size;
}

// Draw the window, including the contents of the derived class
void ChildWindow::Draw() {
    //DrawRectangleRec(this->m_Rect, LIGHTGRAY);
    if (this->IsClosed()) {
        return;
    }
    BeginTextureMode(this->m_WindowTexture);
    this->DrawContents();
    /*this->m_CloseButton.Draw();
    this->m_CloseButton.SetMouseOffset(this->m_Pos);*/
    DrawRectangleRec(this->m_MaximizeButton, SKYBLUE);
    DrawText(this->m_Title.c_str(), 5, 5, 20, DARKGRAY);
    EndTextureMode();
    DrawTextureRec(this->m_WindowTexture.texture, Rectangle(0, 0, this->m_Size.x, -this->m_Size.y), this->m_Pos, Color(255, 255, 255, 255));
    this->HandleInput();
}

void ChildWindow::HandleInput() {
    Vector2 MousePos = GetMousePosition();
    /*if (CheckCollisionPointRec(MousePos, m_CloseButton)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            this->Close();
        }
    }*/
    /*if (this->m_CloseButton.IsClicked()) {
        this->Close();
    }
    else if (CheckCollisionPointRec(MousePos, m_MaximizeButton)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            this->Maximize();
        }
    }
    else {*/
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(MousePos, Rectangle(this->m_Pos.x, this->m_Pos.y, this->m_Size.x, this->m_TitleBarSize.y))) {
                this->m_bIsDragging = true;
                this->m_DragOffset = Vector2(MousePos.x - this->m_Pos.x, MousePos.y - this->m_Pos.y);
            }
            else {
                this->m_bIsDragging = false;
            }
        }
        else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            this->m_bIsDragging = false;
            this->m_bIsResizing = false;
        }
        else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            if (this->m_bIsDragging) {
                this->m_Pos.x = MousePos.x - this->m_DragOffset.x;
                this->m_Pos.y = MousePos.y - this->m_DragOffset.y;
            }
            else if (this->m_bIsResizing) {
                this->m_Size.x = MousePos.x - this->m_Pos.x;
                this->m_Size.y = MousePos.y - this->m_Pos.y;
            }
        }
        else {
            if (CheckCollisionPointRec(MousePos, Rectangle(this->m_Pos.x + this->m_Size.x - 10, this->m_Pos.y + this->m_Size.y - 10, 10, 10))) {
                SetMouseCursor(MOUSE_CURSOR_RESIZE_NESW);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    this->m_bIsResizing = true;
                }
            }
            else {
                SetMouseCursor(MOUSE_CURSOR_ARROW);
                this->m_bIsResizing = false;
            }
        }
    //}
}

void ChildWindow::Close() {
    this->m_bIsClosed = true;
}

void ChildWindow::Show() {
    this->m_bIsClosed = false;
}

void ChildWindow::Maximize() {
    if (!this->m_bIsMaximized) {
        this->m_LastPos = this->m_Pos;
        this->m_Pos = Vector2(0.f, 0.f);
    }
    else {
        this->m_LastPos = this->m_Pos;
    }
    this->m_bIsMaximized = !this->m_bIsMaximized;
}

bool ChildWindow::IsClosed() const {
    return this->m_bIsClosed;
}

void ChildWindow::DrawContents() {

}