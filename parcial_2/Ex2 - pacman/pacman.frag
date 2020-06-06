#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D colormap;

float s = vtexCoord.x * 100;
float t = vtexCoord.y * 100;

bool circulo(float a, float b) {

    float R, position, edge;
    
    R = 3;
    position = (s - a)*(s - a) + (t - b)*(t - b);
    edge = R*R;
    
    return (position < edge) && (position > 2);
}

bool rectangulo(float ax, float bx, float ay, float by) {
    return ax <= s && s < bx && ay <= t && t < by;
}

void main()
{
    float w = 2.0, h = 40;

    bool linea = (rectangulo(10,10+w,55,55+h)) ||
                 (rectangulo(10,10+w,45-h,45)) ||
                 (rectangulo(90-w,90,55,55+h)) ||
                 (rectangulo(90-w,90,45-h,45)) ||

                 (rectangulo(30,70  ,30,30+w)) ||
                 (rectangulo(30,70  ,70-w,70)) ||

                 (rectangulo(30,70  ,40,40+w)) ||
                 (rectangulo(30,70  ,60-w,60)) ||

                 (rectangulo(40,40+w,10,20  )) ||
                 (rectangulo(60-w,60,10,20  )) ||
                 (rectangulo(40,40+w,80,90  )) ||
                 (rectangulo(60-w,60,80,90  ));

    bool pacman = (40 < s && s <= 50) && (30 < t && t <= 40);

    if (linea) {
        fragColor = vec4(0,0,1,1);
        return;
    }
    
    if (pacman) {
        fragColor = texture(colormap, vec2((s+10)/20,t/10));
        return;
    }

    if ((70 < s && s <= 80) && (30 < t && t <= 40)) {

        fragColor = texture(colormap, vec2((s+10)/20,t/10));
        if (fragColor == vec4(1,0,0,1))
            fragColor = vec4(1,0.8,0,1);
        return;
    }

    if ((70 < s && s <= 80) && (40 < t && t <= 50)) {
        
        fragColor = texture(colormap, vec2((s+10)/20,t/10));
        if (fragColor == vec4(1,0,0,1))
            fragColor = vec4(1,0.8,0.8,1);
        return;
    }

    if ((40 < s && s <= 60) && (30 < t && t <= 40)) {
        
        fragColor = texture(colormap, vec2((s+10)/20,t/10));
        if (fragColor == vec4(1,0,0,1))
            fragColor = vec4(0.2,0.7,1,1);
        return;
    }

    if ((50 < s && s <= 60) && (40 < t && t <= 50)) {
        
        fragColor = texture(colormap, vec2((s+10)/20,t/10));
        return;
    }

    // for (int i=0; i< 100; i+=10 ) {
    //     for (int j=0; j< 100; j+=10 ) {
    //         if (circulo(i, j)) {
    //             fragColor = vec4(vec3(1),1);
    //             return;
    //         }
    //     }
    // }
    fragColor = vec4(vec3(0),1);
}
