#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float amplitude = 0.1;
uniform float freq = 1; // Hz
uniform float time;
const float PI = 3.141592;

mat4 translation(float x, float y, float z) {
    return mat4(vec4(1,0,0,0), vec4(0,1,0,0), vec4(0,0,1,0), vec4(x,y,z,1));
}

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(N.z,N.z,N.z,0);
    vtexCoord = texCoord;
    
    float D = amplitude * sin(2*PI*freq*time); 
    vec3 ND = D * normalize(normal);
    
    vec4 vertexMOD = translation(ND.x,ND.y,ND.z) * vec4(vertex,1);
    
    gl_Position = modelViewProjectionMatrix * vertexMOD;
}
