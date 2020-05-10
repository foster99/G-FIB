#include "modelinfo2.h"
#include "glwidget.h"

void Modelinfo2::putText(int x, int y, QString text) {
    QFont font;
    font.setPixelSize(15);
    painter.begin(glwidget());
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(x,y,text);
    painter.end();
}

void Modelinfo2::onPluginLoad()
{

    
}

void Modelinfo2::preFrame() // Este si
{
	
}

void Modelinfo2::postFrame() // Este tambien
{
    Scene* scn = scene();
    
    int numObj = scn -> objects().size();
    
    float perTri;
    int numVert, numPoly, numTri, i = 0;
    
    for (auto& obj : scn -> objects()) {
        
        numTri = 0;
        for(auto& face : obj.faces()) {
            if (face.numVertices() == 3) ++numTri;
        }
        
        numVert = obj.vertices().size();
        numPoly = obj.faces().size();
        perTri = 100.0 * float(numTri)/float(numPoly);
        
        QString info =  QString("Objeto ") + QString::number(i) + QString(": ") +
                        QString("# vertices: ") + QString::number(numVert) + QString(" | ") +
                        QString("# poligonos: ") + QString::number(numPoly) + QString(" | ") +
                        QString("% triangulos: ") + QString::number(perTri);
        
        putText(20,35 + 15*i, info);


        ++i;
    } 
}

void Modelinfo2::onObjectAdd()
{
	
}

bool Modelinfo2::drawScene()
{
	return false; // return true only if implemented
}

bool Modelinfo2::drawObject(int)
{
	return false; // return true only if implemented
}

bool Modelinfo2::paintGL()
{
	return false; // return true only if implemented
}

void Modelinfo2::keyPressEvent(QKeyEvent *)
{
	
}

void Modelinfo2::mouseMoveEvent(QMouseEvent *)
{
	
}

