#version 330 core

in vec2 vtexCoord;
in vec3 N1;
in vec4 V;

out vec4 fragColor;

uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform sampler2D noise;

vec4 shading(vec3 N, vec3 Pos, vec4 diffuse) {

    vec3 lightPos = vec3(0.0,0.0,2.0);
    
    vec3 L = normalize(lightPos - Pos);
    vec3 V = normalize(-Pos);
    vec3 R = reflect(-L,N);
    
    float NdotL = max(0.0, dot( N,L ));
    float RdotV = max(0.0, dot( R,V ));
    float Ispec = pow(RdotV, 20.0);
    
    return diffuse * NdotL + Ispec;
}

void main()
{
    vec4 coefS = 0.3 * vec4(0,1,-1,0);
    vec4 coefT = 0.3 * vec4(-2,-1,1,0);
    
    float s = dot(coefS,V);
    float t = dot(coefT,V);
    
    float v = texture(noise, vec2(s,t)).r;
    vec4 white = vec4(1.0,1.0,1.0,1.0);
    vec4 redish = vec4(0.5,0.2,0.2,1.0);
    
    vec4 color;
    if (v <= 0.5) color = mix(white, redish, v*2);
    else color = mix(redish, white, v*2 - 1);
    
    fragColor = shading(normalize(normalMatrix * N1), (modelViewMatrix * V).xyz, color);
}
