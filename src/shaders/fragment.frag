#version 450

layout(location = 0) out vec4 OutputFragmentColor;

layout(location = 0) in vec3 FragmentColor;

void main()
{
    OutputFragmentColor = vec4(FragmentColor, 1.0);
}