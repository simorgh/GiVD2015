#ifndef BOLA
#define BOLA

#include <objecte.h>
#include <vec.h>
#include <math.h>
#include <sstream>

class Bola: public Objecte
{

public:
    static const int NumVerticesF = 3072; //12 * 4^(NumIteracionsEsfera)
    static const float scaleFactor = 0.35;

    Bola();
    Bola(int id, double x, double z); // Constructor defined for ConjuntBoles impl.
    ~Bola();

private:
    static const int NumIteracionsEsfera = 4;
    int id; // Bola id. Determines which ball is. Used to load texture and set it's position

    point4 v[4] = {
        vec4(0.0, 0.0, 1.0, 1.0),
        vec4(0.0, 0.942809, -0.333333, 1.0),
        vec4(-0.816497, -0.471405, -0.333333, 1.0),
        vec4(0.816497, -0.471405, -0.333333, 1.0)
    };

    void triangle(const point4 &a, const point4 &b, const point4 &c);
    void tetrahedron();
    void tetrahedron(int n);
    void divide_triangle(point4 a, point4 b, point4 c, int n);
    vec4 calculVectorUnitari(const vec4& v );
    void initTextura();

    vec2 calculTexturaCoord(const vec4 &v);
};
#endif // BOLA

