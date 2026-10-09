#include "layout.hpp"

namespace{
    constexpr float TITLE_HEIGHT_PERCENT = 0.10f;
    constexpr float SIDEBAR_WIDTH_PERCENT = 0.20f;
    constexpr int TARGET_FPS = 60;
}

ApplicationWindow::ApplicationWindow(int width, int height, const char* title){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, title);
    SetTargetFPS(TARGET_FPS);
}

ApplicationWindow::~ApplicationWindow(){
    CloseWindow();
}

bool ApplicationWindow::shouldClose() const{
    return WindowShouldClose();
}

AppLayout calculateLayout(){
    const float screenWidth = static_cast<float>(GetScreenWidth());
    const float screenHeight = static_cast<float>(GetScreenHeight());

    const float titleHeight = screenHeight * TITLE_HEIGHT_PERCENT;
    const float sidebarWidth = screenWidth * SIDEBAR_WIDTH_PERCENT;

    return {
        .titleBar = {0.0f, 0.0f, screenWidth, titleHeight},
        .sidebar = {0.0f, titleHeight, sidebarWidth, screenHeight - titleHeight},
        .content = {sidebarWidth, titleHeight, screenWidth - sidebarWidth,screenHeight - titleHeight}
    };
}

void drawLayout(const AppLayout& layout){
    DrawRectangleRec(layout.titleBar, DARKGRAY);
    DrawRectangleRec(layout.sidebar, LIGHTGRAY);
    DrawRectangleRec(layout.content, RAYWHITE);

    DrawRectangleLinesEx(layout.titleBar, 1.0f, BLACK);
    DrawRectangleLinesEx(layout.sidebar, 1.0f, BLACK);
    DrawRectangleLinesEx(layout.content, 1.0f, BLACK);
}

void beginFrame(){
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

void endFrame(){
    EndDrawing();
}