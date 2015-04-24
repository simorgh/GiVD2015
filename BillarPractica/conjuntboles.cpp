#include<conjuntboles.h>

ConjuntBoles::ConjuntBoles() : Objecte(0){
    ConjuntBoles::make();
    capsa = this->calculCapsa3D();
}

ConjuntBoles::~ConjuntBoles(){
    for(int i=0; i<NumBoles; i++) delete boles[i];
}

void ConjuntBoles::make(){
    //qDebug() << "ConjuntBoles -> make()";
    int count = 0;
    float z = 1;
    for(int i=0; i<5; i++){  // each row
        float aux = i;
        for(int it = 0; it <= i; it++){ // iter. balls per row
            boles[count] = new Bola(count+1, aux, z);
            //qDebug() << "new Bola " << count+1 << aux << z;
            count++;
            aux-=2;
         }
        z+=2;
    }

    this->aplicaTGCentrat( Scale(Bola::scaleFactor, Bola::scaleFactor, Bola::scaleFactor) );
    this->aplicaTGCentrat( Translate(0. ,0. ,3.) );
}

void ConjuntBoles::toGPU(QGLShaderProgram *pr){
    //qDebug() << "ConjuntBoles -> toGPU()";
    for(int i=0; i<NumBoles; i++) boles[i]->toGPU(pr);
}

void ConjuntBoles::draw(){
    //qDebug() << "ConjuntBoles -> draw()";
    for(int i=0; i<NumBoles; i++) boles[i]->draw();
}

void ConjuntBoles::aplicaTG(mat4 m){
    //qDebug() << "ConjuntBoles -> aplicaTG";
    for(int i=0; i<NumBoles; i++) boles[i]->aplicaTG(m);
}

void ConjuntBoles::aplicaTGPoints(mat4 m){
    //qDebug() << "ConjuntBoles -> aplicaTGPoints";
    for(int i=0; i<NumBoles; i++){
        boles[i]->aplicaTGPoints(m);
    }
}

void ConjuntBoles::aplicaTGCentrat(mat4 m){
    //qDebug() << "ConjuntBoles -> aplicaTGCentrat";
    vec3 centre = vec3(capsa.pmin.x + capsa.a/2.,
                       capsa.pmin.y + capsa.h/2.,
                       capsa.pmin.z + capsa.p/2.);
    //qDebug() << "ConjuntBoles centre( " << centre.x << "," << centre.y << "," << centre.z << ")";

    // Contrucció de la matriu de translació al centre
    mat4 t1 = Common::Translate(-centre.x, -centre.y, -centre.z);
    mat4 t2 = Common::Translate( centre.x,  centre.y,  centre.z);
    aplicaTG(t2*m*t1);
    this->capsa = this->calculCapsa3D();
}

Capsa3D ConjuntBoles::calculCapsa3D(){
    // Metode a implementar: calcula la capsa mínima contenidora d'un objecte
    Capsa3D c;
    vec3 pmin = vec3(  99999,  99999,  99999);
    vec3 pmax = vec3( -99999, -99999, -99999);

    for(int i=0; i<NumBoles; i++){
        vec3 bmax = vec3( boles[i]->capsa.a + boles[i]->capsa.pmin.x,
                          boles[i]->capsa.h + boles[i]->capsa.pmin.y,
                          boles[i]->capsa.p + boles[i]->capsa.pmin.z);

        if( bmax.x > pmax.x) pmax.x = bmax.x;
        if( bmax.y > pmax.y) pmax.y = bmax.y;
        if( bmax.z > pmax.z) pmax.z = bmax.z;

        if(boles[i]->capsa.pmin.x < pmin.x) pmin.x = boles[i]->capsa.pmin.x;
        if(boles[i]->capsa.pmin.y < pmin.y) pmin.y = boles[i]->capsa.pmin.y;
        if(boles[i]->capsa.pmin.z < pmin.z) pmin.z = boles[i]->capsa.pmin.z;
    }

    c.pmin = pmin;
    c.a = pmax.x - pmin.x;
    c.h = pmax.y - pmin.y;
    c.p = pmax.z - pmin.z;
    return c;
}

void ConjuntBoles::initTextura(){}
