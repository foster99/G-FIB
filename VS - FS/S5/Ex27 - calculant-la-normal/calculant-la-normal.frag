#version 330 core

in vec3 V;
in vec4 frontColor;
out vec4 fragColor;

void main()
{
    vec3 N = normalize(cross(dFdx(V), dFdy(V)));
    fragColor = frontColor * N.z;
}
