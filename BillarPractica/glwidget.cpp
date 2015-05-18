#include <math.h>
#include <glwidget.h>
#include <QtDebug>
#include <QString>


GLWidget::GLWidget(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {
    setFocusPolicy( Qt::StrongFocus );

    xRot = -90;
    yRot = 180;
    zRot = 0;

    a = 20.0;
    h = 20.0;
    p = 20.0;

    clearColor = Qt::gray;
    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

    program = 0;
    moviment = false;
    cameraActual = true; //true-> s'ha de modificar la càmera general; false -> s'ha de modificar la càmera en primera persona.
    esc = new Escena();
}

GLWidget::~GLWidget() {
    makeCurrent();
    delete esc;
}

// Create a GLSL program object from vertex and fragment shader files
void GLWidget::InitShader(const char* vShaderFile, const char* fShaderFile){
    QGLShaderProgram *pr;
    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);

    // Compilació del vertex shader
    vshader->compileSourceFile(vShaderFile);
    fshader->compileSourceFile(fShaderFile);

    pr = new QGLShaderProgram(this);
    pr->addShader(vshader);
    pr->addShader(fshader);
    programs.push_back(pr);
}

/**
 * @brief GLWidget::initShadersGPU
 */
void GLWidget::initShadersGPU(){
    // Carrega dels shaders i posa a punt per utilitzar els programes carregats a la GPU
    //InitShader("://vshader1.glsl", "://fshader1.glsl");
    InitShader("://gouraud_vshader.glsl", "://gouraud_fshader.glsl");
    InitShader("://phong_vshader.glsl", "://phong_fshader.glsl");
    InitShader("://toon_vshader.glsl", "://toon_fshader.glsl");
    setProgram(0);
}

/**
 * @brief GLWidget::setProgram
 * @param id
 */
void GLWidget::setProgram(int id){
    if(id < 0 || id >= programs.size()) return;

    this->program = programs[id];
    program->link();    // muntatge del shader en el pipeline grafic per a ser usat
    program->bind();    // unió del shader al pipeline gràfic

    esc->llum->toGPU(program);
    esc->setAmbientToGPU(program);

    update();
}

QSize GLWidget::minimumSizeHint() const {
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const {
    return QSize(400, 400);
}


static void qNormalizeAngle(int &angle) {
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}


void GLWidget::setXRotation(int angle) {
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        update();
    }
}


void GLWidget::setYRotation(int angle) {
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        update();
    }
}

void GLWidget::setZRotation(int angle) {
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        update();
    }
}


void GLWidget::initializeGL() {
    qDebug() << "Entering initializeGL()...";
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_RGBA);
    glEnable(GL_DOUBLE);

    initShadersGPU();
    esc->iniCamera(cameraActual, this->size().width(), this->size().height(), this->program);

    //qDebug() << "\t >> esc->setAmbientToGPU is sending Ia:" << esc->Ia.x << esc->Ia.y << esc->Ia.z;
    esc->setAmbientToGPU(this->program);
/*
    qDebug() << "\t >> esc->llum->toGPU...";
    qDebug() << "\t\t + a, b, c:" << esc->llum->a << esc->llum->b << esc->llum->c;
    qDebug() << "\t\t + ambient:" << esc->llum->ambient.x << esc->llum->ambient.y << esc->llum->ambient.z;
    qDebug() << "\t\t + specular:" << esc->llum->specular.x << esc->llum->specular.y << esc->llum->specular.z;
    qDebug() << "\t\t + diffuse:" << esc->llum->diffuse.x << esc->llum->diffuse.y << esc->llum->diffuse.z;
    qDebug() << "\t\t + position:" << esc->llum->position.x << esc->llum->position.y << esc->llum->position.z;
*/
    esc->llum->toGPU(this->program);

    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWidget::paintGL() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    program->setUniformValue("texture", 0);

    // Camera rotation if needed
    esc->setAnglesCamera(cameraActual, xRot, yRot, zRot );

    // update active camera
    if(cameraActual) esc->camGeneral->toGPU(program);
    else esc->camFP->toGPU(program);

    esc->draw();
}


