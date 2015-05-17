#ifndef LLUM_H
#define LLUM_H

#define PUNTUAL 0
#define DIRECCIONAL 1
#define SPOT 2

#include <Common.h>
#include <QGLShaderProgram>

typedef Common::vec4  point4;
typedef Common::vec3  point3;

using namespace std;

struct {
    GLuint position;
    GLuint dir;
    GLuint angle;
    GLuint a,b,c;
    GLuint ambient;
    GLuint specular;
    GLuint diffuse;
} gl_IdLlum;

class Llum {
    public:
        Llum( point4 position, point4 dir, GLfloat angle, GLfloat a, GLfloat b,
              GLfloat c, point3 ambient, point3 specular, point3 diffuse);

        point4 position;//per a la puntual y  spot
        point4 dir; //per a la direccional y spot
        GLfloat angle;
        GLfloat a,b,c;
        point3 ambient; //això són colors rgb
        point3 specular;
        point3 diffuse;

        void toGPU(QGLShaderProgram*);
};

#endif // LLUM_H
