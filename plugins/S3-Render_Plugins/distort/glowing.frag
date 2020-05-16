#version 330 core
out vec4 fragColor;

uniform sampler2D colorMap;

uniform float time;
uniform float SIZE;

const int W = 4; // filter size: 2W*2W

void main()
{
    
    vec2 coords = (gl_FragCoord.xy) / SIZE;

    vec2 st_mod = coords + vec2(0.01*sin(10.0*time + 30.0 * coords.s));

    fragColor = texture2D(colorMap, st_mod);
    
}

