#include "taulabillar.h"

TaulaBillar::TaulaBillar(QString n) : Objecte(NumVerticesF)
{
    nom = n;
    Index = 0;
    tam = 1;

    xorig = 0;
    yorig = 0;
    zorig = 0;

    xRot = 0;
    yRot = 0;
    zRot = 0;

    readObj(n);

    Objecte::make();
    initTextura();
    capsa = calculCapsa3D();

    // Codi adhoc per a la taula carregada de fitxer taula.obj. Cal modificar-lo per a que sigui general
    double escalaZ = 2.0 / 8.63;
    mat4 m = Scale(escalaZ, escalaZ, escalaZ)*Translate(-2.55, +3.8, -0.74);
    //aplicaTG(Scale(escalaZ, escalaZ, escalaZ) * Translate(-2.55, +3.8, -0.74));
    aplicaTG(m);
    aplicaTGCentrat(Translate(0.,-0.524,0.));
    capsa = calculCapsa3D();
}

TaulaBillar::~TaulaBillar(){}
void TaulaBillar::initTextura(){
    qDebug() << "Taula - Initializing textures...";

    // Carregar la textura
    glActiveTexture(GL_TEXTURE0);
    texture = new QOpenGLTexture(QImage("://resources/Fabric_Green_L.jpg"));



}
