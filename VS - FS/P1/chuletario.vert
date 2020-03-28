// ILUMINACION DE CAMARA POR VERTICE
    void main() {
        vec3 N = normalize(normalMatrix * normal);
        frontColor = vec4(color,1.0) * N.z;		// Crear una iluminacion de camara
        vtexCoord = texCoord;
        gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
    }
// ILUMINACION DE CAMARA POR FRAGMENTO
    in vec3 N; // Le pasamos la normal (NO LA USAMOS EN EL VS)
    in vec4 frontColor;
    out vec4 fragColor;

    void main() {
        fragColor = frontColor * N.z;
    }
// PHONG ORIGINAL
    vec4 myPhong(vec3 N, vec3 L, vec3 V) {
        float DotNL = dot(N,L);
        if (DotNL < 0) return  (matAmbient * lightAmbient);
        vec3 R = normalize(2 * DotNL * N - L);
        float DotRV = dot(R,V);
        if (DotRV < 0) return  (matAmbient * lightAmbient) + (matDiffuse * lightDiffuse * DotNL);
        return  (matAmbient * lightAmbient) + (matDiffuse * lightDiffuse * DotNL) + (matSpecular * lightSpecular * pow(DotRV,matShininess));
    }

    // Uniforms sobre la luz
    uniform vec4 lightAmbient;   // similar a gl_LightSource[0].ambient
    uniform vec4 lightDiffuse;   // similar a gl_LightSource[0].diffuse
    uniform vec4 lightSpecular;  // similar a gl_LightSource[0].specular
    uniform vec4 lightPosition;  // similar a gl_LightSource[0].position (Eye Space)

    // Uniforms sobre el material
    uniform vec4 matAmbient;     // similar a gl_FrontMaterial.ambient
    uniform vec4 matDiffuse;     // similar a gl_FrontMaterial.diffuse
    uniform vec4 matSpecular;    // similar a gl_FrontMaterial.specular
    uniform float matShininess;  // similar a gl_FrontMaterial.shininess

    // Calculando por vertice
    void main() {   
        // TODAS LAS OPERACIONES SE DEBEN REALIZAR EN EYE SPACE
        vec3 vertexEye = (modelViewMatrix* vec4(vertex, 1.0)).xyz;  // Coordenadas del vertice en EyeSpace
        vec3 N = normalize(normalMatrix * normal);
        vec3 L = normalize(lightPosition.xyz - vertexEye);  // Vector luz -> vertex
        vec3 V = normalize(-vertexEye);                     // Vector vertex -> camara (0,0,0)
        frontColor = myPhong(N, L, V);
        gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
    }

    // Calculando por fragmento
    in vec3 N1;         // Tenemos que pasar la normal
    in vec3 vertexEye;  // Tenemos que pasar las coordenadas en eyeSpace
    void main() {
        // TODAS LAS OPERACIONES SE DEBEN REALIZAR EN EYE SPACE
        vec3 L = normalize(lightPosition.xyz - vertexEye);  // Vector luz -> vertex
        vec3 V = normalize(-vertexEye);                     // Vector vertex -> camara (0,0,0)
        fragColor = myPhong(N1, L, V);
    }
 ------------------------------------------------------------------------------------------- */
// TRASLACION DE UN VERTICE
    mat4 translation(float x, float y, float z) {
        return mat4(vec4(1,0,0,0), vec4(0,1,0,0), vec4(0,0,1,0), vec4(x,y,z,1));
    }

// ROTATE EJE X
    mat4 rotateX(float alpha) {
        float cosAlpha = cos(alpha);
        float sinAlpha = sin(alpha);
        return mat4(vec4(1,0,0,0), vec4(0,cosAlpha, sinAlpha,0), vec4(0,-sinAlpha,cosAlpha,0),vec4(0,0,0,1));
    }

// ROTATE EJE Y
    mat3 rotateY(float alpha) {
        float cosAlpha = cos(alpha);
        float sinAlpha = sin(alpha);
        return mat3(vec3(cosAlpha, 0, -sinAlpha), vec3(0,1,0), vec3(sinAlpha,0,cosAlpha));
    }

// DESPLAZAMIENTO EN DIRECCION DE LA NORMAL
    vec3 v = vertex + D * normalize(normal);

// VERTICE EN NDC
    vec4 vertexNDC = gl_Position / gl_Position.w;

// INTERPOLACION DE COLORES
    vec3 colorInterpol;    
    if (fract(t) == 0) {
        switch (int(t)) {
            case 4: colorInterpol = vec3(0,0,1); break;
            case 3: colorInterpol = vec3(0,1,1); break;
            case 2: colorInterpol = vec3(0,1,0); break;
            case 1: colorInterpol = vec3(1,1,0); break;
            case 0: colorInterpol = vec3(1,0,0); break;
            default: break;
        }
    }
    else {
        vec3 colorMax, colorMin;
        if (t > 3) {
            colorMax = vec3(0,0,1); // Blue
            colorMin = vec3(0,1,1); // Green
        }
        else if (t > 2) {
            colorMax = vec3(0,1,1); // Green
            colorMin = vec3(0,1,0); // Red
        }
        else if (t > 1) {
            colorMax = vec3(0,1,0); // Green
            colorMin = vec3(1,1,0); // Red
        }
        else {
            colorMax = vec3(1,1,0); // Green
            colorMin = vec3(1,0,0); // Red
        }
    }
    colorInterpol = mix(colorMin, colorMax, fract(t));

// INVERTIR EN Z

    // VERTEX VERSION
    void main() {
        vec3 N = normalize(normalMatrix * normal);
        frontColor = vec4(color.x,color.y,color.z,1.0) * abs(N.z);
        vtexCoord = texCoord;
        vec4 pos = modelViewProjectionMatrix * vec4(vertex, 1.0);
        pos.z *= -1;
        gl_Position = pos;
    }

    // FRAGMENT VERSION
    void main() {
        // gl_FragDepth va entre 0 y 1, por lo tanto al multiplicarlo por -1, este
        // esta entre -1 y 0, y hay que moverlo una unidad hacia arriba (+1)
        gl_FragDepth = - gl_FragCoord.z + 1.0;
        fragColor = frontColor;
    }


// CALCULAR LA NORMAL EN FRAGMENT
    // V es el vertice en EyeSpace
    vec3 N = normalize(cross(dFdx(V), dFdy(V)));

// HINOMARU
    float x = vtexCoord.x, y = vtexCoord.y;
    float a = 0.5, b = 0.5, R = 0.2;
    float position = (x - a)*(x - a) + (y - b)*(y - b);
    float edge = R*R;
    
    fragColor = vec4(1, vec2(step(edge, position)), 1); // if (position < edge) return 0
 
// HINOMARU CON ANTIALIASING
    float x = vtexCoord.x, y = vtexCoord.y;
    float a = 0.5, b = 0.5, R = 0.2;
    float position = (x - a)*(x - a) + (y - b)*(y - b);
    float edge = R*R;
    
    float aa = 0.0007; // cantidad antialiasing
    fragColor = vec4(1, vec2(smoothstep(edge - aa, edge + aa, position)), 1);