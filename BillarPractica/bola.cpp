#include<bola.h>

Bola::Bola() : Objecte(NumVerticesF){
    Index = 0;
    this->id = 0;
    tetrahedron(NumIteracionsEsfera);
    initTextura();
    capsa = calculCapsa3D();
    aplicaTGCentrat( Scale(scaleFactor, scaleFactor, scaleFactor));
    aplicaTGCentrat( Translate(0.0, scaleFactor, -5.0)); // place the sphere over the plane and fit size to ratio

}

Bola::Bola(int id, double x, double z) : Objecte(NumVerticesF){
    Index = 0;
    this->id = id;
    tetrahedron(NumIteracionsEsfera);
    initTextura();
    capsa = calculCapsa3D();
    aplicaTGCentrat( Translate( x, 1., z) ); // place the sphere over the plane and fit size to ratio
}

Bola::~Bola(){}

void Bola::triangle(const point4 &a, const point4 &b, const point4 &c){
    vec2 tx;

    points[Index] = a;
    colors[Index] = color4(1.0, 1.0, 1.0, 1.0);
    tx = calculTexturaCoord(a);
    vertexsTextura[Index] = vec2(tx.x, tx.y);
    Index++;

    points[Index] = b;
    colors[Index] = color4(1.0, 1.0, 1.0, 1.0);
    tx = calculTexturaCoord(b);
    vertexsTextura[Index] = vec2(tx.x, tx.y);
    Index++;

    points[Index] = c;
    colors[Index] = color4(1.0, 1.0, 1.0, 1.0);
    tx = calculTexturaCoord(c);
    vertexsTextura[Index] = vec2(tx.x, tx.y);
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
    double u = 0.5 + atan2(v.z, v.x) / (2.*M_PI);
    double j = 0.5 - asin(v.y) / M_PI;
    //qDebug() << "u, j: " << u << j;
    return vec2(u, j);
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

     texture->bind(0);
}

void Bola::draw(){
    texture->bind(0);
    // per si han canviat les coordenades dels punts
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*Index, &points[0] );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index, sizeof(color4)*Index, &colors[0] );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index + sizeof(color4)*Index, sizeof(texture2)*Index, &vertexsTextura[0]);
    Objecte::draw();

}
