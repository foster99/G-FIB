#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;
out vec3 Neye;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform float speed = 0.1;
uniform float time; 

void main()
{
    vec3 N = normalize(normalMatrix * normal).xyz;
    frontColor = vec4(1,1,1,0);
    vtexCoord = texCoord;// + speed * time;
    
    Neye = (modelViewMatrix*vec4(normal,0)).xyz;
    //Neye = N.xyz; //Analogo
    
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
