#include "showDegree.h"
#include "glwidget.h"

void ShowDegree::putText(int x, int y, QString text) {
    QFont font;
    font.setPixelSize(32);
    painter.begin(glwidget());
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(x,y,text);
    painter.end();
}

void ShowDegree::onPluginLoad()
{
    const Object& obj = (scene() -> objects())[0];
    
    float total_degree = 0;
    float total_vert   = obj.vertices().size();
    
    for (const auto& face : obj.faces())
        total_degree += face.numVertices();
    
    avg_degree = total_degree/total_vert;
    
    cout << total_degree/total_vert << endl;
    
//     // Version para autistas que no piensan
//
//     float avg, total_degree = 0, total_vert = obj.vertices().size();
//     
//     vector<int> counters(total_vert, 0);
//     
//     for (const auto& face : obj.faces())
//         for (int j = 0; j < face.numVertices(); ++j)
//                 counters[face.vertexIndex(j)]++;
//             
//     for (const auto& degree : counters)
//         total_degree += degree;
//     
//     avg = total_degree/total_vert;
//     cout << avg << endl; 
    
}

void ShowDegree::preFrame()
{

}

void ShowDegree::postFrame()
{
    putText(20, 50, QString("Average Degree: ") + QString::number(avg_degree));
}

void ShowDegree::onObjectAdd()
{
	
}

bool ShowDegree::drawScene()
{
	return false; // return true only if implemented
}

bool ShowDegree::drawObject(int)
{
	return false; // return true only if implemented
}

bool ShowDegree::paintGL()
{
	return false; // return true only if implemented
}

void ShowDegree::keyPressEvent(QKeyEvent *)
{
	
}

void ShowDegree::mouseMoveEvent(QMouseEvent *)
{
	
}

