#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

IN vec4 color;
IN vec2 v_texcoord;

uniform sampler2D texMap;

void main() {
    //gl_FragColor = 0.6*color + 0.4*texture2D(texMap, v_texcoord);
    gl_FragColor = color * texture2D(texMap, v_texcoord);


    /*
     * Testing...
     * * * * */
    //gl_FragColor = color; /* direct vshare input color */
    //gl_FragColor = texture2D(texMap, v_texcoord); /* pure texture */
}
