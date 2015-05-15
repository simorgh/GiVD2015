28/04/2015	Igor Dzinka / Vicent Roig
===========================
  GiVD - Practica2 README
===========================

GENERAL:
------------------------------
- Se ha eliminado el proceso de adaptaObjecteTamanyWidget() (gracias a la implementación de la cámara, ya no va a ser necesario).

- Al cargar newSalaBillar(), si existen elementos préviamente cargados, estos son eliminados y se resetea la rotación.

- TaulaBillar se carga correctamente en newSalaBillar(), debido a un problema con el path relativo ://resources/taula.obj, hemos comentado esta parte.

- Implementat el extra de rotació de la bola blanca al moure's. Per tal de que es pugui visualitzar la rotació, hem posat a la bola blanca la textura de la bola 15.

- Al nostre cas, hem decidit que la camara general tingui la projecció paral·lela i la camara en primera persona la projecció perspectiva.

- Com a correcció de la primera pràctica hem implementat com a mètode abstracte hasCollided() a la classe Objecte per tal de que tots els objectes puguin 
  sobreescriure  i detectar la colisió la seva corresponent col·lisión en funció del centre de la seva capsaMínima.

- la camara en primera persona  s'inicialitza en el moment que faci falta, es a dir quan es cambia a camara en primera persona per primer cop.

- Actualment el botó  de "Play" s'ha deixat sense implementació. L'usuari pot moure la bola directament quan s'hagi carregat la sala de billar.

- Hem considerat deixar la rotació també a la càmara en primera persona, d'aquesta manera podem seguir la bola blanca i rotar la càmara per visualitzar millor l'escena. El zoom in / zoom out no estarà actiu, al igual que el paning, donat que entenem que la gràcia d'aquesta càmera resideix en tenir una visualització fixe en quant a proximitat i ben centrada respecte a la bola blanca.

CORRECCIONES:
------------------------------
1. Agregada la homogenización de de la gl_Position en el vertex shader.
2. Cambiada la inicialización  de la camara en el metodo 'ini' (setViewport ahora recibe la coordenada (0,0), esquina superior de la ventana, en lugar del pmin de la capsa contenedora de la escena).
3. Quitado el calculo  de la matriz projection  a la hora de hacer setRotation de la cámara.
4. Eliminado el calculObs en la función  setRotation de clase Camara, por ser redundante, ya que se calcula dentro de la función calculMatriuModelView, que era llamada a continuación.
5. corregido dant y dpost al hacer setDCamera;
6. Recuperación los ángulos (guardados en cámara) en función de la cámara a la hora de hacer rotaciones.
