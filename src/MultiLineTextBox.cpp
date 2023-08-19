#include "MultiLineTextBox.h"

class MultiLineTextBox {
public:
    MultiLineTextBox(int posX, int posY, int width, int height, int fontSize, int maxLines)
        : positionX(posX), positionY(posY), boxWidth(width), boxHeight(height),
        textFontSize(fontSize), maxVisibleLines(maxLines), cursorPos(0),
        selectionStart(-1), scrollOffsetX(0), scrollOffsetY(0), cursorBlinkTime(0),
        cursorVisible(true), clipboard(""), font({}), texture({}) {
        font = GetFontDefault();
        texture = LoadRenderTexture(boxWidth, boxHeight);
        UpdateRenderTexture();
    }

    void Update() {
        // Update cursor blink
        if (GetTime() >= cursorBlinkTime + cursorBlinkDelay) {
            cursorBlinkTime = GetTime();
            cursorVisible = !cursorVisible;
            UpdateRenderTexture();
        }

        // Handle cursor movement and text selection
        HandleInput();
    }

    void Draw() {
        // Draw the text box
        //DrawRenderTexture(texture, positionX, positionY, WHITE);
        DrawTextureRec(texture.texture, Rectangle(positionX, positionY, boxWidth, -boxHeight), Vector2(positionX, positionY), Raylib::RAYWHITE);
        

        // Draw the cursor
        if (cursorVisible && IsWindowFocused()) {
            int cursorX = positionX + GetCursorX();
            int cursorY = positionY + GetCursorY();
            DrawRectangle(cursorX, cursorY, 2, textFontSize + 2, BLACK);
        }
    }

private:
    static const int lineSpacing = 4;
    static const int cursorBlinkDelay = 500; // milliseconds

    int positionX;
    int positionY;
    int boxWidth;
    int boxHeight;
    int textFontSize;
    int maxVisibleLines;
    int cursorPos;
    int selectionStart;
    int scrollOffsetX;
    int scrollOffsetY;
    double cursorBlinkTime;
    bool cursorVisible;
    std::vector<std::string> text;
    std::string clipboard;
    Font font;
    RenderTexture2D texture;

    void HandleInput() {
        // Handle cursor movement and text selection
        if (IsKeyPressed(KEY_RIGHT)) {
            MoveCursorRight();
        }
        else if (IsKeyPressed(KEY_LEFT)) {
            MoveCursorLeft();
        }
        else if (IsKeyPressed(KEY_UP)) {
            MoveCursorUp();
        }
        else if (IsKeyPressed(KEY_DOWN)) {
            MoveCursorDown();
        }
        else if (IsKeyPressed(KEY_BACKSPACE)) {
            DeleteCharacter();
        }
        else if (IsKeyPressed(KEY_DELETE)) {
            DeleteCharacter(true);
        }
        else if (IsKeyPressed(KEY_ENTER)) {
            InsertNewline();
        }
        else if (IsKeyPressed(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C)) {
            CopySelection();
        }
        else if (IsKeyPressed(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_X)) {
            CutSelection();
        }
        else if (IsKeyPressed(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_V)) {
            PasteClipboard();
        }
        else if (IsKeyPressed(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_A)) {
            SelectAll();
        }

        // TODO: Handle other input events like text insertion

        // TODO: Handle scrolling if the text goes beyond the visible area
    }

    void MoveCursorRight() {
        if (cursorPos < static_cast<int>(text.size()) - 1) {
            cursorPos++;
        }
    }

    void MoveCursorLeft() {
        if (cursorPos > 0) {
            cursorPos--;
        }
    }

    void MoveCursorUp() {
        if (cursorPos > 0) {
            cursorPos--;
            if (GetCursorX() > static_cast<int>(text[cursorPos].size())) {
                cursorPos -= text[cursorPos].size();
            }
        }
    }

    void MoveCursorDown() {
        if (cursorPos < static_cast<int>(text.size()) - 1) {
            cursorPos++;
            if (GetCursorX() > static_cast<int>(text[cursorPos].size())) {
                cursorPos -= text[cursorPos].size();
            }
        }
    }

