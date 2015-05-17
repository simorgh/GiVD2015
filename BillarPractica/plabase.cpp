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

    /* by default using 'Green Rubber' def. See "http://devernay.free.fr/cours/opengl/materials.html" */
    this->m = new Material(vec3(0.0, 0.05, 0.0), vec3(0.4, 0.5, 0.4), vec3(0.04, 0.7, 0.04), .078125f);
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
    //calculaNormals();

    normals[Index] = normal; points[Index] = vertices[a]; vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    normals[Index] = normal; points[Index] = vertices[c]; vertexsTextura[Index] = vec2(1.0, 1.0); Index++;
    normals[Index] = normal; points[Index] = vertices[d]; vertexsTextura[Index] = vec2(0.0, 1.0); Index++;
    //calculaNormals();
}

void PlaBase::initTextura(){
     //qDebug() << "PlaBase - Initializing textures...";

     // Carregar la textura
     glActiveTexture(GL_TEXTURE0);
     texture = new QOpenGLTexture(QImage("://resources/Fabric_Green_L.jpg"));
     texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
     texture->setMagnificationFilter(QOpenGLTexture::Linear);
}

/**
 * @brief PlaBase::calculaNormalCara
 */
void PlaBase::calculaNormals() {
    int j;
    vec3 normal = vec3(0.0, 0.0, 0.0);

    for (int i=Index-2; i<=Index; i++) {
        j = (i+1)%3;
        normal.x += ((points[i].z + points[j].z) * (points[i].y - points[j].y));
        normal.y += ((points[i].x + points[j].x) * (points[i].z - points[j].z));
        normal.z += ((points[i].y + points[j].y) * (points[i].x - points[j].x));
    }

    normal.x *= 0.5;
    normal.y *= 0.5;
    normal.z *= 0.5;

    normals[Index-2] = normal;
    normals[Index-1] = normal;
    normals[Index] = normal;
    //normal.normalize();
}


PlaBase::~PlaBase(){}
