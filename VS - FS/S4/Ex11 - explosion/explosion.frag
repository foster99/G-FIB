#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;

out vec4 fragColor;
uniform sampler2D explosion;
uniform float time;


void main()
{

    float frame = mod(time*30,48);
    
    float coordS = floor(mod(frame,8));
    float coordT = ceil(frame/8);
    
    float S = vtexCoord.s + coordS; 
    float T = vtexCoord.t - coordT;
    
    fragColor = texture(explosion , vec2(S/8,T/6));
    fragColor = fragColor * fragColor.a;
}
