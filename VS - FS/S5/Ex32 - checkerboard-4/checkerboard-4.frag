#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;

out vec4 fragColor;

uniform float n = 8;

void main()
{   
    bool rayax = abs(fract(vtexCoord.x * n)) <= 1./9.;
    bool rayay = abs(fract(vtexCoord.y * n)) <= 1./9.;
    
    if (rayax || rayay) fragColor = vec4(1,0,0,1);
    else discard;
}
