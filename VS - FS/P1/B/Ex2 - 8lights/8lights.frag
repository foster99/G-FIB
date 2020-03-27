#version 330 core

out vec4 fragColor;

in vec3 N1;
in vec3 vertexEye;

uniform vec4 lightDiffuse;   // similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular;  // similar a gl_LightSource[0].specular
uniform vec4 matDiffuse;     // similar a gl_FrontMaterial.diffuse
uniform vec4 matSpecular;    // similar a gl_FrontMaterial.specular
uniform float matShininess;  // similar a gl_FrontMaterial.shininess

uniform mat4 modelViewMatrix;
uniform vec3 boundingBoxMin;  
uniform vec3 boundingBoxMax;

vec4 myPhong8(vec3 N, vec3 L, vec3 V) {
    
    float DotNL = dot(N,L); 
    if (DotNL < 0)
        return vec4(0);
    
    vec3 R = normalize(2 * DotNL * N - L);
    float DotRV =  dot(R,V);

        
    return  (matDiffuse * lightDiffuse * max(0.0,DotNL))/2 + (matSpecular * lightSpecular * pow(max(0.0,DotRV),matShininess));
}


void main()
{
    
    vec3 L;
    vec3 V = normalize(-vertexEye);

    // Calculos de vertices de la boundingBox
    
    vec3 Min = boundingBoxMin;
    vec3 Max = boundingBoxMax;
    
    vec3 BB[8];
    
    BB[0] = (modelViewMatrix * vec4(Max.x, Max.y, Max.z, 1)).xyz;
    BB[1] = (modelViewMatrix * vec4(Max.x, Max.y, Min.z, 1)).xyz;
    BB[2] = (modelViewMatrix * vec4(Max.x, Min.y, Max.z, 1)).xyz;
    BB[3] = (modelViewMatrix * vec4(Max.x, Min.y, Min.z, 1)).xyz;
    BB[4] = (modelViewMatrix * vec4(Min.x, Max.y, Max.z, 1)).xyz;
    BB[5] = (modelViewMatrix * vec4(Min.x, Max.y, Min.z, 1)).xyz;
    BB[6] = (modelViewMatrix * vec4(Min.x, Min.y, Max.z, 1)).xyz;
    BB[7] = (modelViewMatrix * vec4(Min.x, Min.y, Min.z, 1)).xyz;
    
    // Calculo de iluminacion para las
    
    fragColor = vec4(0);
    
    for (int i=0; i<8; ++i) {
        L = normalize(BB[i] - vertexEye);
        fragColor += myPhong8(N1,L,V);
    }
    

} 
