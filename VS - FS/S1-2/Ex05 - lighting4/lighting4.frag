#version 330 core

out vec4 fragColor;

in vec3 N1;
in vec3 vertexEye;


// Uniforms sobre la luz
uniform vec4 lightAmbient;   // similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;   // similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular;  // similar a gl_LightSource[0].specular
uniform vec4 lightPosition;  // similar a gl_LightSource[0].position (Eye Space)

// Uniforms sobre el material
uniform vec4 matAmbient;     // similar a gl_FrontMaterial.ambient
uniform vec4 matDiffuse;     // similar a gl_FrontMaterial.diffuse
uniform vec4 matSpecular;    // similar a gl_FrontMaterial.specular
uniform float matShininess;  // similar a gl_FrontMaterial.shininess


vec4 myPhong(vec3 N, vec3 L, vec3 V) {

    float DotNL = dot(N,L);
    
    if (DotNL < 0)
        return  (matAmbient * lightAmbient);
    
    vec3 R = normalize(2 * DotNL * N - L);
    
    float DotRV = dot(R,V);
    if (DotRV < 0)
        return  (matAmbient * lightAmbient) + (matDiffuse * lightDiffuse * DotNL);

    
    return  (matAmbient * lightAmbient) + (matDiffuse * lightDiffuse * DotNL) + (matSpecular * lightSpecular * pow(DotRV,matShininess));
}

void main()
{

    // TODAS LAS OPERACIONES SE DEBEN REALIZAR EN EYE SPACE
    vec3 L = normalize(lightPosition.xyz - vertexEye);  // Vector luz -> vertex
    vec3 V = normalize(-vertexEye);                     // Vector vertex -> camara (0,0,0)
    
    fragColor = myPhong(N1, L, V);
} 
