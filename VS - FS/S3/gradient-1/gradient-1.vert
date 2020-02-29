#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    vtexCoord = texCoord;
    
    float t = 4 * (vertex.y - boundingBoxMin.y)/(boundingBoxMax.y - boundingBoxMin.y);
    
    vec3 colorInterpol;    
    if (fract(t) == 0) {
        switch (int(t)) {
            case 4: colorInterpol = vec3(0,0,1); break;
            case 3: colorInterpol = vec3(0,1,1); break;
            case 2: colorInterpol = vec3(0,1,0); break;
            case 1: colorInterpol = vec3(1,1,0); break;
            case 0: colorInterpol = vec3(1,0,0); break;
            default: break;
        }
    }
    else {
        vec3 colorMax, colorMin;
        if (t > 3) {
            colorMax = vec3(0,0,1); // Blue
            colorMin = vec3(0,1,1); // Green
        }
        else if (t > 2) {
            colorMax = vec3(0,1,1); // Green
            colorMin = vec3(0,1,0); // Red
        }
        else if (t > 1) {
            colorMax = vec3(0,1,0); // Green
            colorMin = vec3(1,1,0); // Red
        }
        else {
            colorMax = vec3(1,1,0); // Green
            colorMin = vec3(1,0,0); // Red
        }
        
        colorInterpol = mix(colorMin, colorMax, fract(t));
    }
    
            
    
    frontColor = vec4(colorInterpol,1.0);
    
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
