#include "escena.h"

Escena::Escena()
{
    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes
    capsaMinima.pmin[0] = 0; capsaMinima.pmin[1] = 0; capsaMinima.pmin[2]=0;
    capsaMinima.a = 1; capsaMinima.h = 1; capsaMinima.p = 1;
}

Escena::~Escena()
{
    // Cal anar fent delete dels objectes que se'l hagi fet new

    for(int i=0; i<elements.size(); i++){
        delete elements.at(i);
    }

}

void Escena::addObjecte(Objecte *obj) {
    elements.push_back(obj);
}


void Escena::CapsaMinCont3DEscena() {
    vec3 pmin = vec3(  99999,  99999,  99999);
    vec3 pmax = vec3( -99999, -99999, -99999);

    for(int i=0; i<elements.size(); i++){
        vec3 bmax = vec3( elements.at(i)->capsa.a + elements.at(i)->capsa.pmin.x,
                          elements.at(i)->capsa.h + elements.at(i)->capsa.pmin.y,
                          elements.at(i)->capsa.p + elements.at(i)->capsa.pmin.z);

        if( bmax.x > pmax.x) pmax.x = bmax.x;
        if( bmax.y > pmax.y) pmax.y = bmax.y;
        if( bmax.z > pmax.z) pmax.z = bmax.z;

        if(elements.at(i)->capsa.pmin.x < pmin.x) pmin.x = elements.at(i)->capsa.pmin.x;
        if(elements.at(i)->capsa.pmin.y < pmin.y) pmin.y = elements.at(i)->capsa.pmin.y;
        if(elements.at(i)->capsa.pmin.z < pmin.z) pmin.z = elements.at(i)->capsa.pmin.z;
    }

    capsaMinima.pmin = pmin;
    capsaMinima.a = pmax.x - pmin.x;
    capsaMinima.h = pmax.y - pmin.y;
    capsaMinima.p = pmax.z - pmin.z;
    //qDebug() << "Escena -> calculaCapsa3D:\n\tpmin: (" << pmin.x << "," << pmin.y << ","
    //         << pmin.z << ") \n\ta:" << capsaMinima.a << "\n\th:" << capsaMinima.h << "\n\tp:" << capsaMinima.p;
}

void Escena::aplicaTG(mat4 m) {

    // Metode a modificar

    for(int i=0; i<elements.size(); i++){
        elements.at(i)->aplicaTG(m);
    }
}

void Escena::aplicaTGCentrat(mat4 m) {

    // Metode a modificar

    vec3 centre = vec3(0.0, 0.0, 0.0);
    /*vec3 centre = vec3(capsaMinima.pmin.x + capsaMinima.a/2.,
                   capsaMinima.pmin.y + capsaMinima.h/2.,
                   capsaMinima.pmin.z + capsaMinima.p/2.);*/
    //qDebug() << "ESCENA centre( " << centre.x << "," << centre.y << "," << centre.z << ")";

    // Contrucció de la matriu de translació al centre
    mat4 t1 = Common::Translate(-centre.x, -centre.y, -centre.z);
    mat4 t2 = Common::Translate( centre.x,  centre.y,  centre.z);
    aplicaTG(t1*m*t2);
    CapsaMinCont3DEscena();
}

void Escena::draw() {

    // Metode a modificar

    for(int i=0; i<elements.size(); i++){
        elements.at(i)->draw();
    }

}



