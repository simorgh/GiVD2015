#include<conjuntboles.h>

ConjuntBoles::ConjuntBoles() : Objecte(){
    ConjuntBoles::make();
    ConjuntBoles::calculCapsa3D();
}

ConjuntBoles::~ConjuntBoles(){
    for(int i=0; i<NumBoles; i++) delete boles[i];
}

void ConjuntBoles::make(){
    qDebug() << "ConjuntBoles -> make()";

    boles[0] = new Bola(1, 9, 4);
    boles[1] = new Bola(2, 9, 2);
    boles[2] = new Bola(3, 9, 0);
    boles[3] = new Bola(4, 9, -2);
    boles[4] = new Bola(5, 9, -4);
    boles[5] = new Bola(6, 7, 3);
    boles[6] = new Bola(7, 7, 1);
    boles[7] = new Bola(8, 7, -1);
    boles[8] = new Bola(9, 7, -3);
    boles[9] = new Bola(10, 5, 2);
    boles[10] = new Bola(11, 5, 0);
    boles[11] = new Bola(12, 5, -2);
    boles[12] = new Bola(13, 3, 1);
    boles[13] = new Bola(14, 3, -1);
    boles[14] = new Bola(15, 1, 0);
    this->aplicaTGCentrat( Scale(Bola::scaleFactor, Bola::scaleFactor, Bola::scaleFactor) );

/*
    int count = 0;
    float z = 0.0;
    for(float i=0; i<5; i++){  // each row
        for(float it = 0; it <= i; it++){ // iter. balls per row
            boles[count] = new Bola(NumBoles-count, 1.+2*(i), z);
            qDebug() << "new Bola " << NumBoles-count << 1+2*(i) << z;
            count++;
         }
    }
    this->aplicaTGCentrat( Scale(Bola::scaleFactor, Bola::scaleFactor, Bola::scaleFactor) );
*/
}

void ConjuntBoles::toGPU(QGLShaderProgram *pr){
     qDebug() << "ConjuntBoles -> toGPU()";
    for(int i=0; i<NumBoles; i++) boles[i]->toGPU(pr);
}

void ConjuntBoles::draw(){
    qDebug() << "ConjuntBoles -> draw()";
    for(int i=0; i<NumBoles; i++) boles[i]->draw();
}

void ConjuntBoles::aplicaTG(mat4 m){
    qDebug() << "ConjuntBoles -> aplicaTG";
    for(int i=0; i<NumBoles; i++) boles[i]->aplicaTG(m);
}

void ConjuntBoles::aplicaTGPoints(mat4 m){
    qDebug() << "ConjuntBoles -> aplicaTGPoints";
    for(int i=0; i<NumBoles; i++) boles[i]->aplicaTGPoints(m);
}

void ConjuntBoles::aplicaTGCentrat(mat4 m){
    qDebug() << "ConjuntBoles -> aplicaTGCentrat";

    vec3 centre = vec3(capsa.pmin.x + capsa.a/2.,
                       capsa.pmin.y + capsa.h/2.,
                       capsa.pmin.z + capsa.p/2.);
    //qDebug() << "ConjuntBoles centre( " << centre.x << "," << centre.y << "," << centre.z << ")";

    // Contrucció de la matriu de translació al centre
    mat4 t1 = Common::Translate(-centre.x, -centre.y, -centre.z);
    mat4 t2 = Common::Translate( centre.x,  centre.y,  centre.z);
    aplicaTG(t2*m*t1);
    capsa = this->calculCapsa3D();
}

Capsa3D ConjuntBoles::calculCapsa3D(){
    // Metode a implementar: calcula la capsa mínima contenidora d'un objecte

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

    capsa.pmin = pmin;
    capsa.a = pmax.x - pmin.x;
    capsa.h = pmax.y - pmin.y;
    capsa.p = pmax.z - pmin.z;
    qDebug() << "ConjuntBoles -> calculaCapsa3D:\n\tpmin: (" << pmin.x << "," << pmin.y << ","
             << pmin.z << ") \n\ta:" << capsa.a << "\n\th:" << capsa.h << "\n\tp:" << capsa.p;
    return capsa;
}

void ConjuntBoles::initTextura(){}
