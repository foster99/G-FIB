#version 330 core

in vec4 gfrontColor;
in vec2 gtexCoord;
out vec4 fragColor;

uniform sampler2D lego;

void main()
{
    fragColor = gfrontColor * texture(lego, gtexCoord).b;
}