void GLWidget::resizeGL(int width, int height) {
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-1.5, +1.5, -1.5, +1.5, 0.0, 15.0);
#else
    glOrtho(-1.5, +1.5, -1.5, +1.5, 0.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}


void GLWidget::mousePressEvent(QMouseEvent *event) {
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    /* si hi ha un desplaçament en X de viewport, es canviarà l'angle Y de la càmera
     * si hi ha un desplaçament en Y de viewport, es canviarà l'angle X de la càmera.*/

    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + RSPEED * dy);
        setYRotation(yRot + RSPEED * dx);
    }

    lastPos = event->pos();
}


void GLWidget::keyPressEvent(QKeyEvent *event) {

    switch ( event->key() ){

        case Qt::Key_Up:
            //qDebug() << "KEY_UP pressed";
            if(event->modifiers() & Qt::AltModifier) Pan(0,-PAN);
            else {
                mat4 rotate = RotateX(15);

                esc->elements.at(1)->backupPoints();
                esc->elements.at(1)->aplicaTG(Translate(0.0, 0.0, 0.08)); //movement
                esc->elements.at(1)->aplicaTGCentrat(rotate);

                if(!esc->hasCollided(esc->elements.at(1)) && !(esc->elements.at(2)->hasCollided(esc->elements.at(1)))) {
                    esc->elements.at(1)->aplicaTGnormals(rotate);

                    // if FP Camera, let's update it
                    if(!cameraActual) {
                        point4 c = point4(esc->elements.at(1)->capsa.pmin.x + esc->elements.at(1)->capsa.a/2.,
                                          esc->elements.at(1)->capsa.pmin.y + esc->elements.at(1)->capsa.h/2.,
                                          esc->elements.at(1)->capsa.pmin.z + esc->elements.at(1)->capsa.p/2., 1.0);
                        esc->setVRPCamera(cameraActual, c);
                    }

                    update();
                } else esc->elements.at(1)->restorePoints();
            }
            break;

        case Qt::Key_Down:
            //qDebug() << "KEY_DOWN pressed";
            if(event->modifiers() & Qt::AltModifier) Pan(0, PAN);
            else {
                mat4 rotate = RotateX(-15);

                esc->elements.at(1)->backupPoints();
                esc->elements.at(1)->aplicaTG( Translate(0.0, 0.0, -0.08 ) ); //movement
                esc->elements.at(1)->aplicaTGCentrat(rotate);
                if(!esc->hasCollided(esc->elements.at(1)) && !(esc->elements.at(2)->hasCollided(esc->elements.at(1)))) {
                    esc->elements.at(1)->aplicaTGnormals(rotate);

                    // if FP Camera, let's update it
                    if(!cameraActual) {
                        point4 c = point4(esc->elements.at(1)->capsa.pmin.x + esc->elements.at(1)->capsa.a/2.,
                                          esc->elements.at(1)->capsa.pmin.y + esc->elements.at(1)->capsa.h/2.,
                                          esc->elements.at(1)->capsa.pmin.z + esc->elements.at(1)->capsa.p/2., 1.0);
                        esc->setVRPCamera(cameraActual, c);
                    }
                    update();
                } else esc->elements.at(1)->restorePoints();
            }
            break;

        case Qt::Key_Left:
            //qDebug() << "KEY_LEFT pressed";
            if(event->modifiers() & Qt::AltModifier) Pan(PAN,0);
            else {
                mat4 rotate = RotateZ(-15);

                esc->elements.at(1)->backupPoints();
                esc->elements.at(1)->aplicaTG( Translate(0.08, 0.0, 0.0) ); //movement
                esc->elements.at(1)->aplicaTGCentrat(rotate);
                if(!esc->hasCollided(esc->elements.at(1)) && !(esc->elements.at(2)->hasCollided(esc->elements.at(1)))) {
                    esc->elements.at(1)->aplicaTGnormals(rotate);

                    // if FP Camera, let's update it
                    if(!cameraActual) {
                        point4 c = point4(esc->elements.at(1)->capsa.pmin.x + esc->elements.at(1)->capsa.a/2.,
                                          esc->elements.at(1)->capsa.pmin.y + esc->elements.at(1)->capsa.h/2.,
                                          esc->elements.at(1)->capsa.pmin.z + esc->elements.at(1)->capsa.p/2., 1.0);
                        esc->setVRPCamera(cameraActual, c);
                    }
                    update();
                } else esc->elements.at(1)->restorePoints();
            }
            break;

        case Qt::Key_Right:
            //qDebug() << "KEY_RIGHT pressed";
            if(event->modifiers() & Qt::AltModifier) Pan(-PAN,0);
            else {
                mat4 rotate = RotateZ(15);

                esc->elements.at(1)->backupPoints();
                esc->elements.at(1)->aplicaTG( Translate(-0.08, 0.0, 0.0) ); //movement
                esc->elements.at(1)->aplicaTGCentrat(rotate);
                if(!esc->hasCollided(esc->elements.at(1)) && !(esc->elements.at(2)->hasCollided(esc->elements.at(1)))) {
                    esc->elements.at(1)->aplicaTGnormals(rotate);

                    // if FP Camera, let's update it
                    if(!cameraActual) {
                        point4 c = point4(esc->elements.at(1)->capsa.pmin.x + esc->elements.at(1)->capsa.a/2.,
                                          esc->elements.at(1)->capsa.pmin.y + esc->elements.at(1)->capsa.h/2.,
                                          esc->elements.at(1)->capsa.pmin.z + esc->elements.at(1)->capsa.p/2., 1.0);
                        esc->setVRPCamera(cameraActual, c);
                    }
                    update();
                } else esc->elements.at(1)->restorePoints();
            }
            break;

        case Qt::Key_Plus:
            //qDebug() << "KEY_PLUS pressed";
            this->Zoom(1);
            break;

        case Qt::Key_Minus:
            //qDebug() << "KEY_MINUS pressed";
            this->Zoom(-1);
            break;


        case Qt::Key_B:
            //qDebug() << "KEY_B pressed";

            //canviar des de la càmera general a la càmera en primera persona.
            if(cameraActual) {
                cameraActual = false;
                if(!esc->camFP) {
                    qDebug() << "First Person Camera initialization";
                    esc->iniCamera(cameraActual, this->size().width(), this->size().height(), this->program);
                    xRot = -15;
                    yRot = 180;
                } else {
                    xRot = this->esc->camFP->vs.angx;
                    yRot = this->esc->camFP->vs.angy;
                }

                point4 c = point4(esc->elements.at(1)->capsa.pmin.x + esc->elements.at(1)->capsa.a/2.,
                                  esc->elements.at(1)->capsa.pmin.y + esc->elements.at(1)->capsa.h/2.,
                                  esc->elements.at(1)->capsa.pmin.z + esc->elements.at(1)->capsa.p/2., 1.0);
                esc->setVRPCamera(cameraActual, c);
                update();
            }
            break;

        case Qt::Key_T:
            //qDebug() << "KEY_T pressed";

            //canviar des de la càmera en primera persona a la càmera general.
            if(!cameraActual) {
                cameraActual = true;
                if(!esc->camGeneral) {
                    qDebug() << "General Camara initialization";
                    esc->iniCamera(cameraActual, this->size().width(), this->size().height(), this->program);
                    xRot = -90;
                    yRot = 180;
                } else {
                    xRot = this->esc->camGeneral->vs.angx;
                    yRot = this->esc->camGeneral->vs.angy;
                }

                update();
            }
            break;

        case Qt::Key_1: // Flat shading
            int flag;
            if(event->modifiers() & Qt::ShiftModifier) flag = 1;
            else flag = 1.0;

            if(esc->ntype == GOURAUD) {
                esc->ntype = FLAT;
                esc->calculaNormals(esc->ntype);
            }

            setProgram(0);
            break;

        case Qt::Key_2: // Gouraud
            if(esc->ntype == FLAT) {
                esc->ntype = GOURAUD;
                esc->calculaNormals(esc->ntype);
            }

            setProgram(0);
            break;

        case Qt::Key_3: //Phong shading
            if(esc->ntype == FLAT){
                 esc->ntype = GOURAUD;
                 esc->calculaNormals(esc->ntype);
             }

            setProgram(1);
            break;

        case Qt::Key_4: //Toon Shading

            setProgram(2);
            break;
        }


}

