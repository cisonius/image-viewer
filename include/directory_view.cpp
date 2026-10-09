#include "directory_view.hpp"

#include <algorithm>
#include <cmath>
#include <string>

namespace{
    constexpr int DIRECTORY_FONT_SIZE = 25;
    constexpr float DIRECTORY_LINE_HEIGHT = 30.0f;

    constexpr float SIDEBAR_PADDING_PERCENT = 0.05f;
    constexpr float SECTION_GAP_PERCENT = 0.50f;

    constexpr const char* DIRECTORY_FONT_PATH = "include/NotoSans-Bold.ttf";
}

DirectoryView::DirectoryView(){
    font_ = LoadFontEx(DIRECTORY_FONT_PATH, DIRECTORY_FONT_SIZE, nullptr, 0);
    SetTextureFilter(font_.texture, TEXTURE_FILTER_BILINEAR);
}

DirectoryView::~DirectoryView(){
    UnloadFont(font_);
}

DirectoryContents readDirectory(const fs::path& directory){
    DirectoryContents contents;

    if(!fs::is_directory(directory)){
        return contents;
    }

    for(const fs::directory_entry& entry : fs::directory_iterator(directory)){
        if(entry.is_directory()){
            contents.folders.push_back(entry.path());
        }else if(entry.is_regular_file()){
            contents.files.push_back(entry.path());
        }
    }

    std::ranges::sort(contents.folders);
    std::ranges::sort(contents.files);

    return contents;
}

void DirectoryView::draw(const Rectangle& sidebar, const DirectoryContents& contents) const{
    const float padding = sidebar.width * SIDEBAR_PADDING_PERCENT;

    float currentY = sidebar.y + padding;

    for(const fs::path& folder : contents.folders){
        const std::string name = folder.filename().string();

        const Vector2 position{
            std::round(sidebar.x + padding),
            std::round(currentY)
        };

        DrawTextEx(font_, name.c_str(), position, DIRECTORY_FONT_SIZE, 1.0f, DARKBLUE);

        currentY += DIRECTORY_LINE_HEIGHT;
    }

    currentY += DIRECTORY_LINE_HEIGHT * SECTION_GAP_PERCENT;

    for(const fs::path& file : contents.files){
        const std::string name = file.filename().string();

        const Vector2 position{
            std::round(sidebar.x + padding),
            std::round(currentY)
        };

        DrawTextEx(font_, name.c_str(), position, DIRECTORY_FONT_SIZE, 1.0f, DARKGRAY);

        currentY += DIRECTORY_LINE_HEIGHT;
    }
}