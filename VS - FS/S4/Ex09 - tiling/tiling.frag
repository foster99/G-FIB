#version 330 core

out vec4 fragColor;

in vec2 vtexCoord;
uniform sampler2D colorMap;

void main()
{
    fragColor = texture(colorMap, vtexCoord);
}
