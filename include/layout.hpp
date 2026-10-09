#pragma once

#include <raylib.h>

struct AppLayout{
    Rectangle titleBar;
    Rectangle sidebar;
    Rectangle content;
};

class ApplicationWindow{
    public:
        ApplicationWindow(int width, int height, const char* title);
        ~ApplicationWindow();

        ApplicationWindow(const ApplicationWindow&) = delete;
        ApplicationWindow& operator=(const ApplicationWindow&) = delete;

        [[nodiscard]] bool shouldClose() const;
};

[[nodiscard]] AppLayout calculateLayout();

void drawLayout(const AppLayout& layout);
void beginFrame();
void endFrame();