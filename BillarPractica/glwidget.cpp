#include <math.h>
#include <glwidget.h>
#include <QtDebug>
#include <QString>


GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)

{
    setFocusPolicy( Qt::StrongFocus );
    esc = new Escena();

    xRot = 0;
    yRot = 0;
    zRot = 0;

    a = 20.0;
    h = 20.0;
    p = 20.0;

    clearColor = Qt::black;
    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

    program = 0;
    moviment = false;

}


GLWidget::~GLWidget()
{
    makeCurrent();
    delete esc;
}


// Create a GLSL program object from vertex and fragment shader files
void GLWidget::InitShader(const char* vShaderFile, const char* fShaderFile){

    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);

    // Compilació del vertex shader
    vshader->compileSourceFile(vShaderFile);
    fshader->compileSourceFile(fShaderFile);

    program = new QGLShaderProgram(this);
    program->addShader(vshader);
    program->addShader(fshader);

    program->link();    // muntatge del shader en el pipeline grafic per a ser usat
    program->bind();    // unió del shader al pipeline gràfic
}

void GLWidget::initShadersGPU(){
    // Carrega dels shaders i posa a punt per utilitzar els programes carregats a la GPU
   InitShader( "://vshader1.glsl", "://fshader1.glsl" );

}


QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const

{
    return QSize(400, 400);
}


static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}


void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        update();
    }
}


void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        update();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        update();
    }
}


void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_RGBA);
    glEnable(GL_DOUBLE);

    qDebug() <<"inicialitzant els shaders";
    initShadersGPU();

    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void GLWidget::paintGL()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   program->setUniformValue("texture", 0);

   qNormalizeAngle(xRot);
   qNormalizeAngle(yRot);
   qNormalizeAngle(zRot);

   mat4 transform = ( RotateX( xRot / 16.0 ) *
                       RotateY( yRot / 16.0 ) *
                       RotateZ( zRot / 16.0 ) );

   // A modificar si cal girar tots els objectes
   esc->aplicaTGCentrat(transform);
   esc->draw();
}


void GLWidget::resizeGL(int width, int height)
{
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


void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 0.1 * dy);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 0.1 * dy);
        setZRotation(zRot + 0.1 * dx);
    }
    lastPos = event->pos();
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
    // Metode a implementar
    switch ( event->key() )
    {
        case Qt::Key_Up:

            break;
        case Qt::Key_Down:

            break;
        case Qt::Key_Left:

            break;
        case Qt::Key_Right:

            break;
    }
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    // Metode a implementar en el cas que es mogui la bola

}



void GLWidget::adaptaObjecteTamanyWidget(Objecte *obj)
{
    // Metode a implementar
    double escala = 2/20.;

    mat4 m = Scale(escala, escala, escala);
    vec3 centre = vec3(obj->capsa.pmin.x + obj->capsa.a/2.,obj->capsa.pmin.y + obj->capsa.h/2., obj->capsa.pmin.z + obj->capsa.p/2.);
    //std::cout << "cente( " << centre.x << " , " << centre.y << " , " << centre.z << ")" << endl;

    // Contrucció de la matriu de translació al centre
    mat4 t1 = Common::Translate(-centre.x, -centre.y, -centre.z);
    mat4 t2 = Common::Translate( centre.x*escala,  centre.y*escala,  centre.z*escala);

    obj->aplicaTGPoints(t2*m*t1);
    qDebug()<< "Calculando Capsa3D desde AdaptaObjecteTamanyWidget en GLWidget"<< endl;
    obj->calculCapsa3D();
}

void GLWidget::newObjecte(Objecte * obj)
{
    adaptaObjecteTamanyWidget(obj);
    obj->toGPU(program);
    esc->addObjecte(obj);

    updateGL();
}

void GLWidget::newPlaBase()
{
    // Metode que crea un objecte PlaBase poligon amb el punt central al (0,0,0) i perpendicular a Y=0
    PlaBase *pla;

    pla = new PlaBase();
    newObjecte(pla);
}

void GLWidget::newObj(QString fichero)
{
    // Metode que carrega un fitxer .obj llegit de disc
    TaulaBillar *obj;
    obj = new TaulaBillar(fichero);

    obj->toGPU(program);
    esc->addObjecte(obj);
    updateGL();
}

void GLWidget::newBola()
{
    // Metode que crea la Bola blanca de joc
    Bola *obj;

    obj = new Bola();
    newObjecte(obj);
}

void GLWidget::newConjuntBoles()
{
    // Metode que crea les 15 Boles del billar america
    ConjuntBoles *obj;

    obj = new ConjuntBoles();
    newObjecte(obj);
}

void GLWidget::newSalaBillar()
{
    // Metode que construeix tota la sala de billar: taula, 15 boles i bola blanca
    clearSalaBillar();

    // add game elements here:
    newPlaBase();
    newBola();
    newConjuntBoles();


    newObj("://resources/taula.obj");
}

void GLWidget::clearSalaBillar(){
    // in case of needed clear old elements and reset Escena
    if(!esc->elements.empty()){
        esc->elements.clear();

        esc->capsaMinima.pmin[0]=0; esc->capsaMinima.pmin[1] = 0; esc->capsaMinima.pmin[2]=0;
        esc->capsaMinima.a = 1; esc->capsaMinima.h = 1; esc->capsaMinima.p = 1;
        xRot = 0; yRot = 0; zRot = 0;
    }
}

// Metode per iniciar la dinàmica del joc
void GLWidget::Play()
{

}
