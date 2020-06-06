#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

float x = vtexCoord.x * 100;
float y = vtexCoord.y * 100;

const vec4 R = vec4(1, 0, 0, 1);
const vec4 G = vec4(0, 1, 0, 1);
const vec4 B = vec4(0, 0, 1, 1);

const vec4 C = vec4(0, 1, 1, 1);
const vec4 M = vec4(1, 0, 1, 1);
const vec4 Y = vec4(1, 1, 0, 1);

bool circulo(float a, float b) {

    float R, position, edge;
    
    R = 3;
    position = (x - a)*(x - a) + (y - b)*(y - b);
    edge = R*R;
    
    return (position < edge) && (position > 2);
}

vec4 whichColor(int i) {
    
    switch (i%6) {
        case 0: return R;
        case 1: return G;
        case 2: return B;
        case 3: return C;
        case 4: return M;
        case 5: return Y;
    }
}


void main()
{
    fragColor = vec4(1);
    
    // esquinas:
    // if (circulo(0,0)) fragColor = R;
    // if (circulo(0,100)) fragColor = R;
    // if (circulo(100,0)) fragColor = R;
    // if (circulo(100,100)) fragColor = R;
    
    for (int i = 30; i < 75; i = i + 5)
        if (circulo(i,20)) fragColor = whichColor(i);
    
    for (int i = 20; i < 80; i = i + 5)
        if (circulo(30,i)) fragColor = whichColor(i);
    
    for (int i = 30; i < 60; i = i + 5)
        if (circulo(i,50)) fragColor = whichColor(i);
    
    for (int i = 30; i < 75; i = i + 5)
        if (circulo(i,80)) fragColor = whichColor(i);
    
}
