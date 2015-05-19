#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

// fragment shader
IN vec4 lightDir;
IN vec4 normal;
IN vec2 v_texcoord;

uniform sampler2D texMap;
uniform float tflag;

void main() {
    float intensity;
    vec4 color;
    intensity = dot(lightDir, normalize(normal));

    if(intensity > 0.80)        color = vec4(1.0, 1.0, 1.0, 1.0);
    else if (intensity > 0.17)  color = vec4(0.9, 0.9, 0.9, 1.0);
    else if (intensity > 0.15)  color = vec4(0.7, 0.7, 0.7, 1.0);
    else if (intensity > 0.10)  color = vec4(0.5, 0.5, 0.5, 1.0);
    else                        color = vec4(0.3, 0.3, 0.3, 1.0);

    if (tflag == 1.0) gl_FragColor = color * texture2D(texMap, v_texcoord);
    else gl_FragColor = color;
}
