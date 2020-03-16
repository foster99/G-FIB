#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;

out vec4 fragColor;

uniform float n = 8;

void main()
{   
    vec4 black = vec4(0);
    vec4 grey = vec4(.8);
    
    bool rayax = abs(fract(vtexCoord.x * n)) <= 1./9.;
    bool rayay = abs(fract(vtexCoord.y * n)) <= 1./9.;
    
    if (rayax || rayay) fragColor = black;
    else fragColor = grey;
}
