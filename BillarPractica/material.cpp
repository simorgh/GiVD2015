#include "material.h"

Material::Material(vec3 ambient, vec3 diffuse, vec3 specular, float reflection) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->reflection = reflection;
}


void Material::toGPU(QGLShaderProgram *program) {
    gl_IdMaterial m;

    m.ambient = program->uniformLocation("material.ambient");
    m.specular = program->uniformLocation("material.specular");
    m.diffuse = program->uniformLocation("material.diffuse");
    m.reflection = program->uniformLocation("material.reflection");

    glUniform3fv(m.ambient, 1, this->ambient);
    glUniform3fv(m.specular, 1, this->specular);
    glUniform3fv(m.diffuse, 1, this->diffuse);
    glUniform1f(m.reflection, this->reflection);
}
