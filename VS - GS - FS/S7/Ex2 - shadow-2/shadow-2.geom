#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform mat4 modelViewProjectionMatrix;

in vec4 vfrontColor[];
out vec4 gfrontColor;

void main( void )
{
    
    if (gl_PrimitiveIDIn == 0) {
        
        gfrontColor = vec4(0,1,1,1); // cyan
        vec3 position;
        
        float ground = boundingBoxMin.y - 0.01;
        float R = length(boundingBoxMax-boundingBoxMin)/2;
        vec3  C = (boundingBoxMax + boundingBoxMin)/2;
        
        position  = vec3(C.x - R, ground, C.z + R);
        gl_Position = modelViewProjectionMatrix * vec4(position, 1);
        EmitVertex();
        
        position  = vec3(C.x + R, ground, C.z + R);
        gl_Position = modelViewProjectionMatrix * vec4(position, 1);
        EmitVertex();
        
        position  = vec3(C.x - R, ground, C.z - R);
        gl_Position = modelViewProjectionMatrix * vec4(position, 1);
        EmitVertex();
        
        position  = vec3(C.x + R, ground, C.z - R);
        gl_Position = modelViewProjectionMatrix * vec4(position, 1);
        EmitVertex();
        
        EndPrimitive();
    }
    
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
    
    for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(0);
		vec4 P = gl_in[i].gl_Position;
		P.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix * P;
		EmitVertex();
	}
    EndPrimitive();
    
    
}
