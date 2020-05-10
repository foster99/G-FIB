#ifndef _DRAWBOUNDINGBOX_H
#define _DRAWBOUNDINGBOX_H

#include "plugin.h" 

class DrawBoundingBox: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void postFrame();
     
  private:
     // Shaders
	 QOpenGLShaderProgram* program;
     QOpenGLShader *fs, *vs; 
     
     void computeBoundingBox();
     void creaBuffers();
     
     bool created; 
     GLuint VAO_bb;
     GLuint VBO_coords;
     GLuint VBO_colors;
     
     void setVS();
     void setFS();
};

#endif
