#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float time;
const float tau = 2 * 3.141592;

mat3 rotateY(float alpha) {
    float cosAlpha = cos(alpha);
    float sinAlpha = sin(alpha);
    return mat3(vec3(cosAlpha, 0, -sinAlpha), vec3(0,1,0), vec3(sinAlpha,0,cosAlpha));
}

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    
    float alpha = 0.4 * vertex.y * sin(mod(time,tau));
    mat3 T = rotateY(alpha);
    
    gl_Position = modelViewProjectionMatrix * vec4(T*vertex, 1.0);
}
