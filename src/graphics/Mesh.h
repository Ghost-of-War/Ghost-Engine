#pragma once
#include <vulkan/vulkan.h>
#include <glm/glm.hpp> // Используем GLM для векторов
#include <array>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE // Важно для Вулкана!
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Mesh {
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    uint32_t vertexCount;

    void destroy(VkDevice device) {
        vkDestroyBuffer(device, vertexBuffer, nullptr);
        vkFreeMemory(device, vertexBufferMemory, nullptr);
    }
};