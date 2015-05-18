#include <objecte.h>
#include <readfile.h>


Objecte::Objecte(int npoints, QObject *parent) : numPoints(npoints) ,QObject(parent){
    points = new point4[npoints];
    pointsTmp = new point4[npoints];

    normals = new point4[numPoints];
    vertexsTextura = new texture2[npoints];

    /* by default using 'Black Rubber' def. See "http://devernay.free.fr/cours/opengl/materials.html" */
    m = new Material(vec3(0.02, 0.02, 0.02), vec3(0.01, 0.01, 0.01), vec3(0.4, 0.4, 0.4), .078125f);
}

Objecte::Objecte(int npoints, QString n) : numPoints(npoints){
    qDebug() << "Estic en el constructor parametritzat del objecte\n";
    points = new point4[npoints];
    normals = new point4[numPoints];
    vertexsTextura = new texture2[npoints];

    /* by default using 'Black Rubber' def. See "http://devernay.free.fr/cours/opengl/materials.html" */
    m = new Material(vec3(0.02, 0.02, 0.02), vec3(0.01, 0.01, 0.01), vec3(0.4, 0.4, 0.4), .078125f);

    xRot = 0;
    yRot = 0;
    zRot = 0;

    Index = 0;
    readObj(n);
    make();
}


Objecte::~Objecte(){
    delete points;
    delete vertexsTextura;
    delete normals;
    delete m;
}


Capsa3D Objecte::calculCapsa3D(){

    // Metode a implementar: calcula la capsa mínima contenidora d'un objecte
    vec3 pmin = vec3(  99999,  99999,  99999);
    vec3 pmax = vec3( -99999, -99999, -99999);
    Capsa3D c;

    for(int i = 0; i<Index; i++){
        if(points[i].x > pmax.x) pmax.x = points[i].x;
        if(points[i].y > pmax.y) pmax.y = points[i].y;
        if(points[i].z > pmax.z) pmax.z = points[i].z;

        if(points[i].x < pmin.x) pmin.x = points[i].x;
        if(points[i].y < pmin.y) pmin.y = points[i].y;
        if(points[i].z < pmin.z) pmin.z = points[i].z;
    }

    c.pmin = pmin;
    c.a = pmax.x - pmin.x;
    c.h = pmax.y - pmin.y;
    c.p = pmax.z - pmin.z;
    return c;
}

void Objecte::aplicaTG(mat4 m) {
    aplicaTGPoints(m);
    capsa = calculCapsa3D();
}

/**
 * Should be use when some Rotation is applied to the Object
 * @brief aplicaTGnormals
 * @param m
 */
void Objecte::aplicaTGnormals(mat4 m) {
    point4  *transformed_normals = new point4[Index];

    for ( int i = 0; i < Index; ++i ) transformed_normals[i] = m * normals[i];

    transformed_normals = &transformed_normals[0];
    normals = &normals[0];

    for ( int i = 0; i < Index; ++i )  normals[i] = transformed_normals[i];
    delete transformed_normals;
}

/**
 * @brief Objecte::aplicaTGPoints
 * @param m
 */
void Objecte::aplicaTGPoints(mat4 m) {
    point4  *transformed_points = new point4[Index];

    for ( int i = 0; i < Index; ++i ) {
        transformed_points[i] = m * points[i];
    }

    transformed_points = &transformed_points[0];
    points = &points[0];

    for ( int i = 0; i < Index; ++i ) {
        points[i] = transformed_points[i];
    }

    delete transformed_points;
}

/**
 * @brief Objecte::aplicaTGCentrat
 * @param m
 */
void Objecte::aplicaTGCentrat(mat4 m){
    vec3 centre = vec3(capsa.pmin.x + capsa.a/2., capsa.pmin.y + capsa.h/2., capsa.pmin.z + capsa.p/2.);
    //qDebug() << "centre( " << centre.x << "," << centre.y << "," << centre.z << ")";

    // Contrucció de la matriu de translació al centre
    mat4 t1 = Common::Translate(-centre.x, -centre.y, -centre.z);
    mat4 t2 = Common::Translate( centre.x,  centre.y,  centre.z);

    aplicaTG(t2*m*t1);
}

/**
 * @brief Objecte::toGPU
 * @param pr
 */
