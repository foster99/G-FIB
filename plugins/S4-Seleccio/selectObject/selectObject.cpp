#include "selectObject.h"
#include "glwidget.h"

#define FILENAME "selectObject"
#define SHADERS_PATH "./selectObject"

void SelectObject::recompileShaders()
{
	GLWidget &g = *glwidget();
	g.makeCurrent();
	vs->compileSourceFile(g.getPluginPath() + "/../" + QString(FILENAME) + "/" + QString(SHADERS_PATH) + QString(".vert"));
	fs->compileSourceFile(g.getPluginPath() + "/../" + QString(FILENAME) + "/" + QString(SHADERS_PATH) + QString(".frag"));
	program->link();
}

void SelectObject::setShaders()
{
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile(QString(SHADERS_PATH) + QString(".vert"));
	cout << "VS log:" << vs->log().toStdString() << endl;

	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile(QString(SHADERS_PATH) + QString(".frag"));
	cout << "FS log:" << fs->log().toStdString() << endl;

	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();

	cout << "Link log:" << program->log().toStdString() << endl;
	if (!program->isLinked())
		cout << "Shader link error" << endl;
}

void SelectObject::onPluginLoad()
{
	// Link shaders to program
	setShaders();

	// Controla la creacion de los Buffers de las BoundingBoxes
	created = false;
}

void SelectObject::keyPressEvent(QKeyEvent *event)
{
	int obj = -1;
	int n = scene()->objects().size();

	switch (event->key())
	{
	case Qt::Key_R:
		recompileShaders();
		cout << "Los shaders se han recompilado!!" << endl;
		break;
	case Qt::Key_0:
		obj = 0;
		break;
	case Qt::Key_1:
		obj = 1;
		break;
	case Qt::Key_2:
		obj = 2;
		break;
	case Qt::Key_3:
		obj = 3;
		break;
	case Qt::Key_4:
		obj = 4;
		break;
	case Qt::Key_5:
		obj = 5;
		break;
	case Qt::Key_6:
		obj = 6;
		break;
	case Qt::Key_7:
		obj = 7;
		break;
	case Qt::Key_8:
		obj = 8;
		break;
	case Qt::Key_9:
		obj = 9;
		break;
	default:
		break;
	}

	if (obj > -1) {
		if (obj < n) {
			scene() -> setSelectedObject(obj);
			cout << "Has seleccionado el objeto: " << scene() -> selectedObject() << endl;
		}
		else {
			scene() -> setSelectedObject(-1);
			cout << "Se ha deseleccionado el objeto." << endl;
		}
	}
}

void SelectObject::encodeID(unsigned int i, GLubyte* color) {

	color[0] = i%256;
	color[1] = (i/256)%256;
	color[2] = (i/(256*256))%256;
	color[3] = 1.0; 
}

unsigned int SelectObject::decodeID(GLubyte* color) {
	return color[0] + (256*color[1]) + (256*256*color[2]);
}

void SelectObject::mouseReleaseEvent(QMouseEvent *event)
{
	bool selection_mode = 	   (event->button()    & Qt::RightButton    )
						  and !(event->modifiers() & Qt::ShiftModifier  )
						  and  (event->modifiers() & Qt::ControlModifier);
	
	
	if (selection_mode) {

		GLWidget &g = *glwidget();
		g.makeCurrent();

		g.glClearColor(1,1,1,1);
    	g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		program->bind();

		QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
		program->setUniformValue("modelViewProjectionMatrix", MVP);

		program->setUniformValue("selection", true);

		// per cada objecte 
		for (unsigned int i = 0; i < scene()->objects().size(); ++i)
		{
			GLubyte color[4];
			encodeID(i, color); // trieu la conversió que volgueu
			program->setUniformValue("color", QVector4D(color[0] / 255.0,
														 color[1] / 255., color[2] / 255., 1.0));
			drawPlugin()->drawObject(i);
		}

		int x = event->x();
		int y = glwidget()->height() - event->y();
		
		GLubyte read[4];
		glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);

		// cout <<"color: (" << int(read[0]) <<',' << int(read[1]) <<',' << int(read[2]) <<") --> " << decodeID(read) << endl;
		int objectID = decodeID(read);

		if (objectID < 16777215) {
			scene() -> setSelectedObject(objectID);
			cout << "Has seleccionado el objeto: " << scene() -> selectedObject() << endl;
		}
		else {
			scene() -> setSelectedObject(-1);
			cout << "Se ha deseleccionado el objeto." << endl;
		}

		g.update();
	}
}

void SelectObject::preFrame()
{
	program->bind();
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", MVP);
	program->setUniformValue("selection", false); 
}

void SelectObject::computeBoundingBox(const int objectID) {
    
    GLWidget &g = *glwidget();
    g.makeCurrent();
    
    Scene* scn=scene();
    const auto& objects = scn -> objects();
    const auto& obj  = objects[objectID];

	programBB->bind();

	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
	programBB->setUniformValue("modelViewProjectionMatrix", MVP);
    programBB->setUniformValue("boundingBoxMin", obj.boundingBox().min());
    programBB->setUniformValue("boundingBoxMax", obj.boundingBox().max());
        
    g.glBindVertexArray(VAO_bb);              // Seleccionamos el VAO
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 14); // Establecemos modo interpretacion
    g.glBindVertexArray(0); 
}

void SelectObject::creaBuffers() {
    
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

void SelectObject::compileBBShaders() {

	GLWidget &g = *glwidget();
    g.makeCurrent();

	vsBB = new QOpenGLShader(QOpenGLShader::Vertex, this);
	fsBB = new QOpenGLShader(QOpenGLShader::Fragment, this);
	vsBB->compileSourceFile(g.getPluginPath() + "/../" + QString(FILENAME) + "/" + QString("drawBoundingBox") + QString(".vert"));
	fsBB->compileSourceFile(g.getPluginPath() + "/../" + QString(FILENAME) + "/" + QString("drawBoundingBox") + QString(".frag"));

	programBB = new QOpenGLShaderProgram(this);
	programBB->addShader(vsBB);
	programBB->addShader(fsBB);
	programBB->link();
	
	cout << "Link log:" << program->log().toStdString() << endl;
	if (!program->isLinked())
		cout << "Shader link error" << endl;
}

void SelectObject::postFrame()
{	
	
	program->release();
	
	const int seleccionat = scene() -> selectedObject();

	if (seleccionat >= 0) {

		
		GLWidget &g = *glwidget();
    	g.makeCurrent();

		if(!created) {
			created = true;
			creaBuffers();
			compileBBShaders();
		}

		g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  
    
        // 3. Pintamos con el nuevo modo
        computeBoundingBox(seleccionat);
		
        // 4. Restablecemod modo de pintado anterior
        g.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    	// unbind shader
    	programBB->release(); 
	}
	
}