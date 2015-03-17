#include "escena.h"

Escena::Escena()
{
    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes
    capsaMinima.pmin[0] = 0; capsaMinima.pmin[1] = 0; capsaMinima.pmin[2]=0;
    capsaMinima.a = 1; capsaMinima.h = 1; capsaMinima.p = 1;

    taulaBillar = NULL;
    plaBase = NULL;
    blanca = NULL;
    boles = NULL;
}

Escena::~Escena()
{
    // Cal anar fent delete dels objectes que se'l hagi fet new
   delete this->taulaBillar;
   delete this->plaBase;
   delete this->blanca;
   delete this->boles;
}

void Escena::addObjecte(Objecte *obj) {
    if (dynamic_cast<TaulaBillar*>(obj)){
        this->taulaBillar = (TaulaBillar*)obj;
    } else if(dynamic_cast<PlaBase*> (obj)){
        this->plaBase = (PlaBase*)obj;
    } else if(dynamic_cast<Bola*> (obj)){
        this->blanca = (Bola*)obj;
    } else if(dynamic_cast<ConjuntBoles*> (obj)){
        this->boles = (ConjuntBoles*)obj;
    }
}


void Escena::CapsaMinCont3DEscena()
{
    // Metode a implementar
}

void Escena::aplicaTG(mat4 m) {

    // Metode a modificar

    if (taulaBillar!=NULL) taulaBillar->aplicaTG(m);
    if (plaBase!=NULL) plaBase->aplicaTG(m);
    if (blanca!=NULL) blanca->aplicaTG(m);
    if (boles!=NULL) boles->aplicaTG(m);
}

void Escena::aplicaTGCentrat(mat4 m) {

    // Metode a modificar

    if (taulaBillar!=NULL) taulaBillar->aplicaTGCentrat(m);
    if (plaBase!=NULL) plaBase->aplicaTGCentrat(m);
    if (blanca!=NULL) blanca->aplicaTGCentrat(m);
    if (boles!=NULL) boles->aplicaTGCentrat(m);
}

void Escena::draw() {

    // Metode a modificar

    if (taulaBillar!=NULL) taulaBillar->draw();
    if (plaBase!=NULL) plaBase->draw();
    if (blanca!=NULL) blanca->draw();
    if (boles!=NULL) blanca->draw();

}