void Objecte::toGPU(QGLShaderProgram *pr) {
    program = pr;
/*
    qDebug() << "\t >> obj->material->toGPU...";
    qDebug() << "\t\t + ambient:" << m->ambient.x << m->ambient.y << m->ambient.z;
    qDebug() << "\t\t + diffuse:" << m->diffuse.x << m->diffuse.y << m->diffuse.z;
    qDebug() << "\t\t + specular:" << m->specular.x << m->specular.y << m->specular.z;
    qDebug() << "\t\t + reflection:" << m->reflection;
*/
    //qDebug() <<"Objecte -> toGPU() : Passo les dades de l'objecte a la GPU\n";
    glGenBuffers( 1, &buffer );             // inicialitzacio d'un vertex buffer object (VBO)
    glBindBuffer( GL_ARRAY_BUFFER, buffer );// Activació a GL del Vertex Buffer Object

    // Transferència dels punts, colors, normals i coordenades de textura al vertex buffer object
    glBufferData( GL_ARRAY_BUFFER, sizeof(point4)*Index + sizeof(point4)*Index + sizeof(texture2)*Index, NULL, GL_STATIC_DRAW );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );
    program->bind();
}


/**
 * Pintat en la GPU.
 * @brief Objecte::draw
 */
void Objecte::draw(){
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // per si han canviat les coordenades dels punts
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*Index, &points[0] ); // Actualitzacio del vertex array per a preparar per pintar
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index, sizeof(point4)*Index, &normals[0] );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index + sizeof(point4)*Index, sizeof(texture2)*Index, &vertexsTextura[0]);

    // Per a conservar el buffer
    int vertexLocation = program->attributeLocation("vPosition");
    int normalLocation = program->attributeLocation("vNormal");
    int coordTextureLocation = program->attributeLocation("vCoordTexture");

    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer("vPosition", GL_FLOAT, 0, 4);

    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer("vNormal", GL_FLOAT, sizeof(point4)*Index, 4);

    program->enableAttributeArray(coordTextureLocation);
    program->setAttributeBuffer("vCoordTexture", GL_FLOAT, sizeof(point4)*Index + sizeof(point4)*Index, 2);

    // S'activa la textura i es passa a la GPU
    texture->bind(0);
    program->setUniformValue("texMap", 0);
    m->toGPU(program);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays( GL_TRIANGLES, 0, Index );
}

void Objecte::make(){
    static vec3  base_colors[] = {
        vec3( 1.0, 0.0, 0.0 ),
        vec3( 0.0, 1.0, 0.0 ),
        vec3( 0.0, 0.0, 1.0 ),
        vec3( 1.0, 1.0, 0.0 )
    };

    // Recorregut de totes les cares per a posar-les en les estructures de la GPU
    // Cal recorrer l'estructura de l'objecte per a pintar les seves cares
    Index = 0;
    for(unsigned int i=0; i<cares.size(); i++){
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++){
            points[Index] = vertexs[cares[i].idxVertices[j]];
            //TODO: normals ??
            //colors[Index] = vec4(base_colors[1], 1.0);
            vertexsTextura[Index] = vec2(0.0, 0.0);
            Index++;
        }
    }

}


void Objecte::backupPoints() {
    for ( int i = 0; i < Index; i++ )
        pointsTmp[i] = points[i];
}

void Objecte::restorePoints() {
    for ( int i = 0; i < Index; i++ )
        points[i] = pointsTmp[i];
}


