#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;

out vec4 fragColor;

uniform float n = 8;

void main()
{   
    vec4 black = vec4(0);
    vec4 grey = vec4(.8);
    
    bool xImpar = mod(floor(vtexCoord.x * n),2) == 1;
    bool yImpar = mod(floor(vtexCoord.y * n),2) == 1;
    
    if (xImpar ^^ yImpar) fragColor = black;
    else fragColor = grey;
}
