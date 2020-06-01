#version 330 core
uniform mat4 modelViewProjectionMatrix;

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 color;

out vec3 frontColor;

uniform bool invert;
uniform bool mirror;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

mat4 inverter_matrix(vec3 normal_plano, vec3 P) {

	// normal_plano: 	Normal del plano sobre el que reflejamos
	// P:				Punto por el que pasa el plano.

	float a = normal_plano.x;
	float b = normal_plano.y;
	float c = normal_plano.z;
	float d = - dot(normal_plano, P);

	return mat4(vec4(1.-2.*a*a,   -2.*b*a,   -2.*c*a, 0.),
				vec4(  -2.*b*a, 1.-2.*b*b,   -2.*c*b, 0.),
				vec4(  -2.*c*a,   -2.*c*b, 1.-2.*c*c, 0.),
				vec4(  -2.*d*a,   -2.*d*b,   -2.*d*c, 1.));

}

void main()
{
	frontColor = color;

	if (invert) {
		vec3 normal_plano = vec3(0,1,0); // Normal del plano sobre el que reflejamos
		vec3 P = boundingBoxMin;	 	 // Punto por el que pasa el plano.

		gl_Position = modelViewProjectionMatrix * inverter_matrix(normal_plano, P) * vec4(vertex,1.0);
		return;
	}
	
	gl_Position = modelViewProjectionMatrix * vec4(vertex,1.0);
}

	
