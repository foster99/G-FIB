#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;

out vec4 fragColor;

uniform bool classic = false;

void main()
{   

    float x = vtexCoord.x;
    float y = vtexCoord.y;
    float a = 0.5;
    float b = 0.5;
    float R = 0.2;
    
    float position = (x - a)*(x - a) + (y - b)*(y - b);
    float edge = R*R;
    
    fragColor = vec4(1, vec2(step(edge, position)), 1);
    
    // si ya es rojo, no hace falta pintar
    if (!classic && fragColor.y != 0) { 
        
        float phi = 3.141592/16;
        float theta = atan(x - 0.5, y - 0.5);
        
        if (mod(theta/phi + 0.5, 2) < 1) // rojo
            fragColor = vec4(1,0,0,1);
    }
}
