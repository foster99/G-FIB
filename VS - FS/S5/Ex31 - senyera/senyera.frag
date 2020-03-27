#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

void main()
{
    float f = fract(vtexCoord.s), a = 1.0/9.0;
    
    bool groc =    (0 <= f && f < a)     
                || (2.0*a <= f && f < 3.0*a)
                || (4.0*a <= f && f < 5.0*a)
                || (6.0*a <= f && f <= 7.0*a)
                || (8.0*a <= f && f < 9.0*a);
    
    if (groc) fragColor = vec4(1,1,0,1);
    else fragColor = vec4(1,0,0,1);
}
