#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

void main()
{   

    // BANDERA COLUMNA 1 (OPCION -> NOTA MAXIMA 10)
    
    float x = vtexCoord.x * 10;
    float y = vtexCoord.y * 5;
    
    bool white = false;
    float a, b, R;
    
    // luna blanca
    a = 3.1; b = 2.5; R = 2;
    float luna = (x - a)*(x - a) + (y - b)*(y - b);
    float radio_luna = R*R;
    if (luna < radio_luna) white = true;
    
    // parte a borrar de la luna
    a = 4.1; b = 2.5; R = 1.9;
    float no_luna = (x - a)*(x - a) + (y - b)*(y - b);
    float radio_no_luna = R*R;
    if (no_luna < radio_no_luna) white = false;
    
    // redonda blanca
    a = 7; b = 2.5; R = 1.25;
    float redonda = (x - a)*(x - a) + (y - b)*(y - b);
    float radio_redonda = R*R;
    if (redonda < radio_redonda) white = true;
    
    if (white) fragColor = vec4(1);
    else fragColor = vec4(1,0,0,1);
}
