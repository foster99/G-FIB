#version 330 core

in vec4 frontColor;
out vec4 fragColor;

void main()
{
    // gl_FragDepth va entre 0 y 1, por lo tanto al multiplicarlo
    // por -1, este esta entre -1 y 0, y hay que moverlo una
    // unidad hacia arriba (+1)
    
    gl_FragDepth = - gl_FragCoord.z + 1.0;
    
    fragColor = frontColor;
}
