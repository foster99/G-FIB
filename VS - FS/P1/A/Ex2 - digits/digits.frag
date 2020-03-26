#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D colorMap;
uniform float time;

void main()
{   
    int value = (int(time));
    int d, d0 = value%10, d1 = (value/10)%10, d2 = (value/100)%10;
     
    float s = vtexCoord.s;
    
    if (s < 1.0)         d = d2;
    else if (s < 2.0)    d = d1 - 1;
    else                 d = d0 - 2;
    
    s = (s+d)/10;
    
    if (texture(colorMap, vec2(s,vtexCoord.t)).a < 0.5) discard;
    fragColor = vec4(1,0,0,1);
}
