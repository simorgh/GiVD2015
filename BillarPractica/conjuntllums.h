#ifndef CONJUNTLLUMS_H
#define CONJUNTLLUMS_H
#include <vector>
#include "llum.h"
#include "Common.h"

using namespace std;

class ConjuntLlums
{
public:    
    ConjuntLlums();
    void toGPU(QGLShaderProgram* program);
    void addLight(Llum* l);

    //vector de llums
    vector<Llum*> llums;
};

#endif // CONJUNTLLUMS_H
