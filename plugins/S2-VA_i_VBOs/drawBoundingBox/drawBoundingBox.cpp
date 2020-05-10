#include "drawBoundingBox.h"
#include "glwidget.h"

#define SHADERS_PATH "./drawBoundingBox"

void DrawBoundingBox::setVS() {
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs -> compileSourceFile(QString(SHADERS_PATH) + QString(".vert"));
    cout << "VS log:" << vs->log().toStdString() << endl;
}
 
void DrawBoundingBox::setFS() {
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs -> compileSourceFile(QString(SHADERS_PATH) + QString(".frag")); 
    cout << "FS log:" << fs->log().toStdString() << endl;
}

void DrawBoundingBox::creaBuffers() {
    
    GLWidget &g = *glwidget();
    g.makeCurrent();
    
    // Crear un VAO
    g.glGenVertexArrays(1, &VAO_bb);
    g.glBindVertexArray(VAO_bb);
    
    /*   PINTAR UN CUBITO
          6 +--------+ 7
           /|       /|
          / |      / |
       3 +--------+ 2|
         |  |     |  |      strip: 3 2 6 7 4 2 0 3 1 6 5 4 1 0 
         |5 +-----|--+ 4    normales: 
         | /      | /
         |/       |/
       1 +--------+ 0
    */
    
    float coords[] =  { 0, 1, 0,  // 3
                        1, 1, 0,  // 2
                        0, 1, 1,  // 6
                        1, 1, 1,  // 7
                        1, 0, 1,  // 4
                        1, 1, 0,  // 2
                        1, 0, 0,  // 0
                        0, 1, 0,  // 3
                        0, 0, 0,  // 1
                        0, 1, 1,  // 6
                        0, 0, 1,  // 5
                        1, 0, 1,  // 4
                        0, 0, 0,  // 1
                        1, 0, 0   // 0
    };
    
    float colors[] =  { 1, 0, 0,
                        1, 0, 0,
                        1, 0, 0,
                        1, 0, 0,
                        1, 0, 0,
                        1, 0, 0,
                        1, 0, 0,
                        1, 0, 0,
                        1, 0, 0,
                        1, 0, 0,
                        1, 0, 0,
                        1, 0, 0,
                        1, 0, 0,
                        1, 0, 0
    };
  
    // Crear VBO para las coords
    g.glGenBuffers(1, &VBO_coords);
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(0);
    
    // Crear VBO para los colores
    g.glGenBuffers(1, &VBO_colors);
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(0);
    
    g.glBindVertexArray(0);
}

void DrawBoundingBox::onPluginLoad()
{
    // Flag para controlar que no se han creado los buffers
    created=false;
    
    // Shaders
    setVS();
    setFS();
    
    // Link shaders to program
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;
    
}

void DrawBoundingBox::computeBoundingBox() {
    
    GLWidget &g = *glwidget();
    g.makeCurrent();
     
    Scene* scn=scene();
    const auto& objects = scn -> objects();
    
    for (const auto& obj : objects) {
        
        program->setUniformValue("boundingBoxMin", obj.boundingBox().min());
        program->setUniformValue("boundingBoxMax", obj.boundingBox().max());
        
        g.glBindVertexArray(VAO_bb);              // Seleccionamos el VAO
        g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 14); // Establecemos modo interpretacion
        g.glBindVertexArray(0); 
    }
}

void DrawBoundingBox::postFrame()
{
    // bind shader
    program->bind();
    
    if (!created) {
        created = true;
        creaBuffers();
    }
     
    // Send uniforms
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    GLWidget &g = *glwidget(); 
    g.makeCurrent(); 
    
    // Para establecer el modo de pintado: (GL_LINE, GL_FILL, GL_POINTS)
        
        // 1. guardamos el anterior
//         GLint polygonMode;    
//         g.glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
    
        // 2. Ponemos el modo deseado: GL_LINE = WireFrame
        g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  
    
        // 3. Pintamos con el nuevo modo
        computeBoundingBox();
        
        // 4. Restablecemod modo de pintado anterior
         g.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // unbind shader
    program->release(); 
}
