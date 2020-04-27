#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec2 gtexCoord;
out vec4 gfrontColor;

uniform mat3 normalMatrix;
uniform mat4 modelViewProjectionMatrix;

vec3 finalColor;
vec3 N;
    
void sendVertex(vec3 pos) {
    
    gfrontColor = vec4(finalColor,1) * N.z;
    gl_Position = modelViewProjectionMatrix * vec4(pos,1);
    EmitVertex();
}

void voxelize(vec3 centre, float size) {
    float D = size/2;
    
    // Back
    N = normalMatrix * vec3(0,0,-1);
    gtexCoord = vec2(1,0); sendVertex(centre + vec3(-D, D,-D)); // 1
    gtexCoord = vec2(0,0); sendVertex(centre + vec3( D, D,-D)); // 2
    gtexCoord = vec2(1,1); sendVertex(centre + vec3(-D,-D,-D)); // 3
    gtexCoord = vec2(0,1); sendVertex(centre + vec3( D,-D,-D)); // 4
    EndPrimitive();
    
    // Right
    N = normalMatrix * vec3(1,0,0);
    gtexCoord = vec2(1,0); sendVertex(centre + vec3( D, D,-D));
    gtexCoord = vec2(0,0); sendVertex(centre + vec3( D, D, D));
    gtexCoord = vec2(1,1); sendVertex(centre + vec3( D,-D,-D));
    gtexCoord = vec2(0,1); sendVertex(centre + vec3( D,-D, D));
    EndPrimitive();
    
    // Front
    N = normalMatrix * vec3(0,0,1);
    gtexCoord = vec2(1,0); sendVertex(centre + vec3(-D,-D, D));
    gtexCoord = vec2(0,0); sendVertex(centre + vec3( D,-D, D));
    gtexCoord = vec2(1,1); sendVertex(centre + vec3(-D, D, D));
    gtexCoord = vec2(0,1); sendVertex(centre + vec3( D, D, D));
    EndPrimitive();
    
    // Up
    N = normalMatrix * vec3(0,1,0);
    gtexCoord = vec2(1,0); sendVertex(centre + vec3( D, D, D));
    gtexCoord = vec2(0,0); sendVertex(centre + vec3( D, D,-D));
    gtexCoord = vec2(1,1); sendVertex(centre + vec3(-D, D, D));
    gtexCoord = vec2(0,1); sendVertex(centre + vec3(-D, D,-D));
    EndPrimitive();
    
    // Left
    N = normalMatrix * vec3(-1,0,0);
    gtexCoord = vec2(1,0); sendVertex(centre + vec3(-D,-D,-D));
    gtexCoord = vec2(0,0); sendVertex(centre + vec3(-D,-D, D));
    gtexCoord = vec2(1,1); sendVertex(centre + vec3(-D, D,-D));
    gtexCoord = vec2(0,1); sendVertex(centre + vec3(-D, D, D));
    EndPrimitive();
    
    // Down
    N = normalMatrix * vec3(0,-1,0);
    gtexCoord = vec2(1,0); sendVertex(centre + vec3( D,-D,-D));
    gtexCoord = vec2(0,0); sendVertex(centre + vec3( D,-D, D));
    gtexCoord = vec2(1,1); sendVertex(centre + vec3(-D,-D,-D));
    gtexCoord = vec2(0,1); sendVertex(centre + vec3(-D,-D, D));
    EndPrimitive();
}

vec3 nearestColor(vec3 avgColor) {
    float R,G,B,C,Y;
    
    R = distance(avgColor, vec3(1,0,0));
    G = distance(avgColor, vec3(0,1,0));
    B = distance(avgColor, vec3(0,0,1));
    C = distance(avgColor, vec3(0,1,1));
    Y = distance(avgColor, vec3(1,1,0));
    
    if (R <= G && R <= B && R <= C && R <= Y) return vec3(1,0,0);
    if (G <= R && G <= B && G <= C && G <= Y) return vec3(0,1,0);
    if (B <= R && B <= G && B <= C && B <= Y) return vec3(0,0,1);
    if (C <= R && C <= G && C <= B && C <= Y) return vec3(0,1,1);
    return vec3(1,1,0);
}

void main( void )
{
    float size = 0.1;
    vec3 G, avgColor;
    
    G = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position).xyz/3;
    G = size * floor(G/size);
    
    avgColor = (vfrontColor[0] + vfrontColor[1] + vfrontColor[2]).xyz/3;
    finalColor = nearestColor(avgColor);
    
    voxelize(G, size);
    
}
