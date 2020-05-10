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

#include "drawSmooth.h"
#include "glwidget.h"
#include <cassert>
#include <cmath>

DrawVBOng::~DrawVBOng() {
	cleanUp();
}

void DrawVBOng::onSceneClear()
{
	cleanUp();
}

void DrawVBOng::cleanUp()
{
	GLWidget &g = *glwidget();
	g.glDeleteBuffers(coordBuffers.size(),  &coordBuffers[0]);
	g.glDeleteBuffers(normalBuffers.size(), &normalBuffers[0]);
	g.glDeleteBuffers(stBuffers.size(),  &stBuffers[0]);
	g.glDeleteBuffers(colorBuffers.size(),  &colorBuffers[0]);
	g.glDeleteBuffers(indicesBuffers.size(),  &indicesBuffers[0]);
	g.glDeleteVertexArrays(VAOs.size(), &VAOs[0]);
	coordBuffers.clear();
	normalBuffers.clear();
	stBuffers.clear();
	colorBuffers.clear();
	indicesBuffers.clear();
	VAOs.clear();
	numIndices.clear();
}

bool DrawVBOng::drawObject(int i)
{
	GLWidget &g = *glwidget();
	g.makeCurrent();
	g.glBindVertexArray(VAOs[i]);
	// g.glDrawElements(GL_TRIANGLES, #indices que necesitas, tipo_del_indice, puntero);
	g.glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, 0);
	g.glBindVertexArray(0);
	return true;
}

bool DrawVBOng::drawScene()
{
	GLWidget &g = *glwidget();
	g.makeCurrent();
	for(unsigned int i=0; i < VAOs.size(); i++) // for each buffer (that is, for each object)
		drawObject(i);
	return true;
}

void DrawVBOng::onPluginLoad()
{
	for(unsigned int i=0; i<scene()->objects().size(); i++)
		addVBO(i);
}

void DrawVBOng::onObjectAdd()
{
	addVBO( scene()->objects().size() - 1 );
}

void DrawVBOng::addVBO(unsigned int currentObject)
{
	const Object& obj = scene()->objects()[currentObject];
	
	// 1. Para cada face del objeto, tengo que guardarme la normal asociada a cada
	// vertice para despues hacer una media (solo guardo una normal por vertice)
	const int realNumVertices = obj.vertices().size();
	vector<Vector> normalSum(realNumVertices);
	vector<uint> normalCount(realNumVertices);
	vector<Vector> normalAvg(realNumVertices);
	
	for (auto&& f: obj.faces()) {               // Para cada cara
		for (int i = 0; i < f.numVertices(); ++i) { // Para cada vertice
			
			const auto index = f.vertexIndex(i);
			
			normalSum[index] += f.normal().normalized();
			++normalCount[index];
		}
	}
	
	// 2. Calculamos las medias de todas las normales 
	for(int i = 0; i < realNumVertices; ++i) {
		normalAvg[i] = normalSum[i]/float(normalCount[i]);
	}
	
	// 3. Creamos una entrada de VBO para cada vertice.
	vector<float> vertices;
	vector<float> texCoords;
	vector<float> normals;
	vector<float> colors;
	
	for(int i = 0; i < realNumVertices; ++i) {
		
		const auto& P  = obj.vertices()[i].coord();
		const auto& N  = normalAvg[i];
		const auto& TC = obj.vertTexCoords()[i];
		
		// coordenadas
		vertices.push_back(P.x());
		vertices.push_back(P.y());
		vertices.push_back(P.z());
		
		// normal
		normals.push_back(N.x());
		normals.push_back(N.y());
		normals.push_back(N.z());
		
		// color
		colors.push_back(fabs(N.x()));
		colors.push_back(fabs(N.y()));
		colors.push_back(fabs(N.z()));
		
		// texture Coords
		texCoords.push_back(TC.first); 
		texCoords.push_back(TC.second);
	}
	
	// 4. Creamos la lista de indices de los vertices segun aparecen en el modelo
	vector<GLuint> indices;
	for (auto&& face: obj.faces()) {
		for (int i = 0; i < face.numVertices(); ++i) {
			indices.push_back(face.vertexIndex(i));
		}
	}
	
	// 5. Creamos VAO y VBOs vacios para cada caracteristica
	GLWidget& g = *glwidget();
	
	GLuint VAO;
	g.glGenVertexArrays(1, &VAO);
	VAOs.push_back(VAO);
	g.glBindVertexArray(VAO);

	GLuint coordBufferID;
	g.glGenBuffers(1, &coordBufferID);
	coordBuffers.push_back(coordBufferID);

	GLuint normalBufferID;
	g.glGenBuffers(1, &normalBufferID);
	normalBuffers.push_back(normalBufferID);

	GLuint stBufferID;
	g.glGenBuffers(1, &stBufferID);
	stBuffers.push_back(stBufferID);

	GLuint colorBufferID;
	g.glGenBuffers(1, &colorBufferID);
	colorBuffers.push_back(colorBufferID);
	
	GLuint indicesBufferID;
	g.glGenBuffers(1, &indicesBufferID);
	indicesBuffers.push_back(indicesBufferID);
	
	// 6. Hay que poner el TOTAL de vertices a pintar, es decir, contando las
	// repeticiones en cada cara.
	numIndices.push_back(indices.size()); 
	
	// 7. Introducimos datos a los VBOs
	g.glBindBuffer(GL_ARRAY_BUFFER, coordBufferID);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
	g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	g.glEnableVertexAttribArray(0);

	g.glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normals.size(), &normals[0], GL_STATIC_DRAW);
	g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	g.glEnableVertexAttribArray(1);

	g.glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*colors.size(), &colors[0], GL_STATIC_DRAW);
	g.glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	g.glEnableVertexAttribArray(2);

	g.glBindBuffer(GL_ARRAY_BUFFER, stBufferID);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
	g.glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
	g.glEnableVertexAttribArray(3);
	
	g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferID);
	g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indices.size(), &indices[0], GL_STATIC_DRAW);

	g.glBindBuffer(GL_ARRAY_BUFFER,0);
	g.glBindVertexArray(0);
}
