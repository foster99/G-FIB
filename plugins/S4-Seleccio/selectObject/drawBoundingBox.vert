#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 color;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

mat4 scale(float sx, float sy, float sz) {
 return mat4(   vec4(sx,0,0,0),
                vec4(0,sy,0,0),
                vec4(0,0,sz,0),
                vec4(0,0,0, 1));
}

mat4 translate(float sx, float sy, float sz) {
 return mat4(   vec4(1,0,0,sx),
                vec4(0,1,0,sy),
                vec4(0,0,1,sz),
                vec4(0,0,0, 1));
}


void main()
{
    frontColor = vec4(color,1);
    
    vec3 BB = boundingBoxMax - boundingBoxMin;
    vec3 BBCentre = (boundingBoxMax + boundingBoxMin)/2;
    
    vec4 vertexMOD;
    vertexMOD = vec4(vertex,1);
    vertexMOD -= vec4(vec3(0.5),0);       // Centrar en origen
    vertexMOD *= scale(BB.x,BB.y,BB.z);   // Escalar al tamano del modelo
    vertexMOD *= translate(BBCentre.x,BBCentre.y,BBCentre.z); // Centrar en el centro del modelo
    
    gl_Position = modelViewProjectionMatrix * vertexMOD;
}
