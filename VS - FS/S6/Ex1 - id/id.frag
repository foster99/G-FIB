#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;
uniform sampler2D colorMap; 

void main()
{   
    // mi DNI: 46483191 --> 464831
    
    int d;
    float s = vtexCoord.s;
    
    if (s < 1.0)         d = 4;
    else if (s < 2.0)    d = 6 - 1;
    else if (s < 3.0)    d = 4 - 2;
    else if (s < 4.0)    d = 8 - 3;
    else if (s < 5.0)    d = 3 - 4;
    else                 d = 1 - 5;
    
    s = (s+d)/10;
    
    if (texture(colorMap, vec2(s,vtexCoord.t)).a < 0.5) discard;
    
    fragColor = vec4(0,0,1,1);
}
