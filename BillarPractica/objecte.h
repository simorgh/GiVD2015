#ifndef OBJECTE_H
#define OBJECTE_H

#include <QObject>
#include <vector>
#include <Common.h>
#include <cara.h>
#include <QGLShaderProgram>
#include <QOpenGLTexture>
#include <material.h>

using namespace std;

typedef Common::vec4  point4;
typedef Common::vec2  texture2;

class Objecte : public QObject
{
    Q_OBJECT
protected:
    QString nom; // nom del fitxer on esta el cotxe
    vector<Cara> cares; // cares de l'objecte
    vector<point4> vertexs; // vertexs de l'objecte sense repetits

    // Sistema de coordenades d'un objecte: punt origen i eixos de rotació
    GLfloat xorig, yorig, zorig;
    float xRot;
    float yRot;
    float zRot;

    GLfloat tam; // Escala de l'objecte aplicada al fitxer d'entrada

    QOpenGLTexture *texture;
    GLuint buffer; // Buffer de comunicacio amb la GPU

    // Estructures de vertexs i colors per passar a la GPU
    int     numPoints;
    point4 *points;
    point4 *pointsTmp;
    point4 *normals;
    texture2 *vertexsTextura; // coordenades de textura associades a cada vertex

    int Index; // index de control del numero de vertexs a posar a la GPU


public:

    // Capsa mínima contenidora de l'objecte
    Capsa3D capsa;

    // Programa de shaders de la GPU
    QGLShaderProgram *program;
    Material *m;

    //explicit Objecte(QObject *parent = 0);
    Objecte(const int npoints, QObject *parent = 0);
    Objecte(const int npoints, QString n);
    ~Objecte();

    // llegeix un model en format OBJ
    virtual void readObj(QString filename);

    // make(): omple l'estructura de points i colors de l'objecte, inicialitza NumVertices
    // Si l'objecte es construeix procedimentalment es sobrecarrega el make
    virtual void make();

    // Pas generic de vertexs i colors a la GPU
    virtual void toGPU(QGLShaderProgram *p);

    // Pintat amb la GPU
    virtual void draw();

    // Calcula la capsa 3D contenidora de l'objecte
    virtual Capsa3D calculCapsa3D();

    // Aplica una TG qualsevol a un objecte
    virtual void aplicaTG(mat4 m);
    virtual void aplicaTGPoints(mat4 m);
    virtual void aplicaTGnormals(mat4 m);

    // Aplica una TG centrada en el punt central de la capsa de l'objecte a un objecte
    virtual void aplicaTGCentrat(mat4 m);
    virtual void initTextura() = 0; //abstract method to be overwritten to apply new texture on points
    virtual bool hasCollided(Objecte* obj);
    // Funciones necesarias para el movimiento de la bola (en caso de colisinar tenemos que recuperar los puntos anteriores)
    void backupPoints();
    void restorePoints();

private:
    void construeix_cara ( char **words, int nwords, Objecte*objActual, int vindexUlt);

protected:
    //virtual void calculaNormals(); //abstract method to be overwritten to compute vertex normals
};



#endif // OBJECTE_H
