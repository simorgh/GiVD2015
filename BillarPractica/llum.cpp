#include "llum.h"

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
    glUniform4fv(gl_IdLlum.posicio, 1, position);
    glUniform4fv(gl_IdLlum.dir, 1, dir);
    glUniform1f(gl_IdLlum.angle, angle);
    glUniform1f(gl_IdLlum.a, a);
    glUniform1f(gl_IdLlum.b, b);
    glUniform1f(gl_IdLlum.c, c);
    glUniform3fv(gl_IdLlum.ambient, 1, ambient);
    glUniform3fv(gl_IdLlum.diffuse, 1, diffuse);
    glUniform3fv(gl_IdLlum.specular, 1, specular);
}
