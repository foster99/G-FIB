#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 vfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float n = 1; // Temps de caiguda lliure en segons
uniform float time;

float t;
const float a = -9.8;

float mov_accelerat(bool subir) {
    float v0,y0;

    if (subir) {
        v0 = 0;
        y0 = 0;
        return y0 + v0*t + 0.5*a*t*t;

    } else {
        v0 = -a*n;
        y0 = 0.5*a*n*n;
        return y0 + v0*(t-n) + 0.5*a*(t-n)*(t-n);
    }
    
    
    
}

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    vfrontColor = vec4(color,1.0) * N.z;

    t = mod(time,2*n);

    bool subir = false;
    if (t < n) subir = true;

    vec3 vertexMOD = vec3(vertex.x, vertex.y + mov_accelerat(subir), vertex.z);
 
    gl_Position = vec4(vertexMOD, 1.0);
}
