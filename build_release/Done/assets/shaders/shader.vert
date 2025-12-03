#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

// Глобальные данные (Камера) - остаются в UBO binding 0
layout(binding = 0) uniform CameraData {
    mat4 view;
    mat4 proj;
} camera;

// --- ВОТ ЭТО ГЛАВНОЕ ИЗМЕНЕНИЕ ---
// Данные ОБЪЕКТА (Позиция) - теперь через Push Constant
layout(push_constant) uniform PushConsts {
    mat4 model;
} push;
// ---------------------------------

layout(location = 0) out vec3 fragColor;

void main() {
    // Используем push.model вместо ubo.model
    gl_Position = camera.proj * camera.view * push.model * vec4(inPosition, 1.0);
    fragColor = inColor;
}