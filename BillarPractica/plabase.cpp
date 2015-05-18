#include<plabase.h>

PlaBase::PlaBase() : Objecte( NumVerticesF * NumCares ){
    //qDebug() << "Constructor de PlaBase";
    xorig = 0;
    yorig = 0;
    zorig = 0;

    // Vertices of a unit plain centered at origin, sides aligned with axes
    vertices[0] = point4( -0.5, -0.5,  0.0, 1.0 );
    vertices[1] = point4( -0.5,  0.5,  0.0, 1.0 );
    vertices[2] = point4(  0.5,  0.5,  0.0, 1.0 );
    vertices[3] = point4(  0.5, -0.5,  0.0, 1.0 );

    // Materials from "http://devernay.free.fr/cours/opengl/materials.html"
    //this->m = new Material(vec3(0.02, 0.02, 0.02), vec3(0.01, 0.01, 0.01), vec3(0.4, 0.4, 0.4), .078125f); //Black Rubber
    this->m = new Material(vec3(0.05375, 0.05, 0.06625), vec3(0.18275, 0.17, 0.22525), vec3(0.332741, 0.328634, 0.346435), .3f); //Obsidian
    //this->m = new Material(vec3(0.0215, 0.1745, 0.0215), vec3(0.07568, 0.61424, 0.07568), vec3(0.633, 0.727811, 0.633), 5.f); //Emerald

    this->make();

    // let's scale and translate the plane so it's position and lenght will be 18x15 y=0
    double escalaX = 10.;
    double escalaZ = 18.;
    mat4 rotX = RotateX(-90);
    aplicaTGCentrat( Scale(escalaX, 1., escalaZ) * rotX );
    aplicaTGnormals(rotX); //update normals.
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

    // Initialize temporary vectors along the quad's edge to
    // compute its face normal
    vec4 u = vertices[b] - vertices[a];
    vec4 v = vertices[c] - vertices[b];
    vec3 normal = normalize( cross(u, v) );

    normals[Index] = normal; points[Index] = vertices[a]; vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    normals[Index] = normal; points[Index] = vertices[b]; vertexsTextura[Index] = vec2(1.0, 0.0); Index++;
    normals[Index] = normal; points[Index] = vertices[c]; vertexsTextura[Index] = vec2(1.0, 1.0); Index++;

    normals[Index] = normal; points[Index] = vertices[a]; vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    normals[Index] = normal; points[Index] = vertices[c]; vertexsTextura[Index] = vec2(1.0, 1.0); Index++;
    normals[Index] = normal; points[Index] = vertices[d]; vertexsTextura[Index] = vec2(0.0, 1.0); Index++;
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
