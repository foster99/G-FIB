#version 330 core


in vec3 frontColor;
out vec4 fragColor;

uniform bool invert;
uniform bool mirror;
uniform sampler2D colorMap;
uniform float SIZE;

void main()
{
    if (mirror) {
        vec2 st = (gl_FragCoord.xy - vec2(0.5)) / SIZE;
        fragColor = mix(texture2D(colorMap, st), vec4(vec3(0),1), 0.2);
        return;
    }

    fragColor = vec4(frontColor,1);
}