    void DeleteCharacter(bool forward = false) {
        if (selectionStart != -1) {
            DeleteSelectedText();
            return;
        }

        if (!text.empty() && (forward || cursorPos > 0)) {
            if (forward) {
                if (cursorPos < static_cast<int>(text.size()) - 1) {
                    text[cursorPos] = text[cursorPos].substr(0, GetCursorX()) + text[cursorPos + 1];
                    text.erase(text.begin() + cursorPos + 1);
                }
            }
            else {
                int cursorX = GetCursorX();
                int lineLength = static_cast<int>(text[cursorPos].size());
                if (cursorX > 0) {
                    text[cursorPos] = text[cursorPos].substr(0, cursorX - 1) + text[cursorPos].substr(cursorX, lineLength - cursorX);
                    cursorPos--;
                }
                else if (cursorPos > 0) {
                    cursorPos--;
                    cursorX = GetCursorX();
                    lineLength = static_cast<int>(text[cursorPos].size());
                    text[cursorPos] += text[cursorPos + 1];
                    text.erase(text.begin() + cursorPos + 1);
                    cursorX = lineLength;
                }
            }
            UpdateRenderTexture();
        }
    }

    void InsertNewline() {
        if (selectionStart != -1) {
            DeleteSelectedText();
        }

        text.insert(text.begin() + cursorPos + 1, text[cursorPos].substr(GetCursorX()));
        text[cursorPos] = text[cursorPos].substr(0, GetCursorX());
        cursorPos++;
        UpdateRenderTexture();
    }

    void CopySelection() {
        if (selectionStart != -1) {
            clipboard = GetSelectedText();
        }
    }

    void CutSelection() {
        if (selectionStart != -1) {
            clipboard = GetSelectedText();
            DeleteSelectedText();
        }
    }

    void PasteClipboard() {
        if (!clipboard.empty()) {
            DeleteSelectedText();
            text[cursorPos] = text[cursorPos].substr(0, GetCursorX()) + clipboard + text[cursorPos].substr(GetCursorX());
            cursorPos += static_cast<int>(clipboard.size());
            UpdateRenderTexture();
        }
    }

    void SelectAll() {
        selectionStart = 0;
        cursorPos = static_cast<int>(text.size()) - 1;
        UpdateRenderTexture();
    }

    void DeleteSelectedText() {
        if (selectionStart != -1) {
            int start = (selectionStart < cursorPos) ? selectionStart : cursorPos;
            int end = (selectionStart > cursorPos) ? selectionStart : cursorPos;
            int numLines = end - start + 1;
            text[start] = text[start].substr(0, GetCursorX()) + text[end].substr(GetCursorX());
            text.erase(text.begin() + start + 1, text.begin() + start + numLines);
            cursorPos = start;
            selectionStart = -1;
            UpdateRenderTexture();
        }
    }

    std::string GetSelectedText() const {
        if (selectionStart != -1) {
            int start = (selectionStart < cursorPos) ? selectionStart : cursorPos;
            int end = (selectionStart > cursorPos) ? selectionStart : cursorPos;
            std::string selectedText = text[start].substr(GetCursorX());
            for (int i = start + 1; i < end; i++) {
                selectedText += '\n' + text[i];
            }
            if (start != end) {
                selectedText += '\n' + text[end].substr(0, GetCursorX());
            }
            return selectedText;
        }
        return "";
    }

    int GetCursorX() const {
        int lineLength = static_cast<int>(text[cursorPos].size());
        return MeasureText(text[cursorPos].c_str(), textFontSize) + scrollOffsetX;
    }

    int GetCursorY() const {
        int lineY = 0;
        for (int i = 0; i < cursorPos; i++) {
            lineY += textFontSize + lineSpacing;
        }
        return lineY + scrollOffsetY;
    }

    void UpdateRenderTexture() {
        BeginTextureMode(texture);
        ClearBackground(BLANK);

        int lineY = 0;
        for (size_t i = 0; i < text.size(); i++) {
            if (lineY + textFontSize > boxHeight) {
                break;
            }
            DrawTextEx(font, text[i].c_str(), Vector2{ 0, static_cast<float>(lineY) },
                static_cast<float>(textFontSize), 1.0f, BLACK);
            lineY += textFontSize + lineSpacing;
        }

        if (cursorVisible && IsWindowFocused()) {
            int cursorX = GetCursorX();
            int cursorY = GetCursorY();
            DrawRectangle(cursorX, cursorY, 2, textFontSize + 2, BLACK);
        }

        EndTextureMode();
    }
};
