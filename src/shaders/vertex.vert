#version 450

layout(binding = 0) uniform UniformBufferObject
{
    mat4 ModelMatrix;
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
} UBO;

layout(location = 0) in vec2 InPosition;
layout(location = 1) in vec3 InColor;

layout(location = 0) out vec3 OutFragmentColor;

void main()
{
    gl_Position = UBO.ProjectionMatrix * UBO.ViewMatrix * UBO.ModelMatrix * vec4(InPosition, 0.0, 1.0);
    OutFragmentColor = InColor;
}

