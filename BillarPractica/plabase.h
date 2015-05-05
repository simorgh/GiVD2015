#ifndef PLABASE
#define PLABASE

#include <objecte.h>

class PlaBase : public Objecte
{

public:
    PlaBase();
    ~PlaBase();

private:
    static const int NumVerticesF = 12; //(1 face)(2 triangles/face)(3 vertex/triangle) * 2 cares
    //static const int NumCares = 2;

    //Cara *cara1, *cara2;
    point4 vertices[4]; // 4 vertexs del plaBase
    //color4 vertex_colors[4]; // 4 colors RGBA associats a cada vertex

    void make();
    void quad(int a, int b, int c, int d);
    void initTextura();
};

#endif // PLABASE_H

