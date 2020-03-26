#version 330 core

out vec4 fragColor;

in vec3 N1;
in vec3 vertexEye;


// Uniforms sobre la luz
//uniform vec4 lightAmbient;   // similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;   // similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular;  // similar a gl_LightSource[0].specular
//uniform vec4 lightPosition;  // similar a gl_LightSource[0].position (Eye Space)

// Uniforms sobre el material
//uniform vec4 matAmbient;     // similar a gl_FrontMaterial.ambient
uniform vec4 matDiffuse;     // similar a gl_FrontMaterial.diffuse
uniform vec4 matSpecular;    // similar a gl_FrontMaterial.specular
uniform float matShininess;  // similar a gl_FrontMaterial.shininess

// Uniforms del viewer
uniform int n = 4;
const float pi = 3.141592;

vec4 myPhongN(vec3 N, vec3 L, vec3 V, float qtt) {
    
    float DotNL = dot(N,L); 
    if (DotNL < 0)
        return vec4(0);
    
    vec3 R = normalize(2 * DotNL * N - L);
    float DotRV =  dot(R,V);
    
    return  (matDiffuse * lightDiffuse * max(0.0,DotNL))/sqrt(qtt) + (matSpecular * lightSpecular * pow(max(0.0,DotRV),matShininess));
}

void main()
{
    
    vec3 L,V, lightPosition;
    vec4 Ltotal = vec4(0); 
    float a_step = 2*pi/n;
    for (float alpha = 0; alpha < 2*pi; alpha += a_step) {
    
        lightPosition = vec3(10*cos(alpha),10*sin(alpha),0);
        L = normalize(lightPosition.xyz - vertexEye);  // Vector luz -> vertex
        V = normalize(-vertexEye);                     // Vector vertex -> camara (0,0,0)
        
        Ltotal = Ltotal + myPhongN(N1,L,V,float(n));
    }
    
    
    fragColor = Ltotal;
} 
