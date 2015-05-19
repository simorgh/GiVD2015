19/05/2015	Igor Dzinka / Vicent Roig
===========================
  GiVD - Practica3 README
===========================

GENERAL:
---------------------------
>> Shaders

Creados 3 parejas de ficheros vshader/fshader GLSL.

1. gouraud_fshader.glsl / gouraud_vshader.glsl (Usado para el Flat shading y Gouraud shading, dado que el cambio solo implica recalcar las normales de una forma u otra)

2. phong_vshader.glsl / phong_fshader.glsl -> Usado únicamente para Phong shading, dado que en este caso el cálculo de color se ha de realizar en el fragment shader (e interpolar las normales), de igual modo que el Toon Shader.

3. toon_vshader.glsl / toon_fshader.glsl -> Usado únicamente para el Toon shading, dado que aunque el color también se calcular en el fragment, dado que al tener diferentes umbrales y determinar colores fijos entendemos que es más interesante dejarlo separado del Phong.

La fórmula de color final se realiza en una función aparte ‘computeColors’ incluida en el shader correspondiente.


PARTICULARIDADES:
---------------------------

Los 3 programs son compilados al iniciar el programa y agregados a un array ‘programs’. Al conmutar el shading en función de la tecla activaremos uno u otro. Se controla la activación o no las texturas en los shaders (vshader o fshader dependiendo de cada caso), mediante una variable uniform float (tflag).

Para ello se han implementado en la clase GLwidget los métodos:

    void setProgram(int id, bool text); //bool controla el flag de visualizar textura
    void sendTextureFlag(bool b);	//llamada desde setProgram, pasa el flag al shader.

En la clase Objecte se han implementado los métodos para calcular las normales correspondientes:

    virtual void calculaNormalsFlatShading();
    virtual void calculaNormalsGouraud();

Estos métodos serán llamados desde la clase escena mediante:

    void calculaNormals(normalType type);


- La activación de texturas/material se ejecuta pulsando ALT+[1-4] en lugar de Mayus, dado que dependiendo del SO, la combinación SHIFT+Num es capturada a nivel GUI y puede dar problemas.


>> Otros

- Por defecto el tipo de normales se calcula en modo Gouraud y se visualizan las texturas.

- La primera vez que se calculan las normales no llamamos al método calculaNormalsGouraud(), dado que al estar en el origen (0,0,0) podemos aprovechar que la normal coincide con el punto y lo asignamos directamente.


EXTRAS
——————————————
Implementado el punto adicional para agregar diversas luces, ahora escena tiene un ConjuntLlums, i esta reimplementa el toGPU para 
llamar al toGPU de cada llum, agregado el constructor de llum para especificar el nombre que tendrá el uniform en el shader y así 
poder enviar a cada luz independiente.



CORRECCIONES FEEDBACK Práctica2
---------------------------------
1. Agregada la homogenización de de la gl_Position en el vertex shader.

2. Cambiada la inicialización  de la camara en el metodo 'ini' (setViewport ahora
   recibe la coordenada (0,0), esquina superior de la ventana, en lugar del pmin de
   la capsa contenedora de la escena).

3. Quitado el calculo  de la matriz projection  a la hora de hacer setRotation de la camara

4. Eliminado el calculObs en la función  setRotation de clase Camara, por ser redundante,
   ya que se calcula dentro de la función calculMatriuModelView, que era llamada a continuación.

5. Corregido dant y dpost al hacer setDCamera.

6. Ahora los ángulos de cámara son recuperados en el estado en que habían quedado al alternar entre general/FP.

7. Las acciones de Panning/Zoom-in/Zoom-out pasan a estar habilitadas también en la cámara FP.
