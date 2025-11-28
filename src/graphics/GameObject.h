#pragma once
#include <vulkan/vulkan.h>
#include <glm/glm.hpp> // Используем GLM для векторов
#include <array>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE // Важно для Вулкана!
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct GameObject {
    std::string name;
    Mesh* mesh;
    
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::mat4 getTransformMatrix() {
        glm::mat4 m = glm::mat4(1.0f);
        m = glm::translate(m, position);
        m = glm::rotate(m, glm::radians(rotation.x), {1,0,0});
        m = glm::rotate(m, glm::radians(rotation.y), {0,1,0});
        m = glm::rotate(m, glm::radians(rotation.z), {0,0,1});
        m = glm::scale(m, scale);
        return m;
    }
};