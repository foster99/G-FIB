#version 330 core
in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

uniform int nstripes = 16;
uniform vec2 origin = vec2(0,0);

void main()
{
    int d = int(length(vtexCoord - origin) * nstripes);
    if (d%2 == 0) fragColor = vec4(1,0,0,1);
    else fragColor = vec4(1,1,0,1);
}
