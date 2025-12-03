#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>
#include "../core/Window.h"
#include <optional>
#include <algorithm>
#include <fstream>
#include <Vertex.h>
#include <Mesh.h>
#include <GameObject.h>
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_vulkan.h"

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    
    bool isComplete() {
        return graphicsFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class VulkanRenderer {
public:
    VulkanRenderer(Window* window);
    ~VulkanRenderer();

    bool init(); 
    
    void cleanup();

    void drawFrame();
    void waitIdle();

private:
    // ImGui
    VkDescriptorPool m_imguiDescriptorPool;
    void initImGui();
    void renderGui(VkCommandBuffer commandBuffer);

    Window* m_window; 
    VkInstance m_instance;

    //surface
    VkSurfaceKHR m_surface;
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    VkDevice m_device;
    VkQueue m_graphicsQueue;  
    
    //Swapchain
    VkSwapchainKHR m_swapChain;
    std::vector<VkImage> m_swapChainImages;
    VkFormat m_swapChainImageFormat;
    VkExtent2D m_swapChainExtent;
    std::vector<VkImageView> m_swapChainImageViews;

    //Pipeline
    VkPipelineLayout m_pipelineLayout;
    VkRenderPass m_renderPass;
    VkPipeline m_graphicsPipeline;


    //Framebuffer
    std::vector<VkFramebuffer> m_swapChainFramebuffers;
    VkCommandPool m_commandPool;
    VkCommandBuffer m_commandBuffer;

    //Syncrinization
    VkSemaphore m_imageAvailableSemaphore;
    VkSemaphore m_renderFinishedSemaphore;
    VkFence m_inFlightFence;

    //vertex
    VkBuffer m_vertexBuffer;
    VkDeviceMemory m_vertexBufferMemory;
    std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f, -0.5f}, {0.9f, 0.6f, 0.1f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.9f, 0.6f, 0.1f}},
    {{ 0.5f,  0.5f, -0.5f}, {0.9f, 0.6f, 0.1f}},
    {{ 0.5f,  0.5f, -0.5f}, {0.9f, 0.6f, 0.1f}},
    {{-0.5f,  0.5f, -0.5f}, {0.9f, 0.6f, 0.1f}},
    {{-0.5f, -0.5f, -0.5f}, {0.9f, 0.6f, 0.1f}},

    {{-0.5f, -0.5f,  0.5f}, {0.1f, 0.6f, 0.9f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.1f, 0.6f, 0.9f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.1f, 0.6f, 0.9f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.1f, 0.6f, 0.9f}},
    {{-0.5f,  0.5f,  0.5f}, {0.1f, 0.6f, 0.9f}},
    {{-0.5f, -0.5f,  0.5f}, {0.1f, 0.6f, 0.9f}},

    {{-0.5f,  0.5f,  0.5f}, {0.1f, 0.9f, 0.1f}},
    {{-0.5f,  0.5f, -0.5f}, {0.1f, 0.9f, 0.1f}},
    {{-0.5f, -0.5f, -0.5f}, {0.1f, 0.9f, 0.1f}},
    {{-0.5f, -0.5f, -0.5f}, {0.1f, 0.9f, 0.1f}},
    {{-0.5f, -0.5f,  0.5f}, {0.1f, 0.9f, 0.1f}},
    {{-0.5f,  0.5f,  0.5f}, {0.1f, 0.9f, 0.1f}},

    {{ 0.5f,  0.5f,  0.5f}, {0.9f, 0.1f, 0.1f}},
    {{ 0.5f,  0.5f, -0.5f}, {0.9f, 0.1f, 0.1f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.9f, 0.1f, 0.1f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.9f, 0.1f, 0.1f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.9f, 0.1f, 0.1f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.9f, 0.1f, 0.1f}},

    {{-0.5f, -0.5f, -0.5f}, {0.5f, 0.1f, 0.9f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.5f, 0.1f, 0.9f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.5f, 0.1f, 0.9f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.5f, 0.1f, 0.9f}},
    {{-0.5f, -0.5f,  0.5f}, {0.5f, 0.1f, 0.9f}},
    {{-0.5f, -0.5f, -0.5f}, {0.5f, 0.1f, 0.9f}},

    {{-0.5f,  0.5f, -0.5f}, {0.9f, 0.9f, 0.1f}},
    {{ 0.5f,  0.5f, -0.5f}, {0.9f, 0.9f, 0.1f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.9f, 0.9f, 0.1f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.9f, 0.9f, 0.1f}},
    {{-0.5f,  0.5f,  0.5f}, {0.9f, 0.9f, 0.1f}},
    {{-0.5f,  0.5f, -0.5f}, {0.9f, 0.9f, 0.1f}}
};
    void* m_vertexBufferMapped = nullptr;

    std::vector<glm::vec3> m_uniqueVertices = {
        {-0.5f, -0.5f, -0.5f}, // 0: Back-Bottom-Left
        { 0.5f, -0.5f, -0.5f}, // 1: Back-Bottom-Right
        { 0.5f,  0.5f, -0.5f}, // 2: Back-Top-Right
        {-0.5f,  0.5f, -0.5f}, // 3: Back-Top-Left
        {-0.5f, -0.5f,  0.5f}, // 4: Front-Bottom-Left
        { 0.5f, -0.5f,  0.5f}, // 5: Front-Bottom-Right
        { 0.5f,  0.5f,  0.5f}, // 6: Front-Top-Right
        {-0.5f,  0.5f,  0.5f}  // 7: Front-Top-Left
    };

    const std::vector<uint16_t> m_indices = {
        0, 1, 2, 2, 3, 0, // Back
        4, 5, 6, 6, 7, 4, // Front
        7, 3, 0, 0, 4, 7, // Left
        1, 5, 6, 6, 2, 1, // Right
        0, 1, 5, 5, 4, 0, // Bottom
        3, 2, 6, 6, 7, 3  // Top
    };

    std::vector<Mesh> m_meshes;
    
    std::vector<GameObject> m_sceneObjects;

    Mesh loadMesh(const std::string& filename);

    //Rotate
    glm::vec3 m_rotation = {0.0f, 0.0f, 0.0f};
    bool m_autoRotate = true;

    //Camera and time
    glm::vec3 m_cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    float m_sensitivity = 0.1f;

    float m_deltaTime = 0.0f;
    float m_lastFrame = 0.0f;

    //DEPTH BUFFER
    VkImage m_depthImage;
    VkDeviceMemory m_depthImageMemory;
    VkImageView m_depthImageView;

    //Uniform Buffer (UBO)
    VkDescriptorSetLayout m_descriptorSetLayout;
    VkDescriptorPool m_descriptorPool;
    std::vector<VkDescriptorSet> m_descriptorSets;

    std::vector<VkBuffer> m_uniformBuffers;
    std::vector<VkDeviceMemory> m_uniformBuffersMemory;
    std::vector<void*> m_uniformBuffersMapped;


    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    #ifdef NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif

    bool createInstance();
    bool checkValidationLayerSupport();

    //surfaceм
    bool createSurface();
    bool pickPhysicalDevice();
    bool createLogicalDevice();

    //Swapchain
    void createSwapChain();
    void createImageViews();

    //Pipeline
    void createGraphicsPipeline();
    void createRenderPass();
    VkShaderModule createShaderModule(const std::vector<char>& code);

    //Framebuffer
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffer();

    //Syncrinization
    void createSyncObjects();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    //Vertex
    void createVertexBuffer();
    
    //Uniform Buffer (UBO)
    void createDescriptorSetLayout();
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    void updateUniformBuffer(uint32_t currentImage);

    //DEPTH BUFFER
    void createDepthResources();
    VkFormat findDepthFormat();
    
    //camera and time
    void processInput();

    void updateVerticesFromCorners();

    bool checkCollisionAABB(const glm::vec3& point, const glm::vec3& boxMin, const glm::vec3& boxMax, float radius);

    //helpers
    bool isDeviceSuitable(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    bool hasStencilComponent(VkFormat format);
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    static std::vector<char> readFile(const std::string& filename);
    bool checkCollision(const glm::vec3& point, const glm::vec3& min, const glm::vec3& max, float radius);
    void calculateBounds(glm::vec3& outMin, glm::vec3& outMax);
};