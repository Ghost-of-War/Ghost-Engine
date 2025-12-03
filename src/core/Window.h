#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <iostream>

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    void pollEvents();
    
    bool shouldClose() const { return m_shouldClose; }
    bool wasResized() const { return m_wasResized; }
    void resetResizeFlag() { m_wasResized = false; }

    SDL_Window* getNativeWindow() const { return m_window; }

private:
    SDL_Window* m_window = nullptr;
    bool m_shouldClose = false;
    bool m_wasResized = false;
    
    int m_width;
    int m_height;
};