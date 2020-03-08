#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;

void main()
{
    vec4 Grass = texture(grass2, vtexCoord);
    vec4 Rock = texture(rock1, vtexCoord);
    
    float alpha = texture(noise0, vtexCoord).r;
    
    fragColor = mix(Rock,Grass,alpha);
}
