#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D map;
uniform float a = 0.5;
uniform float time; 

const float pi = 3.141592;

void main()
{
    vec4 c = texture(map, vtexCoord); 
    float m = max(max(c.r,c.g),c.b);
    
    float _cos = cos(2*pi*time), _sin = sin(2*pi*time);
    vec2 u = mat2(_cos, -_sin, _sin, _cos) * vec2(m);
    
    vec2 off = (a/100)*u;
    
    fragColor = frontColor * texture(map, vtexCoord + off);
}
