#include<plabase.h>

PlaBase::PlaBase() : Objecte(NumVerticesF){
    qDebug() << "Constructor de PlaBase" << endl;

    xorig = 0;
    yorig = 0;
    zorig = 0;

    // Vertices of a unit plain centered at origin, sides aligned with axes
    vertices[0] = point4( -0.5, -0.5,  0.0, 1.0 );
    vertices[1] = point4( -0.5,  0.5,  0.0, 1.0 );
    vertices[2] = point4(  0.5,  0.5,  0.0, 1.0 );
    vertices[3] = point4(  0.5, -0.5,  0.0, 1.0 );

    vertexs.push_back(vertices[0]);
    vertexs.push_back(vertices[1]);
    vertexs.push_back(vertices[2]);
    vertexs.push_back(vertices[3]);

    // let's create both triangles that composes the plane
    cara1 = new Cara(0, 2, 1);
    cara2 = new Cara(0, 3, 2);

    cares.push_back(*cara1);
    cares.push_back(*cara2);

    Objecte::make();
    capsa = calculCapsa3D();

    // let's scale and translate the plane so it's position and lenght will be 18x15 y=0
    double escalaX = 18.;
    double escalaZ = 13.;
    aplicaTGCentrat( Scale(escalaX, 1., escalaZ) * RotateX(90) );

}

PlaBase::~PlaBase()
{
}
