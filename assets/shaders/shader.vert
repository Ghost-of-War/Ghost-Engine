#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

// Глобальные данные (Камера не меняется для каждого объекта)
layout(binding = 0) uniform CameraData {
    mat4 view;
    mat4 proj;
} camera;

// Данные ОБЪЕКТА (Меняются для каждого вызова draw)
layout(push_constant) uniform PushConsts {
    mat4 model;
} push;

layout(location = 0) out vec3 fragColor;

void main() {
    // P * V * M * Pos
    gl_Position = camera.proj * camera.view * push.model * vec4(inPosition, 1.0);
    fragColor = inColor;
}