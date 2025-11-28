#include "Window.h"
#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h" 

Window::Window(const std::string& title, int width, int height) 
    : m_width(width), m_height(height) {
    
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return;
    }

    m_window = SDL_CreateWindow(
        title.c_str(),
        width,
        height,
        SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE
    );

    if (!m_window) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    std::cout << "Window created successfully!" << std::endl;
}

Window::~Window() {
    if (m_window) {
        SDL_DestroyWindow(m_window);
    }
    SDL_Quit();
    std::cout << "Window cleaned up." << std::endl;
}

void Window::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        
        ImGui_ImplSDL3_ProcessEvent(&event);

        if (event.type == SDL_EVENT_QUIT) {
            m_shouldClose = true;
        }
        else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
            m_wasResized = true;
            m_width = event.window.data1;
            m_height = event.window.data2;
        }
    }
}