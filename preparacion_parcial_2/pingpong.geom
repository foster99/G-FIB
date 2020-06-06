#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;


uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform mat4 modelViewProjectionMatrix;

uniform float n = 1;
const float a = -9.8;

mat4 projectOntoPlane()
{
	vec3 light = vec3(4,10,-4);
	float A = 0;
	float B = 1;
	float C = 0;
	float D = -0.5*a*n*n+0.9;
	float s = -dot(vec4(-A,-B,-C,-D), vec4(light,1));	
	mat4 trans0 = mat4(1.0);
	mat4 trans1 = mat4(1.0); 
	trans0[3].xyz = light;	
	mat4 aux = mat4(vec4(s, 0, 0, -A), vec4(0, s, 0, -B), vec4(0, 0, s, -C), vec4(0));
	trans1[3].xyz = -light;
	return  trans0 * aux * trans1;
}


void Emit() {
	gl_Position.z /= 2.0;
	EmitVertex();
}

void main( void )
{	
	// Pintar suelo
	if (gl_PrimitiveIDIn == 0) {
        
        gfrontColor = vec4(vec3(0.5),1); // color del suelo
        
		vec3 position;
        float ground = 0.5*a*n*n - 1.0;
        
        position  = vec3(5.0, ground, 5.0);
        gl_Position = modelViewProjectionMatrix * vec4(position, 1);
        Emit();
        
        position  = vec3(-5.0, ground, 5.0);
        gl_Position = modelViewProjectionMatrix * vec4(position, 1);
        Emit();
        
        position  = vec3(5.0, ground, -5.0);
        gl_Position = modelViewProjectionMatrix * vec4(position, 1);
        Emit();
        
        position  = vec3(-5.0, ground, -5.0);
        gl_Position = modelViewProjectionMatrix * vec4(position, 1);
        Emit();
        
        EndPrimitive();
    }

	// Pintar pelota normal
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		Emit();
	}
    EndPrimitive();
    
	// Pintar sombra de la pelota
    for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(0);
		vec4 P = gl_in[i].gl_Position;
		// P.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix * projectOntoPlane() * P;
		Emit();
	}
    EndPrimitive();


}