void GLWidget::keyReleaseEvent(QKeyEvent *event) {
    // Metode a implementar en el cas que es mogui la bola (aceleració)
}



void GLWidget::adaptaObjecteTamanyWidget(Objecte *obj) {
    double escala = 2/20.;

    mat4 m = Scale(escala, escala, escala);
    vec3 centre = vec3(obj->capsa.pmin.x + obj->capsa.a/2.,obj->capsa.pmin.y + obj->capsa.h/2., obj->capsa.pmin.z + obj->capsa.p/2.);

    // Contrucció de la matriu de translació al centre
    mat4 t1 = Common::Translate(-centre.x, -centre.y, -centre.z);
    mat4 t2 = Common::Translate( centre.x*escala,  centre.y*escala,  centre.z*escala);

    obj->aplicaTG(t2*m*t1);
    obj->capsa = obj->calculCapsa3D();
}

void GLWidget::newObjecte(Objecte * obj){
    esc->addObjecte(obj);
    obj->toGPU(program);

    updateGL();
}

void GLWidget::newPlaBase() {
    // Metode que crea un objecte PlaBase poligon amb el punt central al (0,0,0) i perpendicular a Y=0
    PlaBase *pla;

    pla = new PlaBase();
    newObjecte(pla);
}

void GLWidget::newObj(QString fichero){
    // Metode que carrega un fitxer .obj llegit de disc
    qDebug() << fichero;

}

