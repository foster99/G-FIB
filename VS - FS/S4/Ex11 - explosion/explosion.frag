#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;

out vec4 fragColor;
uniform sampler2D explosion;
uniform float time;


void main()
{
    float frame = mod(time,48);
    
    float coordS = floor(mod(frame,8));
    float coordT = floor(mod(frame,48));
    
    float S = coordS + vtexCoord.s;
    float T = coordT + vtexCoord.t;
    
    fragColor = texture(explosion, vec2(S/8,T/6));
}
