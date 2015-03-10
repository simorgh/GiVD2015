#include<bola.h>

Bola::Bola() : Objecte(NumVerticesF){
    tam = 1;
    Index = 0;
    xorig = yorig = zorig = 0;

    tetrahedron(4);
    capsa = calculCapsa3D();


    double escala = 1/50.;
    mat4 m = Scale(escala, escala, escala);
    aplicaTGCentrat(m);
    capsa = calculCapsa3D();

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
    divide_triangle(v[0], v[1], v[2], n);
    divide_triangle(v[3], v[2], v[1], n);
    divide_triangle(v[0], v[3], v[1], n);
    divide_triangle(v[0], v[2], v[3], n);
}

void Bola::divide_triangle(point4 a, point4 b, point4 c, int n){
    vec4 v1, v2, v3;

    if (n>0){
        v1 = this->normalize(a + b);
        v2 = this->normalize(a + c);
        v3 = this->normalize(b + c);
        divide_triangle(a ,v2, v1, n-1);
        divide_triangle(c ,v3, v2, n-1);
        divide_triangle(b ,v1, v3, n-1);
        divide_triangle(v1 ,v2, v3, n-1);
    } else triangle(a, b, c);
}

vec4 Bola::normalize(const vec4& v ){
    double m = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

    return vec4( v.x/m, v.y/m, v.z/m, 1.0 );
}



