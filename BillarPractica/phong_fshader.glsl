#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

IN vec4 position;
IN vec4 pNormal;
IN vec2 v_texcoord;
uniform sampler2D texMap;

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

uniform tipusLlum light_1;
uniform tipusLlum light_2;

uniform tipusMaterial material;
uniform vec3 Ia_global;
uniform float tflag;

vec4 computeColor(tipusLlum light, tipusMaterial mat, vec4 v, vec4 dir) {
    float d = length(dir);
    vec4 l = normalize(dir);
    vec4 h = (l+v) / length(l+v);
    vec4 n = normalize(pNormal);

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
    vec4 iag = vec4(Ia_global, 1.0);
    vec4 color = iag + computeColor(light_1, material, position, light_1.dir) + computeColor(light_2, material, position, light_2.dir);

    if (tflag == 1.0) gl_FragColor = color * texture2D(texMap, v_texcoord);
    else gl_FragColor = color;

    //gl_FragColor = pNormal;
}

