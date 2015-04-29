#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif


struct tipusLlum {
    vec4 posicio;
    vec4 dir;
    float angle;
    float a,b,c;
    vec3 ambient;
    vec3 specular;
    vec3 diffuse;
};

struct tipusMaterial {
    vec3 ambient;
    vec3 specular;
    vec3 diffuse;
    float reflection;
};


IN vec4 vPosition;
//IN vec4 vColor;
IN vec4 vNormal;
IN vec2 vCoordTexture;
OUT vec4 color;
OUT vec2 v_texcoord;

uniform tipusLlum light;
uniform tipusMaterial material;

uniform vec3 Ia_global;
uniform vec3 ka_global;

uniform mat4 model_view;
uniform mat4 projection;


void main() {
  gl_Position = projection*model_view*vPosition;
  color = vColor;

  // Pas de les coordenades de textura al fragment shader
  // El valor del color i les coordenades de textura s'interpolaran automaticament
  // en els fragments interiors a les cares dels polígons
  v_texcoord = vCoordTexture;
}
