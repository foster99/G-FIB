#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    vec3 v = vertex - vec3(0,0,0);  // vector centro - vertice del modelo
    float d = max(max(abs(v.x),abs(v.y)),abs(v.z)); // distancia divisora
    vec3 proj = v/d;
    
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(proj, 1.0);
    
}
