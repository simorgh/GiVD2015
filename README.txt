24/03/2015	Igor Dzinka / Vicent Roig
===========================
  GiVD - Practica1 README
===========================

GENERAL:
------------------------------

- La escena cuenta con un array de elementos, cada vez que agregamos un nuevo Objeto a la escena, éste se guarda en dicho array y se adapta al Widget (adaptaObjecteTamanyWidget), de esta manera, mediante un simple recorrido podemos aplicar una misma transformación.


- Al cargar newSalaBillar(), si existen elementos préviamente cargados, estos son eliminados y se resetea la rotación.

- TaulaBillar se carga correctamente en newSalaBillar(), debido a un problema con el path relativo ://resources/taula.obj, hemos comentado esta parte.

- Se han sobrecargado los métodos necesarios de Objecte, pasándolos a virtual:
    virtual void aplicaTG(mat4 m);
    virtual void aplicaTGPoints(mat4 m);
    virtual void aplicaTGCentrat(mat4 m);

 Cabe destacar que la sobrecarga de aplicaTGCentrat varia en la clase ConjuntBoles, dado que se aplica la transformación respecto al punto central de todo el conjunto de bolas. Esto se consigue precalculando la caja minima contenedora del conjunto (a partir de las cajas mínimas de las bolas contenidas).

- El centro de la escena podría recalcularse en cada rotación, aunque hemos considerado que al tratarse de la misma escena eso no es necesario y simplemente la calculamos al agregar un nuevo objeto (donde ES NECESARIO actualizar la cajaMinima para poder disponer del centro correcto).


TEXTURAS:
------------------------------

- Se ha aplicado un método refinado para disimular el problema del "seam" sobre las texturas de las bolas (este problema proviene del hecho de con contar con suficientes vértices). Hemos seguido el método descrito por el siguiente documento (Michigan State University): https://www.cse.msu.edu/~cse872/tutorial4.html
El problema se da cuando los puntos a interpolar coinciden, una posible solución pasa por duplicar esos vértices de forma que el color queda uniforme entre ellos, esta solución en contraposición busca un punto de equilibro entre un rango (threshold) entre las coordenadas de textura U,J.

- métodos draw() y toGPU() adaptados.

- Objecte implementa método abstracto initTexturas() sobrecargado en Bola.cpp y PlaBase.cpp, también la TaulaBillar, de forma que al cargar las caras carga en negro (obtenido a partir de la textura de bola 8).



MOVIMIENTO:
------------------------------
- El método Play realiza una rotación de 90º sobre la escena (aplicaTGCentrat sobrecargado para aplicar la transformación sobre cada elemento de la escena mediante aplicaTG respecto a su centro), de forma que las transformaciones aplicadas a la bola blanca sean coherentes.

- En la clase Objecte se han añadido los métodos void backupPoints(); void restorePoints(); para poder guardar un backup del array points antes de detectar si existe o no colisión. Para esto contamos con un point4 array (pointsTmp) inicializado en el constructor.

- Se han tratado las colisiones con los límites del plano. Y se ha aplicado movimiento horizontal/vertical sobre la bola blanca.