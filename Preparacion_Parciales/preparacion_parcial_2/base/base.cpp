#include "base.h"
#include "glwidget.h"

void Base::onPluginLoad()
{
    const auto& obj = (scene()->objects())[0];
    const auto& vertices = obj.vertices();

    float auxY, minY, center = obj.boundingBox().center().y(); 
	float area = 0;

    for (auto& face : obj.faces())
    {
        
        // Calcular el vertice mas bajo y comprobar si este esta por debajo
        minY = vertices[face.vertexIndex(0)].coord().y();
        for (int v = 1; v < face.numVertices(); ++v){
            auxY = vertices[face.vertexIndex(v)].coord().y();
            if (auxY < minY) minY = auxY;
        }

        if (minY < center) {
            auto& u = vertices[face.vertexIndex(1)].coord() - vertices[face.vertexIndex(0)].coord();
            auto& v = vertices[face.vertexIndex(2)].coord() - vertices[face.vertexIndex(0)].coord();
            area += sqrt(QVector3D::crossProduct(u,v).lengthSquared())/2.0;
        } 

    } 
    cout << "Area: " << area << endl; 
}
