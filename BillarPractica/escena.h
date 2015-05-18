#ifndef ESCENA_H
#define ESCENA_H

#include <cmath>
#include <iostream>
#include <stdlib.h>

#include <list>
#include <vector>
#include <string>
#include <stdio.h>

#include <Common.h>
#include <objecte.h>
#include <taulabillar.h>
#include <plabase.h>
#include <bola.h>
#include <conjuntboles.h>
#include <camera.h>
#include <llum.h>

using namespace std;
enum normalType { FLAT, GOURAUD };

class Escena {

public:
    Escena();
    Escena(int ampladaViewport, int alcadaViewport, QGLShaderProgram *program);
    ~Escena();

    void addObjecte(Objecte *obj);
    void aplicaTG(mat4 m);
    void aplicaTGCentrat(mat4 m);
    void reset();

    void draw();
    void CapsaMinCont3DEscena();
    bool hasCollided(Objecte *obj);

    void iniCamera(bool camGeneral, int ampladaViewport, int alcadaViewport, QGLShaderProgram *program );
    void setAnglesCamera(bool camGeneral, float angX, float angY, float angZ);
    void setVRPCamera(bool camGeneral, point4 vrp);
    void setWindowCamera(bool camGeneral, bool retallat, Capsa2D window);
    void setDCamera(bool camGeneral, float d);
    void setAmbientToGPU(QGLShaderProgram *program);
    void calculaNormals(normalType type);

    // Capsa contenedora de l'escena
    Capsa3D capsaMinima;

    // Objectes de l'escena
    vector <Objecte*> elements;
    QGLShaderProgram* program;

    // Cameras de l'escena
    Camera* camGeneral;
    Camera* camFP;

    // Llum
    vec3 Ia;
    Llum* llum;

    // tipus de Normals
    normalType ntype = GOURAUD;
};

#endif // ESCENA_H
