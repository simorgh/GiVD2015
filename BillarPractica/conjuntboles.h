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

private:
    static const int NumBoles = 15;
    vector <Bola> boles;

    void make();
    Capsa3D calculCapsa3D();

};

#endif // CONJUNTBOLES