void GLWidget::newBola(){
    // Metode que crea la Bola blanca de joc
    Bola *obj;

    obj = new Bola();
    newObjecte(obj);
}

void GLWidget::newConjuntBoles(){
    // Metode que crea les 15 Boles del billar america
    ConjuntBoles *obj;

    obj = new ConjuntBoles();
    newObjecte(obj);
}

void GLWidget::newSalaBillar() {
    // Metode que construeix tota la sala de billar: taula, 15 boles i bola blanca
    clearSalaBillar();

    // add game elements here:
    newPlaBase();
    newBola();
    newConjuntBoles();
    //newTaulaBillar();
}

void GLWidget::newTaulaBillar(){
    QString current = QDir::currentPath();
    QString relative = current.left( current.lastIndexOf('/')) + "/BillarPractica/resources/taula.obj";
    //qDebug() << "CURRENT DIRECTORY is:" << current; qDebug() << "RELATIVE DIRECTORY is:" << relative;

    TaulaBillar *obj;
    obj = new TaulaBillar("/Users/simorgh/givd2015/BillarPractica/resources/taula.obj");//relative);

    obj->toGPU(program);
    esc->addObjecte(obj);
    updateGL();
}

void GLWidget::clearSalaBillar(){
    // in case of needed clear old elements and reset Escena
    if(!esc->elements.empty()){
        esc->elements.clear();

        esc->capsaMinima.pmin[0]=0; esc->capsaMinima.pmin[1] = 0; esc->capsaMinima.pmin[2]=0;
        esc->capsaMinima.a = 0; esc->capsaMinima.h = 0; esc->capsaMinima.p = 0;
        xRot = -90; yRot = 180; zRot = 0;
        cameraActual = true;
    }
}

// Metode per iniciar la dinàmica del joc
void GLWidget::Play() {
    //TODO: i.e. boolean to be checked when white ball should move?
}

//method for zoom in/zoom out. If the parameter is a positive value, the zoom in will be performed and vice versa
void GLWidget::Zoom(int positiu) {
    if (cameraActual) {
        if(positiu > 0)  esc->camGeneral->AmpliaWindow(-0.05);
        else  esc->camGeneral->AmpliaWindow(0.05);
        update();
    }
}


void GLWidget::Pan(int dx, int dy) {
    GLfloat factor = 0.05f;
    if (cameraActual) {
        esc->camGeneral->pan(factor*dx,factor*dy);
        update();
    }
}
