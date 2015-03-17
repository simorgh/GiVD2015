#include<conjuntboles.h>

ConjuntBoles::ConjuntBoles() : Objecte(){ //Objecte(NumBoles * Bola::NumVerticesF){
    ConjuntBoles::make();
    //tetrahedron(NumIteracionsEsfera);
    //capsa = calculCapsa3D();
    //aplicaTGCentrat( Translate(-5.0, 1.0, 0.0)*Scale(0.25, 0.25, 0.25) ); // place the sphere over the plane and fit size to ratio
}

ConjuntBoles::~ConjuntBoles(){}


void ConjuntBoles::make(){

    Bola* b0 = new Bola(9, 4);
    Bola* b1 = new Bola(9, 2);
    Bola* b2 = new Bola(9, 0);
    Bola* b3 = new Bola(9, -2);
    Bola* b4 = new Bola(9, -4);

/*
    int count = 0;
    for(float x=9.; x>= 1.; x-=2){
        for(float y=4.; y>=0.; y--){
            for (float z=y; z >=-y; z-=2){
                Bola* b = new Bola(x, z);
                //boles.push_back(*b);
                count++;
            }
        }
    }
*/
}

Capsa3D ConjuntBoles::calculCapsa3D(){

}




