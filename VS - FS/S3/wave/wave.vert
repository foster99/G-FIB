#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

const float pi = 3.141592;
uniform float amp = 0.5;
uniform float freq = 0.25;
uniform float time;

mat3 rotateX(float alpha) {
    float cosAlpha = cos(alpha);
    float sinAlpha = sin(alpha);
    return mat3(vec3(1,0,0), vec3(0,cosAlpha, sinAlpha), vec3(0,-sinAlpha,cosAlpha));
}

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    
    float alpha = amp * sin(2*pi*freq*time + vertex.y);
    mat3 T = rotateX(alpha);
    
    gl_Position = modelViewProjectionMatrix * vec4(T * vertex, 1.0);
}
