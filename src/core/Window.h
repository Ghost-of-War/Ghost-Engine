#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <iostream>

class Window {
public:
    // Конструктор сразу создает окно
    Window(const std::string& title, int width, int height);
    ~Window();

    // Запрещаем копирование окна (это важно для ресурсов)
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // Эта функция просто обновляет события (без бесконечного цикла)
    void pollEvents();
    
    bool shouldClose() const { return m_shouldClose; }
    bool wasResized() const { return m_wasResized; } // Понадобится для Вулкана
    void resetResizeFlag() { m_wasResized = false; }

    // Геттер для Вулкана (ему нужен сырой указатель)
    SDL_Window* getNativeWindow() const { return m_window; }

private:
    SDL_Window* m_window = nullptr;
    bool m_shouldClose = false;
    bool m_wasResized = false;
    
    int m_width;
    int m_height;
};