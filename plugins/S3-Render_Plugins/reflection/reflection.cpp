// GLarena, a plugin based platform to teach OpenGL programming
// © Copyright 2012-2018, ViRVIG Research Group, UPC, https://www.virvig.eu
// 
// This file is part of GLarena
//
// GLarena is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "reflection.h"
#include <QCoreApplication>

const int IMAGE_WIDTH = 1080;
const int IMAGE_HEIGHT = IMAGE_WIDTH;


void Reflection::onPluginLoad()
{
    GLWidget & g = *glwidget();
    g.makeCurrent();

    // Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(g.getPluginPath()+"/../reflection/reflection.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(g.getPluginPath()+"/../reflection/reflection.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();

    // Setup texture
    g.glActiveTexture(GL_TEXTURE0); // Texture unit 0 = lo que genere ahora (esto es el numero del uniform)
    g.glGenTextures(1, &textureId); // Dame un identificador de textura
    g.glBindTexture(GL_TEXTURE_2D, textureId);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    g.glBindTexture(GL_TEXTURE_2D, 0);

    // Resize to power-of-two viewport
    g.resize(IMAGE_WIDTH,IMAGE_HEIGHT);
}


bool Reflection::paintGL()
{
    GLWidget & g = *glwidget();
    g.makeCurrent();

    // Pass 1. Draw scene
    g.glClearColor(0.8,0.8,0.8,1);
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); 
    
    // Enviamos Uniforms
    Scene* scn=scene(); 
    const auto& objects = scn -> objects();
    Point BBmin = objects[0].boundingBox().min();
    Point BBmax = objects[0].boundingBox().max();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();

    program->bind();
    program->setUniformValue("invert", true);
    program->setUniformValue("mirror", false); 
    program->setUniformValue("boundingBoxMin", BBmin); 
    program->setUniformValue("boundingBoxMax", BBmax);
    program->setUniformValue("modelViewProjectionMatrix", MVP); 

    if (drawPlugin()) drawPlugin()->drawScene();


    // Get texture
    g.glBindTexture(GL_TEXTURE_2D, textureId);  // Binddeo de la textura 2D textureID.
    g.glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);
    g.glGenerateMipmap(GL_TEXTURE_2D);

    // Pass 2. Draw quad using texture
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    program->bind();
    program->setUniformValue("colorMap", 0); 
    program->setUniformValue("SIZE", float(IMAGE_WIDTH));
    program->setUniformValue("invert", false); 
    program->setUniformValue("mirror", true); 
    program->setUniformValue("boundingBoxMin", BBmin); 
    program->setUniformValue("boundingBoxMax", BBmax);
    program->setUniformValue("modelViewProjectionMatrix", MVP); 

    float r = 80.0 * scene()->boundingBox().radius();
    float y = BBmin.y();


    drawQuad(Point(-r, y, r),
             Point( r, y, r),
             Point( r, y,-r),
             Point(-r, y,-r)); 

    
    // Pass 3. Draw std object
    program->bind();
    program->setUniformValue("invert", false); 
    program->setUniformValue("mirror", false); 
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    if (drawPlugin()) drawPlugin()->drawScene();

    g.defaultProgram()->bind();
    g.glBindTexture(GL_TEXTURE_2D, 0); 

    return true;
}


void Reflection::keyPressEvent(QKeyEvent *key)
{
    if (key->key() == Qt::Key_R) {
        onPluginLoad();
    }
} 


void Reflection::drawQuad(const Point& p0, const Point& p1, const Point& p2, const Point& p3)
{
    static bool created = false;
    static GLuint VAO_rect;
    GLWidget &g = *glwidget();
    g.makeCurrent();

    // 1. Create VBO Buffers
    if (!created)
    {
        created = true;        

        // Create & bind empty VAO
        g.glGenVertexArrays(1, &VAO_rect);
        g.glBindVertexArray(VAO_rect);

        // Create VBO with (x,y,z) coordinates
        float coords[] = { p0.x(), p0.y(), p0.z(), p1.x(), p1.y(), p1.z(), p3.x(), p3.y(), p3.z(), p2.x(), p2.y(), p2.z() };

        GLuint VBO_coords;
        g.glGenBuffers(1, &VBO_coords);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(0);
        //glBindVertexArray(0);

        float normals[] = { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0};

        GLuint VBO_normals;
        g.glGenBuffers(1, &VBO_normals);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
        g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(1);
        g.glBindVertexArray(0);
    }

    // 2. Draw
    g.glBindVertexArray(VAO_rect);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);
}