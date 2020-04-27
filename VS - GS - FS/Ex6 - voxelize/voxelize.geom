#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

out vec4 gfrontColor;

uniform mat3 normalMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform float size = 0.1;

vec3 N;

void sendVertex(vec3 pos) {
    
    gfrontColor = vec4(vec3(0.8),1) * N.z;
    gl_Position = modelViewProjectionMatrix * vec4(pos,1);
    EmitVertex();
}

void main( void )
{
    vec3 G, position;
    float D = size/2;

    G = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position).xyz/3;
    G = size * floor(G/size);
    
    // Back
    N = normalMatrix * vec3(0,0,-1);
    sendVertex(G + vec3(-D, D,-D)); // 1
    sendVertex(G + vec3( D, D,-D)); // 2
    sendVertex(G + vec3(-D,-D,-D)); // 3
    sendVertex(G + vec3( D,-D,-D)); // 4
    EndPrimitive();
    
    // Right
    N = normalMatrix * vec3(1,0,0);
    sendVertex(G + vec3( D, D,-D));
    sendVertex(G + vec3( D, D, D));
    sendVertex(G + vec3( D,-D,-D));
    sendVertex(G + vec3( D,-D, D));
    EndPrimitive();
    
    // Front
    N = normalMatrix * vec3(0,0,1);
    sendVertex(G + vec3(-D,-D, D));
    sendVertex(G + vec3( D,-D, D));
    sendVertex(G + vec3(-D, D, D));
    sendVertex(G + vec3( D, D, D));
    EndPrimitive();
    
    // Up
    N = normalMatrix * vec3(0,1,0);
    sendVertex(G + vec3( D, D, D));
    sendVertex(G + vec3( D, D,-D));
    sendVertex(G + vec3(-D, D, D));
    sendVertex(G + vec3(-D, D,-D));
    EndPrimitive();
    
    // Left
    N = normalMatrix * vec3(-1,0,0);
    sendVertex(G + vec3(-D,-D,-D));
    sendVertex(G + vec3(-D,-D, D));
    sendVertex(G + vec3(-D, D,-D));
    sendVertex(G + vec3(-D, D, D));
    EndPrimitive();
    
    // Down
    N = normalMatrix * vec3(0,-1,0);
    sendVertex(G + vec3( D,-D,-D));
    sendVertex(G + vec3( D,-D, D));
    sendVertex(G + vec3(-D,-D,-D));
    sendVertex(G + vec3(-D,-D, D));
    EndPrimitive();
    
}
