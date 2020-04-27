#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec3 N[];
in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float time ;
const float speed = 0.5;

void main( void )
{
    vec3 n = normalize((N[0] + N[1] + N[2])/3);
    vec3 t = speed * time * n;
    
	for( int i = 0 ; i <  3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * (gl_in[i].gl_Position + vec4(t,0));
		
		EmitVertex();
	}
    EndPrimitive();
}
