 #version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;


out vec3 Neye;
out vec3 Veye;
out vec3 Leye;

out vec3 Nworld;
out vec3 Vworld;
out vec3 Lworld;


uniform vec4 lightPosition;  // similar a gl_LightSource[0].position (Eye Space)
uniform mat4 modelViewProjectionMatrix;
uniform mat4 viewMatrixInverse;
uniform mat4 modelViewMatrix;           // Para obtener Eye Space
uniform mat3 normalMatrix;

void main()
{   
    vec3 P = (modelViewMatrix* vec4(vertex, 1.0)).xyz;  // Coordenadas del vertice en EyeSpace

    // Normal
    Nworld = normal;
    Neye = normalMatrix * Nworld;
    
    // Vector unitari del punt cap a la camera
    Veye = - P;
    Vworld = (viewMatrixInverse * vec4(Veye,0)).xyz;
    /* Alternativa */ // Vworld =(viewMatrixInverse * vec4(0,0,0,1)).xyz - vertex.xyz;
    
    // Vector unitari del punt cap a la font de llum
    Leye = lightPosition.xyz - P;
    Lworld = (viewMatrixInverse * vec4(Leye,0)).xyz;

    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
