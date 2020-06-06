#include "volume.h"
#include "glwidget.h"

void Volume::onPluginLoad()
{
	const auto& obj = (scene()->objects())[0];
    const auto& vertices = obj.vertices(); 

	float volume = 0;

    for (auto& face : obj.faces())
    {
        float cz, nz, a;
		
		Point v0,v1,v2;
		v0 = vertices[face.vertexIndex(0)].coord();
		v1 = vertices[face.vertexIndex(1)].coord();
		v2 = vertices[face.vertexIndex(2)].coord();

		// Calculo del area
        a = QVector3D::crossProduct(v1 - v0,v2 - v0).length()/2.0;

		// Componente Z del centroide
		cz = (v0 + v1 + v2).z()/3.0;

		// Componente Z de la nomrmal
		nz = face.normal().z();

		// Sumamos al volumen total el producto de los elementos
		volume += cz * nz * a;
    } 
    cout << "Volume: " << volume << endl; 
}
