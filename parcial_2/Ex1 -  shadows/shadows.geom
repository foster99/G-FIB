#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform vec3 boundingBoxMin; 
uniform mat4 modelViewProjectionMatrix;

void main( void )
{
	// Objeto normal
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();

	// Todas las proyecciones en color negro
	gfrontColor = vec4(vec3(0),1);

	vec4 P;
	// Proyeccion en plano X
	for( int i = 0 ; i < 3 ; i++ )
	{	
		P = gl_in[i].gl_Position;
		P.x = boundingBoxMin.x;
		gl_Position = modelViewProjectionMatrix * P;
		EmitVertex();
	}
    EndPrimitive();
	
	// Proyeccion en plano Y
	for( int i = 0 ; i < 3 ; i++ )
	{
		P = gl_in[i].gl_Position;
		P.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix * P;
		EmitVertex();
	}
    EndPrimitive();

	// Proyeccion en plano Z
	for( int i = 0 ; i < 3 ; i++ )
	{
		P = gl_in[i].gl_Position;
		P.z = boundingBoxMin.z;
		gl_Position = modelViewProjectionMatrix * P;
		EmitVertex();
	}
    EndPrimitive();
}
