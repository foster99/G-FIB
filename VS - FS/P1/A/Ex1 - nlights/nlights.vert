#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec3 N1;
out vec3 vertexEye;

// Uniforms sobre la luz
uniform vec4 lightAmbient;   // similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;   // similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular;  // similar a gl_LightSource[0].specular
//uniform vec4 lightPosition;  // similar a gl_LightSource[0].position (Eye Space)

// Uniforms sobre el material
uniform vec4 matAmbient;     // similar a gl_FrontMaterial.ambient
uniform vec4 matDiffuse;     // similar a gl_FrontMaterial.diffuse
uniform vec4 matSpecular;    // similar a gl_FrontMaterial.specular
uniform float matShininess;  // similar a gl_FrontMaterial.shininess

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;           // Para obtener Eye Space
uniform mat3 normalMatrix;


void main()
{
    N1 = normalize(normalMatrix * normal);
    vertexEye = (modelViewMatrix* vec4(vertex, 1.0)).xyz;  // Coordenadas del vertice en EyeSpace
    
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
