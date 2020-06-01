#ifndef _BASE_H
#define _BASE_H

#include "plugin.h" 
#include <QVector3D>
#include <QtMath>

class Base: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();

  private:
	// add private methods and attributes here
};

#endif
