#version 450

layout(location = 0) in vec3 InFragmentColor;
layout(location = 1) in vec2 InFragmentTextureCoordinate;

layout(location = 0) out vec4 OutputFragmentColor;

layout(binding = 1) uniform sampler2D TextureSampler;

void main()
{
    OutputFragmentColor = texture(TextureSampler, InFragmentTextureCoordinate);
}