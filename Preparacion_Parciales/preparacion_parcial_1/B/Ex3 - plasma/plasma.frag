#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D fbm;
uniform float time;

const float pi = 3.14159;

void main()
{
    float r = texture(fbm, vtexCoord).r;
    float v = sin(2*pi*0.1*time + 2*pi*r);
    
    v = (v + 1) * 3; // [-1,1] -> [0,6]
    
    vec3 COLOR;
    
    if (fract(v) == 0) {
    
        switch (int(v)%6) {
            case 0: COLOR = vec3(1,0,0); break; // RED
            case 1: COLOR = vec3(1,1,0); break; // YELLOW
            case 2: COLOR = vec3(0,1,0); break; // GREEN
            case 3: COLOR = vec3(0,1,1); break; // CYAN
            case 4: COLOR = vec3(0,0,1); break; // BLUE
            case 5: COLOR = vec3(1,0,1); break; // MAGENTA
            default: break;
        }
        
    } else {
    
        vec3 colorMax, colorMin;
        
        if (v > 5) {
            colorMax = vec3(1,0,0); // RED
            colorMin = vec3(1,0,1); // MAGENTA
        }
        else if (v > 4) {
            colorMax = vec3(1,0,1); // MAGENTA
            colorMin = vec3(0,0,1); // BLUE
        }
        else if (v > 3) {
            colorMax = vec3(0,0,1); // BLUE
            colorMin = vec3(0,1,1); // CYAN
        }
        else if (v > 2) {
            colorMax = vec3(0,1,1); // CYAN
            colorMin = vec3(0,1,0); // GREEN
        }
        else if (v > 1) {
            colorMax = vec3(0,1,0); // GREEN
            colorMin = vec3(1,1,0); // YELLOW
        }
        else {
            colorMax = vec3(1,1,0); // YELLOW
            colorMin = vec3(1,0,0); // RED
        }
        
        
        
        COLOR = mix(colorMin, colorMax, fract(v));
    }
    
    fragColor = vec4(COLOR,1.0);
    
}