// Llegeix un fitxer .obj
//  Si el fitxer referencia fitxers de materials (.mtl), encara no es llegeixen
//  Tots els elements del fitxer es llegeixen com a un unic objecte.
void Objecte::readObj(QString filename){

    FILE *fp = fopen(filename.toLocal8Bit(),"rb");
    if (!fp)
    {
        cout << "No puc obrir el fitxer " << endl;
    }
    else {

        while (true)
        {
            char *comment_ptr = ReadFile::fetch_line (fp);

            if (comment_ptr == (char *) -1)  /* end-of-file */
                break;

            /* did we get a comment? */
            if (comment_ptr) {
                //make_comment (comment_ptr);
                continue;
            }

            /* if we get here, the line was not a comment */
            int nwords = ReadFile::fetch_words();

            /* skip empty lines */
            if (nwords == 0)
                continue;

            char *first_word = ReadFile::words[0];

            if (!strcmp (first_word, "v"))
            {
                if (nwords < 4) {
                    fprintf (stderr, "Too few coordinates: '%s'", ReadFile::str_orig);
                    exit (-1);
                }

                QString sx(ReadFile::words[1]);
                QString sy(ReadFile::words[2]);
                QString sz(ReadFile::words[3]);
                double x = sx.toDouble();
                double y = sy.toDouble();
                double z = sz.toDouble();

                if (nwords == 5) {
                    QString sw(ReadFile::words[4]);
                    double w = sw.toDouble();
                    x/=w;
                    y/=w;
                    z/=w;
                }
                // S'afegeix el vertex a l'objecte
                vertexs.push_back(point4(x, y, z, 1));

            }
            else if (!strcmp (first_word, "vn")) {
            }
            else if (!strcmp (first_word, "vt")) {
            }
            else if (!strcmp (first_word, "f")) {
                // S'afegeix la cara a l'objecte
                // A modificar si es vol carregar mes de un objecte
                construeix_cara (&ReadFile::words[1], nwords-1, this, 0);
            }
            // added
            else if (!strcmp (first_word, "mtllib")) {
                //read_mtllib (&words[1], nwords-1, matlib, filename);
            }
            else if (!strcmp (first_word, "usemtl")) {
                //int size = strlen(words[1])-1;
                //while (size && (words[1][size]=='\n' || words[1][size]=='\r') ) words[1][size--]=0;
                //currentMaterial = matlib.index(words[1]);
            }
            // fadded
            else {
                //fprintf (stderr, "Do not recognize: '%s'\n", str_orig);
            }
        }
    }

    capsa = calculCapsa3D();
}

/**
 * @brief Objecte::construeix_cara
 * @param words
 * @param nwords
 * @param objActual
 * @param vindexUlt
 */
void Objecte::construeix_cara ( char **words, int nwords, Objecte*objActual, int vindexUlt) {
    Cara face;

    for (int i = 0; i < nwords; i++) {
        int vindex;
        int nindex;
        int tindex;

        if ((words[i][0]>='0')&&(words[i][0]<='9')) {
            ReadFile::get_indices (words[i], &vindex, &tindex, &nindex);

#if 0
            printf ("vtn: %d %d %d\n", vindex, tindex, nindex);
#endif

            /* store the vertex index */

            if (vindex > 0)       /* indices are from one, not zero */
                face.idxVertices.push_back(vindex - 1 - vindexUlt);
            else if (vindex < 0)  /* negative indices mean count backwards */
                face.idxVertices.push_back(objActual->vertexs.size() + vindex);
            else {
                fprintf (stderr, "Zero indices not allowed: '%s'\n", ReadFile::str_orig);
                exit (-1);
            }
        }
    }
    face.color = vec4(1.0, 0.0, 0.0, 1.0);
    objActual->cares.push_back(face);
}

/**
 * @brief Objecte::hasCollided
 * @param obj
 * @return
 */
bool Objecte::hasCollided(Objecte* obj){
    if(obj->capsa.pmin.x > (capsa.pmin.x + capsa.a)) return false;
    else if((obj->capsa.pmin.x + obj->capsa.a) < capsa.pmin.x) return false;
    else {
        if(obj->capsa.pmin.z > (capsa.pmin.z + capsa.p)) return false;
        else if((obj->capsa.pmin.z + obj->capsa.p) < capsa.pmin.z ) return false;
    }

    return true;
}

/**
 * @brief PlaBase::calculaNormalsFlatShading
 */
void Objecte::calculaNormalsFlatShading() {
    float vec_ax, vec_ay, vec_az, vec_bx, vec_by, vec_bz;
    vec3 normal;
    for (int a = 0; a < Index; a+=3){
        normal = 0.0f;
        vec_ax = points[a+2].x - points[a+1].x;
        vec_ay = points[a+2].y - points[a+1].y;
        vec_az = points[a+2].z - points[a+1].z;

        vec_bx = points[a].x - points[a+1].x;
        vec_by = points[a].y - points[a+1].y;
        vec_bz = points[a].z - points[a+1].z;

        //Cross Product
        normal.x = vec_ay*vec_bz - vec_az * vec_by;//A x B
        normal.y = vec_az*vec_bx - vec_ax * vec_bz;
        normal.z = vec_ax*vec_by - vec_ay*vec_bx;

        float mod = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
        normal.x /= mod;
        normal.y /= mod;
        normal.z /= mod;

        //qDebug() << normal.x << normal.y << normal.z;
        normals[a] = normal;
        normals[a+1] = normal;
        normals[a+2] = normal;
   }

}

/**
 * @brief Objecte::calculaNormalsGouraud
 */
void Objecte::calculaNormalsGouraud() {
    for(int i=0; i < numPoints; i++) normals[i] = points[i];
}
