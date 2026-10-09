#include "include/directory_view.hpp"
#include "include/layout.hpp"

int main(){
    ApplicationWindow window{1200, 800, "Image Browser"};
    DirectoryView directoryView;

    const DirectoryContents rootContents = readDirectory("images");

    while(!window.shouldClose()){
        const AppLayout layout = calculateLayout();

        beginFrame();

        drawLayout(layout);
        directoryView.draw(layout.sidebar, rootContents);

        endFrame();
    }

    return 0;
}