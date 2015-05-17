#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

// fragment shader
in vec4 lightDir;
in vec4 normal;
in vec2 v_texcoord;
uniform sampler2D texMap;

void main()
{
    float intensity;
    vec4 color;
    intensity = dot(lightDir,normalize(normal));
    if (intensity > 0.95)
        color = vec4(1.0,1.0,1.0,1.0);
    else if (intensity > 0.5)
        color = vec4(0.8,0.8,0.8,1.0);
    else if (intensity > 0.25)
        color = vec4(0.5,0.5,0.5,1.0);
    else
    color = vec4(0.3,0.3,0.3,1.0);
    gl_FragColor = color * texture2D(texMap, v_texcoord);

}
