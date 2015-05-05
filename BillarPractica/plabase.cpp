#include<plabase.h>

PlaBase::PlaBase() : Objecte(NumVerticesF){
    //qDebug() << "Constructor de PlaBase";
    xorig = 0;
    yorig = 0;
    zorig = 0;

    // Vertices of a unit plain centered at origin, sides aligned with axes
    vertices[0] = point4( -0.5, -0.5,  0.0, 1.0 );
    vertices[1] = point4( -0.5,  0.5,  0.0, 1.0 );
    vertices[2] = point4(  0.5,  0.5,  0.0, 1.0 );
    vertices[3] = point4(  0.5, -0.5,  0.0, 1.0 );

    // RGBA colors
    vertex_colors[0] = color4( 0.0, 1.0, 0.0, 1.0 );
    vertex_colors[1] = color4( 0.0, 1.0, 0.0, 1.0 );
    vertex_colors[2] = color4( 0.0, 1.0, 0.0, 1.0 );
    vertex_colors[3] = color4( 0.0, 1.0, 0.0, 1.0 );

    /* by default using 'Green Rubber' def. See "http://devernay.free.fr/cours/opengl/materials.html" */
    this->m = new Material(vec3(0.0, 0.05, 0.0), vec3(0.4, 0.5, 0.4), vec3(0.04, 0.7, 0.04), .078125f);
    this->make();

    // let's scale and translate the plane so it's position and lenght will be 18x15 y=0
    double escalaX = 10.;
    double escalaZ = 18.;
    aplicaTGCentrat( Scale(escalaX, 1., escalaZ) * RotateX(90) );
}

void PlaBase::make(){
    Index = 0;
    quad(1, 0, 3, 2);
    quad(2, 3, 0, 1);
    initTextura();
    capsa = calculCapsa3D();
}


// quad generates two triangles for each face and assigns colors
// to the vertices
void PlaBase::quad( int a, int b, int c, int d ){
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a];
    vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    colors[Index] = vertex_colors[b]; points[Index] = vertices[b];
    vertexsTextura[Index] = vec2(1.0, 0.0); Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c];
    vertexsTextura[Index] = vec2(1.0, 1.0); Index++;

    colors[Index] = vertex_colors[a]; points[Index] = vertices[a];
    vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c];
    vertexsTextura[Index] = vec2(1.0, 1.0); Index++;
    colors[Index] = vertex_colors[d]; points[Index] = vertices[d];
    vertexsTextura[Index] = vec2(0.0, 1.0); Index++;
}

void PlaBase::initTextura(){
     //qDebug() << "PlaBase - Initializing textures...";

     // Carregar la textura
     glActiveTexture(GL_TEXTURE0);
     texture = new QOpenGLTexture(QImage("://resources/Fabric_Green_L.jpg"));
     texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
     texture->setMagnificationFilter(QOpenGLTexture::Linear);
}

PlaBase::~PlaBase(){}
