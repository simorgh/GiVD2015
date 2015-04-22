#include "escena.h"

Escena::Escena(int a, int h, QGLShaderProgram *program)
{
    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes
    capsaMinima.pmin[0] = 0; capsaMinima.pmin[1] = 0; capsaMinima.pmin[2]=0;
    capsaMinima.a = 1; capsaMinima.h = 1; capsaMinima.p = 1;
    iniCamera(true, a, h, program);
}

Escena::~Escena()
{
    // Cal anar fent delete dels objectes que se'l hagi fet new
    elements.clear();

}

void Escena::addObjecte(Objecte *obj) {
    elements.push_back(obj);
    CapsaMinCont3DEscena();

    // iniCamera(true, capsaMinima.a, capsaMinima.h, program);
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
}

void Escena::aplicaTG(mat4 m) {
    // Metode a modificar

    for(int i=0; i<elements.size(); i++){
        elements.at(i)->aplicaTG(m);
    }
}

void Escena::aplicaTGCentrat(mat4 m) {
    // Metode a modificar

    vec3 centre = vec3(capsaMinima.pmin.x + capsaMinima.a/2.,
                   capsaMinima.pmin.y + capsaMinima.h/2.,
                   capsaMinima.pmin.z + capsaMinima.p/2.);
    //qDebug() << "ESCENA centre( " << centre.x << "," << centre.y << "," << centre.z << ")";

    // Contrucció de la matriu de translació al centre
    mat4 t1 = Common::Translate(-centre.x, -centre.y, -centre.z);
    mat4 t2 = Common::Translate( centre.x,  centre.y,  centre.z);
    aplicaTG(t2*m*t1);

   //CapsaMinCont3DEscena();
}

void Escena::draw() {

    // Metode a modificar
    for(int i=0; i<elements.size(); i++){
        elements.at(i)->draw();
    }

}

bool Escena::hasCollided(Objecte *obj){

    // horizontal (x-axis)
    if(obj->capsa.pmin.x <= capsaMinima.pmin.x)  return true;
    if( (obj->capsa.pmin.x + obj->capsa.a) > (capsaMinima.pmin.x + capsaMinima.a) ) return true;

    // vertical (z-axis)
    if(obj->capsa.pmin.y <= capsaMinima.pmin.z){
        //qDebug() << obj->capsa.pmin.z << capsaMinima.pmin.z;
        return true;
    }
    if( (obj->capsa.pmin.y + obj->capsa.h) > (capsaMinima.pmin.z + capsaMinima.p) ){
        //qDebug() << obj->capsa.pmin.y + obj->capsa.h << capsaMinima.pmin.z + capsaMinima.p;
        return true;
    }
    return false;
}


void iniCamera(bool camGeneral, int ampladaViewport, int alcadaViewport, QGLShaderProgram *program){
  /*
   * Si el valor del paràmetre és cert, s'inicialitza la càmera general de l'escena. En cas
   * contrari s'inicialitza la càmera en primera persona.
   */

    if(camGeneral){
        this.camGeneral = new Camera();
        this.camGeneral->ini(a, h, capsaMinima);
    } else {
        //TODO: Camera primera Persona
    }

}

void setAnglesCamera(bool camGeneral, float angX, float angY, float angZ){
    /*
     *  Si el valor del paràmetre és cert, es canvien la posició de la càmera general de
     *  l'escena segons els angles d'entrada. Cal actualitzar els atributs que calguin per a
     *  deixar coherent tota la informació de la càmera.
     */
}

void setVRPCamera(bool camGeneral, point4 vrp){
    /*
     * Si el valor del paràmetre és cert, es canvien el punt on enfoca la càmera general de
     * l'escena segons el punt d'entrada. Cal actualitzar els atributs que calguin per a deixar
     * coherent tota la informació de la càmera.
     */
}

void setWindowCamera(bool camGeneral, bool retallat, Capsa2D window){
    /*
    * Si el valor del paràmetre és cert, es canvia la window de la càmera general i tots els
    * atributs depenents d'aquest canvi.
    */
}

void setDCamera(bool camGeneral, float d){
    /*
     * Si el valor del paràmetre és cert, es canvia la distància de la càmera general al pla de
     *projecció i tots els atributs depenents d'aquest canvi.
     */
}



