#ifndef MATERIAL_H

#define MATERIAL_H

#include <Common.h>
#include <QGLShaderProgram>

typedef Common::vec3  point3;

using namespace std;

struct gl_IdMaterial{
    GLuint ambient;
    GLuint diffuse;
    GLuint specular;
    GLuint reflection;
};

class Material {

public:
    Material(vec3 ambient, vec3 diffuse, vec3 specular, float reflection);
    void toGPU(QGLShaderProgram*);
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float reflection;

private:


};

#endif // MATERIAL_H
