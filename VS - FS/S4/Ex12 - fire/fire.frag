#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D sampler0;
uniform sampler2D sampler1;
uniform sampler2D sampler2;
uniform sampler2D sampler3;

uniform float slice = 0.1;
uniform float time;

void main()
{
    float frame = mod(time,0.4);
    if (frame < slice)
        fragColor = texture(sampler0,vtexCoord);
    else if (frame < 2*slice)
        fragColor = texture(sampler1,vtexCoord);
    else if (frame < 3*slice)
        fragColor = texture(sampler2,vtexCoord);
    else
        fragColor = texture(sampler3,vtexCoord);
}
