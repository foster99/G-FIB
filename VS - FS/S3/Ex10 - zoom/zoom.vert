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

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    
    
    float scale = 0.5 + abs(sin(time));

    
    vec4 res = modelViewProjectionMatrix * vec4(vertex, 1);
    
    // LAS DOS OPCIONES FUNCIONAN
    
    //gl_Position = vec4(res.xy, res.z/scale, res.w/scale);
    
    gl_Position = vec4(scale * res.xy, res.z, res.w);

}
