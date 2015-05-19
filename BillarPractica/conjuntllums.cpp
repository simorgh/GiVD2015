#include "conjuntllums.h"

ConjuntLlums::ConjuntLlums()
{}


void ConjuntLlums::toGPU(QGLShaderProgram* program){
    for (int i = 0; i< this->llums.size(); i++) llums[i]->toGPU(program);
}

void ConjuntLlums::addLight(Llum* l) {
    this->llums.push_back(l);
}
