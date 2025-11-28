#include "core/Window.h"
#include "graphics/VulkanRenderer.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Window window("Gh0stEngine", 1280, 720);

    VulkanRenderer renderer(&window);
    if (!renderer.init()) {
        std::cerr << "Critical Error: Failed to initialize Vulkan Renderer" << std::endl;
        return -1;
    }

    while (!window.shouldClose()) {
        
        window.pollEvents();
        renderer.drawFrame();
    }
    renderer.waitIdle();

    return 0;
}