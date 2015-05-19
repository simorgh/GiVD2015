#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

struct tipusLlum {
    vec4 position;
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
IN vec4 vNormal;
IN vec2 vCoordTexture;
OUT vec4 normal;
OUT vec2 v_texcoord;
OUT vec4 lightDir;

uniform tipusLlum light_1;
uniform tipusLlum light_2;

uniform tipusMaterial material;
uniform vec3 Ia_global;
uniform mat4 model_view;
uniform mat4 projection;

void main() {
    gl_Position = projection * model_view * vPosition;

    normal = vNormal;
    lightDir =  light_1.dir;
    v_texcoord = vCoordTexture;
}
