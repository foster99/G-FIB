#include "animateVertices.h"
#include "glwidget.h"

void AnimateVertices::setVS() {
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs -> compileSourceFile("./animate-vertices1.vert");
    cout << "VS log:" << vs->log().toStdString() << endl;
}
 
void AnimateVertices::setFS() {
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs -> compileSourceFile("./animate-vertices1.frag"); 
    cout << "FS log:" << fs->log().toStdString() << endl;
}

void AnimateVertices::onPluginLoad() 
{
    setVS();
    setFS();
    
    // Link shaders to program
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;
    
    // Timer initialization
    elapsedTimer.start();
}

void AnimateVertices::preFrame()
{
    // Timer update
	float curr_time = float(elapsedTimer.elapsed()/1000.0f);
    
    // bind shader
    program->bind();
    
    // Send uniforms
    program->setUniformValue("time", curr_time);
    
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    
    QMatrix3x3 NM = camera()->viewMatrix().normalMatrix();
    program->setUniformValue("normalMatrix", NM); 
}

void AnimateVertices::postFrame()
{
	// unbind shader
    program->release(); 
}

void AnimateVertices::onObjectAdd()
{
	
}

bool AnimateVertices::drawScene()
{
	return false; // return true only if implemented
}

bool AnimateVertices::drawObject(int)
{
	return false; // return true only if implemented
}

bool AnimateVertices::paintGL()
{
	return false; // return true only if implemented
}

void AnimateVertices::keyPressEvent(QKeyEvent *)
{
	
}

void AnimateVertices::mouseMoveEvent(QMouseEvent *)
{
	
}

