#include<bola.h>

Bola::Bola() : Objecte(NumVerticesF){
    Index = 0;

    tetrahedron(NumIteracionsEsfera);
    capsa = calculCapsa3D();

    aplicaTGCentrat( Scale(scaleFactor, scaleFactor, scaleFactor) );
    aplicaTGCentrat( Translate(-5.0, scaleFactor, 0.0) ); // place the sphere over the plane and fit size to ratio
}

Bola::Bola(double x, double z) : Objecte(NumVerticesF){
    Index = 0;

    tetrahedron(NumIteracionsEsfera);
    capsa = calculCapsa3D();
    aplicaTGCentrat( Translate( x, 1., z) ); // place the sphere over the plane and fit size to ratio
}

Bola::~Bola(){}

void Bola::triangle(const point4 &a, const point4 &b, const point4 &c){
    points[Index] = a;
    colors[Index] = color4(1.0, 1.0, 1.0, 1.0); Index++;

    points[Index] = b;
    colors[Index] = color4(1.0, 1.0, 1.0, 1.0); Index++;

    points[Index] = c;
    colors[Index] = color4(1.0, 1.0, 1.0, 1.0); Index++;
}


void Bola::tetrahedron(){
    triangle(v[0], v[1], v[2]);
    triangle(v[3], v[2], v[1]);
    triangle(v[0], v[3], v[1]);
    triangle(v[0], v[2], v[3]);
}

void Bola::tetrahedron(int n){
    qDebug() << "Bola -> make()";
    divide_triangle(v[0], v[1], v[2], n);
    divide_triangle(v[3], v[2], v[1], n);
    divide_triangle(v[0], v[3], v[1], n);
    divide_triangle(v[0], v[2], v[3], n);
}

void Bola::divide_triangle(point4 a, point4 b, point4 c, int n){
    point4 v1, v2, v3;

    if (n>0){
        v1 = calculVectorUnitari(a + b);
        v2 = calculVectorUnitari(a + c);
        v3 = calculVectorUnitari(b + c);
        divide_triangle(a ,v2, v1, n-1);
        divide_triangle(c ,v3, v2, n-1);
        divide_triangle(b ,v1, v3, n-1);
        divide_triangle(v1 ,v2, v3, n-1);
    } else triangle(a, b, c);
}

vec4 Bola::calculVectorUnitari(const vec4& v ){
    double m = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

    return vec4( v.x/m, v.y/m, v.z/m, 1.0 );
}

void Bola::initTextura(){}


