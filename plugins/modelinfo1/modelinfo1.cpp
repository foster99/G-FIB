#include "modelinfo1.h"
#include "glwidget.h"

void Modelinfo1::onPluginLoad()
{

    
}

void Modelinfo1::preFrame() // Este si
{
	
}

void Modelinfo1::postFrame() // Este tambien
{
    Scene* scn = scene();
    
    int numObj = scn -> objects().size();
    cout << "Number of Objects: " << numObj << endl;
    
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
        
        cout << "Objeto " << i++ << ":" << endl;
        cout << "# vertices: "   << numVert << endl;
        cout << "# poligonos: "  << numPoly << endl;
        cout << "% triangulos: " << perTri  << "%" << endl;
    } 
}

void Modelinfo1::onObjectAdd()
{
	
}

bool Modelinfo1::drawScene()
{
	return false; // return true only if implemented
}

bool Modelinfo1::drawObject(int)
{
	return false; // return true only if implemented
}

bool Modelinfo1::paintGL()
{
	return false; // return true only if implemented
}

void Modelinfo1::keyPressEvent(QKeyEvent *)
{
	
}

void Modelinfo1::mouseMoveEvent(QMouseEvent *)
{
	
}

