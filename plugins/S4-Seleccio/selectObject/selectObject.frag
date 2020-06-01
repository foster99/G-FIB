#version 330 core

in vec3 frontColor;
out vec4 fragColor;

uniform vec4 color;
uniform bool selection;

void main()
{
    if (selection) {
        fragColor = color;
    }
    else { 
        fragColor = vec4(frontColor,1);
    }
}

