#include "llum.h"

Llum::Llum(QString name,point4 position, point4 dir, GLfloat angle, GLfloat a, GLfloat b,
            GLfloat c, point3 ambient, point3 specular, point3 diffuse) {
    this->name = name;
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
    gl_IdLlum.position = program->uniformLocation(this->name + ".position");
    gl_IdLlum.dir = program->uniformLocation(this->name + ".dir");
    gl_IdLlum.angle = program->uniformLocation(this->name + ".angle");
    gl_IdLlum.a = program->uniformLocation(this->name + ".a");
    gl_IdLlum.b = program->uniformLocation(this->name + ".b");
    gl_IdLlum.c = program->uniformLocation(this->name + ".c");
    gl_IdLlum.ambient = program->uniformLocation(this->name + ".ambient");
    gl_IdLlum.diffuse = program->uniformLocation(this->name + ".diffuse");
    gl_IdLlum.specular = program->uniformLocation(this->name + ".specular");

    /* ----------------------------------------------
     * Bind de les zones de memoria que corresponen
     * ----------------------------------------------*/
    glUniform4fv(gl_IdLlum.position, 1, this->position);
    glUniform4fv(gl_IdLlum.dir, 1, this->dir);
    glUniform1f(gl_IdLlum.angle, this->angle);
    glUniform1f(gl_IdLlum.a, this->a);
    glUniform1f(gl_IdLlum.b, this->b);
    glUniform1f(gl_IdLlum.c, this->c);
    glUniform3fv(gl_IdLlum.ambient, 1, this->ambient);
    glUniform3fv(gl_IdLlum.diffuse, 1, this->diffuse);
    glUniform3fv(gl_IdLlum.specular, 1, this->specular);
}
