#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float time;
uniform sampler2D sampler;


void main()
{   
    vec2 coords = vtexCoord;
    
    if (fract(time) > 0.5) {
        
        float s = vtexCoord.s, t = vtexCoord.t;
        vec2 ull = vec2(0.393,0.652);
        vec2 delta = vec2(0.057,- 0.172);
        
        if (pow(s-ull.s,2) + pow(t-ull.t,2) <= pow(0.025,2))
            coords = vec2(s + delta.s, t + delta.t);
    }
    
    fragColor = texture(sampler, coords);
}
