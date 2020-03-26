#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
in vec3 Neye;

out vec4 fragColor;


uniform sampler2D colorMap;

void main()
{
    vec2 C1 = vec2(0.34,0.65) - 0.1*Neye.xy;
    vec2 C2 = vec2(0.66,0.65) - 0.1*Neye.xy;
    float iris = 0.05 * 0.05;
    
    
    if (pow(vtexCoord.s - C1.s, 2) + pow(vtexCoord.t - C1.t, 2) <= iris)
        fragColor = vec4(0,0,0,1);
    else if (pow(vtexCoord.s - C2.s, 2) + pow(vtexCoord.t - C2.t, 2) <= iris)
        fragColor = vec4(0,0,0,1);
    else
        fragColor = frontColor * texture(colorMap, vtexCoord);
        
}
