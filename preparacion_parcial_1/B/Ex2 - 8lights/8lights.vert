#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec3 N1;
out vec3 vertexEye;
// out vec3 pos0;
// out vec3 pos1;
// out vec3 pos2;
// out vec3 pos3;
// out vec3 pos4;
// out vec3 pos5;
// out vec3 pos6;
// out vec3 pos7;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;           // Para obtener Eye Space
uniform mat3 normalMatrix;


void main()
{
    
    N1 = normalize(normalMatrix * normal);
    vertexEye = (modelViewMatrix* vec4(vertex, 1.0)).xyz;  // Coordenadas del vertice en EyeSpace
    
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
