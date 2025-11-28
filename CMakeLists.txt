# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название твоего проекта
project(Gh0stEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- 1. Подключаем Vulkan ---
find_package(Vulkan REQUIRED)

# --- 2. Подключаем SDL3 ---
# Убедись, что этот путь правильный на ТВОЕМ компьютере!
set(SDL3_DIR "C:/dev/libs/SDL3-3.2.24/cmake") 
find_package(SDL3 REQUIRED)

# --- 3. Собираем наш исполняемый файл ---
# ✅ ИСПРАВЛЕНИЕ 1: Мы добавили сюда src/graphics/VulkanRenderer.cpp
# Без этого VS Code не видит этот файл и подчеркивает всё красным.
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/core/Window.cpp
    src/graphics/VulkanRenderer.cpp
)

# --- 3.5 Фикс для main ---
target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_MAIN_HANDLED)

# --- 4. Подключаем папки с заголовками (.h) ---
# Здесь всё было верно, оставляем как есть
target_include_directories(${PROJECT_NAME} PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/src" # Добавил корень src, чтобы писать <core/Window.h>
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/graphics"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/scene"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ui"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends"
    ${Vulkan_INCLUDE_DIRS}
    ${SDL3_INCLUDE_DIRS}
)

# --- 5. Линкуем библиотеки ---
target_link_libraries(${PROJECT_NAME} PUBLIC
    Vulkan::Vulkan
    SDL3::SDL3
)

# --- 6. Подключаем ImGui ---
target_sources(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_sdl3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_vulkan.cpp"
)

# ✅ ИСПРАВЛЕНИЕ 2: Убрал двойные кавычки в пути (""D:/...""), 
# CMake из-за них мог ругаться при копировании.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "D:/College/MyBlocks/GraphicEngine/SDL3.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)