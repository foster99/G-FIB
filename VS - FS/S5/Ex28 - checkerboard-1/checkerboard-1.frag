#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;

out vec4 fragColor;


void main()
{   
    vec4 black = vec4(0);
    vec4 grey = vec4(.8);
    
    bool xImpar = mod(floor(vtexCoord.x * 8),2) == 1;
    bool yImpar = mod(floor(vtexCoord.y * 8),2) == 1;
    
    if (xImpar ^^ yImpar) fragColor = black;
    else fragColor = grey;
}
