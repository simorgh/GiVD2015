#include "llum.h"

Llum::Llum(point4 position, point4 dir, GLfloat angle, GLfloat a, GLfloat b,
            GLfloat c, point3 ambient, point3 specular, point3 diffuse) {

    this->position = position;
    this->dir = dir;
    this->angle = angle;
    this->a = a;
    this->b = b;
    this->c = c;
    this->ambient = ambient;
    this->specular = specular;
    this->diffuse = diffuse;

}

void Llum::toGPU(QGLShaderProgram* program) {

    /* ----------------------------------------------
     * Obtencio dels identificadors de la GPU
     * ----------------------------------------------*/
    gl_IdLlum.posicio = program->uniformLocation("tipusLlum.posicio");
    gl_IdLlum.dir = program->uniformLocation("tipusLlum.dir");
    gl_IdLlum.angle = program->uniformLocation("tipusLlum.angle");
    gl_IdLlum.a = program->uniformLocation("tipusLlum.a");
    gl_IdLlum.b = program->uniformLocation("tipusLlum.b");
    gl_IdLlum.c = program->uniformLocation("tipusLlum.c");
    gl_IdLlum.ambient = program->uniformLocation("tipusLlum.ambient");
    gl_IdLlum.diffuse = program->uniformLocation("tipusLlum.diffuse");
    gl_IdLlum.specular = program->uniformLocation("tipusLlum.specular");

    /* ----------------------------------------------
     * Bind de les zones de memoria que corresponen
     * ----------------------------------------------*/
    glUniform4fv(gl_IdLlum.posicio, 1, this->position);
    glUniform4fv(gl_IdLlum.dir, 1, this->dir);
    glUniform1f(gl_IdLlum.angle, this->angle);
    glUniform1f(gl_IdLlum.a, this->a);
    glUniform1f(gl_IdLlum.b, this->b);
    glUniform1f(gl_IdLlum.c, this->c);
    glUniform3fv(gl_IdLlum.ambient, 1, this->ambient);
    glUniform3fv(gl_IdLlum.diffuse, 1, this->diffuse);
    glUniform3fv(gl_IdLlum.specular, 1, this->specular);
}
