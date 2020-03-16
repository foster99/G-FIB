#version 330 core

out vec4 fragColor;

in float x;
uniform float time;

void main()
{   

    if (x > time) discard;
    fragColor = vec4(0,0,1,1);
}
