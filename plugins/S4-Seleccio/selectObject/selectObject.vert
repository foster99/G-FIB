#version 330 core

uniform mat4 modelViewProjectionMatrix;

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;

out vec3 frontColor;

void main()
{
	frontColor = color;
	gl_Position = modelViewProjectionMatrix * vec4(vertex,1.0);
}

	
