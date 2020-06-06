#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;
uniform sampler2D colorMap; 

void main()
{   
    // DNI: 12345678 --> 123456 (cogemos los primeros 5 digitos)
    
    int d;
    float s = vtexCoord.s;
    
    if (s < 1.0)         d = 1;
    else if (s < 2.0)    d = 2 - 1;
    else if (s < 3.0)    d = 3 - 2;
    else if (s < 4.0)    d = 4 - 3;
    else if (s < 5.0)    d = 5 - 4;
    else                 d = 6 - 5;
    
    s = (s+d)/10;
    
    if (texture(colorMap, vec2(s,vtexCoord.t)).a < 0.5) discard;
    
    fragColor = vec4(0,0,1,1);
}
