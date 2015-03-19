#ifndef CONJUNTBOLES
#define CONJUNTBOLES


#include <objecte.h>
#include <bola.h>
#include <vec.h>
#include <vector>
#include <math.h>

class ConjuntBoles : public Objecte
{

public:
    ConjuntBoles();
    ~ConjuntBoles();

    void make();
    void draw();

    void toGPU(QGLShaderProgram *pr);
    void aplicaTG(mat4 m);
    void aplicaTGPoints(mat4 m);
    void aplicaTGCentrat(mat4 m);

    Capsa3D calculCapsa3D();

private:
    static const int NumBoles = 15;
    Bola* boles[NumBoles];

};

#endif // CONJUNTBOLES

