#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;

out vec4 fragColor;


void main()
{   

    float x = vtexCoord.x;
    float y = vtexCoord.y;
    float a = 0.5;
    float b = 0.5;
    float R = 0.2;
    
    float position = (x - a)*(x - a) + (y - b)*(y - b);
    float edge = R*R;
    float aa = 0.0007; // cantidad antialiasing
    
    fragColor = vec4(1, vec2(smoothstep(edge - aa, edge + aa, position)), 1);
}
