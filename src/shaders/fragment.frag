#version 450

layout(location = 0) out vec4 OutputFragmentColor;

layout(location = 0) in vec3 InFragmentColor;

void main()
{
    OutputFragmentColor = vec4(InFragmentColor, 1.0);
}