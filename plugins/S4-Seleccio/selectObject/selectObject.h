#ifndef _SELECTOBJECT_H
#define _SELECTOBJECT_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class SelectObject: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

	 void setShaders();
	 void recompileShaders();

	 void creaBuffers();
	 void computeBoundingBox(const int);
	 void compileBBShaders();

	 void mouseReleaseEvent(QMouseEvent *);
	 void keyPressEvent(QKeyEvent *);
	 void encodeID(unsigned int, GLubyte*);

	 unsigned int decodeID(GLubyte* color);

  private:

	QOpenGLShaderProgram* program;
	QOpenGLShaderProgram* programBB;
    QOpenGLShader* vs;
    QOpenGLShader* fs;
	QOpenGLShader* vsBB;
    QOpenGLShader* fsBB; 

	bool created; 
    GLuint VAO_bb;
    GLuint VBO_coords;
    GLuint VBO_colors;
};

#endif
