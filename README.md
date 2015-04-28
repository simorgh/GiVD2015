GiVD - curs 2014-2015 – Pràctica 3
======================================
##Pràctica número 3: Il·luminació de l'escena

Tema: Implementació de la il·luminació d'una escena amb diferents models locals de shading: flat, Gouraud, Phong i toon shading, tenint en compte les textures.

###Objectiu:
Visualització de la taula de billar amb diferents shaders que permetin els diferents tipus
d'il·luminació. Aprendre a utilitzar els shaders per a programar els models d'il·luminació. La pràctica té com objectiu aprendre a il·luminar l'escena amb diferents models de shading. Per això s'aprendrà a passar diferents valors al vertex shader i al fragment shader. S'inclouran dues noves classes: la classe llum, que representa tots els atributs d'una llum i la classe material, que codificarà els atributs bàsics que codifiquen un material (component difusa, component especular i component ambient).

Fins a la pràctica 2, heu inclòs nous objectes en una escena i heu codificat la càmera per a poder visualitzar la taula de billar des de qualsevol posició i amb diferents opcions de zoom. En aquesta tercera pràctica s'inclou en l'escena una llum i a cada bola de billar i al pla base, el seu material associat.
Per a començar a desenvolupar el codi d'aquesta tercera pràctica, es pot utilitzar el codi realitzat a la pràctica 2 fins a la primera visualització usant la càmera general.

###La pràctica 3 es composa dels següents exercicis:

*Implementació d'una nova classe anomenada llum, que permeti emmagatzemar tots els atributs necessaris per a codificar una llum puntual, una llum direccional, una llum de tipus spot-light i amb possible atenuació en profunditat.
*Implementació d'una nova classe material que permeti representar les característiques del material d'un objecte.
*Implementació dels càlculs d’il·luminació segons les següents tècniques: flat, gouraud, phong- shading i toon-shading tenint en compte les textures.