#include<bola.h>

Bola::Bola() : Objecte(NumVerticesF){
    this->id = 0;

    Index = 0;
    tetrahedron(NumIteracionsEsfera); //make
    initTextura();

    // place the sphere over the plane and fit size to ratio
    capsa = calculCapsa3D();

    aplicaTGCentrat( Scale(scaleFactor, scaleFactor, scaleFactor) );
    aplicaTG( Translate(0.0, scaleFactor, -5.0) );
}

Bola::Bola(int id, double x, double z) : Objecte(NumVerticesF){
    this->id = id;

    Index = 0;
    tetrahedron(NumIteracionsEsfera);
    initTextura();

    capsa = calculCapsa3D();
    aplicaTG( Translate( x, 1. , z) ); // place the sphere over the plane and fit size to ratio
}

Bola::~Bola(){}

void Bola::triangle(const point4 &a, const point4 &b, const point4 &c){
    vec2 t1, t2, t3;

    points[Index] = a;
    colors[Index] = color4(1.0, 1.0, 1.0, 1.0);
    t1 = calculTexturaCoord(a);
    vertexsTextura[Index] = vec2(t1.x, t1.y);
    Index++;

    double th= 0.5;
    points[Index] = b;
    colors[Index] = color4(1.0, 1.0, 1.0, 1.0);
    t2 = calculTexturaCoord(b);
    if(t2.x < th && t1.x > th) t2.x += 1.0;
    else if(t2.x > th && t1.x < th) t2.x -= 1.0;
    vertexsTextura[Index] = vec2(t2.x, t2.y);
    Index++;

    points[Index] = c;
    colors[Index] = color4(1.0, 1.0, 1.0, 1.0);
    t3 = calculTexturaCoord(c);
    if(t3.x < th && t1.x > th) t3.x += 1.0;
    else if(t3.x > th && t1.x < th) t3.x -= 1.0;
    vertexsTextura[Index] = vec2(t3.x, t3.y);
    Index++;
}

void Bola::tetrahedron(){
    triangle(v[0], v[1], v[2]);
    triangle(v[3], v[2], v[1]);
    triangle(v[0], v[3], v[1]);
    triangle(v[0], v[2], v[3]);
}

void Bola::tetrahedron(int n){
    //qDebug() << "Bola -> make()";
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

/**
 * Genera les coordenades de textures associades a cada vèrtex de l'esfera,
 * tot suposant v és el vector unitari que va des del punt p de la superfície
 * de l’esfera fins al del centre de l’esfera.*/
vec2 Bola::calculTexturaCoord(const vec4 &v){
    double U = (double) 0.5f + atan2(v.x, v.z) / ( 2.0f * M_PI );
    double V = (double) 0.5f - asin(v.y) / M_PI;

    if(U > 1.0) U = (float)1.0; else if(U < 0.0) U = (float)0.0;
    if(V > 1.0) V = (float)1.0; else if(V < 0.0) V = (float)0.0;
    //qDebug() << "u, j: " << u << j;

    return vec2(U, V);
}

vec4 Bola::calculVectorUnitari(const vec4& v ){
    double length = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    return vec4( v.x/length, v.y/length, v.z/length, 1.0 );
}

void Bola::initTextura(){
    //qDebug() << "Bola - Initializing textures...";
    ostringstream ss;
    ss << "://resources/Bola" << this->id << ".jpg";

     // Carregar la textura
    glActiveTexture(GL_TEXTURE0);
    texture = new QOpenGLTexture( QImage(ss.str().c_str()) );
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
}


