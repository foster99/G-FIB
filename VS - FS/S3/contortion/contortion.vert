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

mat4 rotateX(float alpha) {
    float cosAlpha = cos(alpha);
    float sinAlpha = sin(alpha);
    return mat4(vec4(1,0,0,0), vec4(0,cosAlpha, sinAlpha,0), vec4(0,-sinAlpha,cosAlpha,0),vec4(0,0,0,1));
}

mat4 translate(float x, float y, float z) {
    return mat4(vec4(1,0,0,0), vec4(0,1,0,0), vec4(0,0,1,0),vec4(x,y,z,1));
}

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    
    float alpha = 0;
    if (vertex.y > 0.5) {
        alpha = (vertex.y - 0.5) * sin(time);
        mat4 T = translate(0,1,0) * rotateX(alpha) * translate(0,-1,0);
        gl_Position = modelViewProjectionMatrix * T * vec4(vertex, 1.0);
    }
    
    else gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
