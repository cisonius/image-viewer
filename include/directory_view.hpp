#pragma once

#include <filesystem>
#include <vector>

#include <raylib.h>

namespace fs = std::filesystem;

struct DirectoryContents{
    std::vector<fs::path> folders;
    std::vector<fs::path> files;
};

[[nodiscard]] DirectoryContents readDirectory(const fs::path& directory);

class DirectoryView{
    public:
        DirectoryView();
        ~DirectoryView();

        DirectoryView(const DirectoryView&) = delete;
        DirectoryView& operator=(const DirectoryView&) = delete;

        void draw(const Rectangle& sidebar, const DirectoryContents& contents) const;

    private:
        Font font_{};
};