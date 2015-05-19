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
OUT vec4 color;
OUT vec2 v_texcoord;

uniform tipusLlum light_1;
uniform tipusLlum light_2;

uniform tipusMaterial material;
uniform vec3 Ia_global;

uniform mat4 model_view;
uniform mat4 projection;

vec4 computeColor(tipusLlum light, tipusMaterial mat, vec4 v, vec4 dir) {
    float d = length(dir);
    vec4 l = normalize(dir);
    vec4 h = (l+v) / length(l+v);
    vec4 n = normalize(vNormal);

    vec4 ks = vec4(mat.specular, 0);
    vec4 kd = vec4(mat.diffuse, 0);
    vec4 ka = vec4(mat.ambient, 0);

    vec4 Ia = vec4(light.ambient, 1.0);
    vec4 Is = vec4(light.specular, 1.0);
    vec4 Id = vec4(light.diffuse, 1.0);

    return ( 1.0 / (light.a*d*d+light.b*d+light.c)) *
            ( (kd*Id) * max(dot(l, n), 0.0) + (ks*Is) * max(pow((dot(n,h)) , material.reflection), 0.0) + ka * Ia );
}


void main() {
    gl_Position = projection * model_view * vPosition;

    //gl_Position /= gl_Position.w;

    vec4 v = normalize( model_view * vPosition );
    vec4 dir_1 = light_1.position - vPosition;
    vec4 dir_2 = light_2.position - vPosition;


    vec4 iag = vec4(Ia_global, 1.0);

    color = iag + computeColor(light_1, material, v, dir_1) + computeColor(light_2, material, v, dir_2);
    v_texcoord = vCoordTexture;

    //color = vNormal;
}
