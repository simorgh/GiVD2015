#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif


IN vec4 vNormal;
IN vec4 vPosition;
IN vec2 vCoordTexture;
OUT vec4 pNormal;
OUT vec4 position;
OUT vec2 v_texcoord;

uniform mat4 model_view;
uniform mat4 projection;

void main() {
    gl_Position = projection * model_view * vPosition;
    //gl_Position /= gl_Position.w;

   /**
    * Output to be interpolated
    **/
    pNormal = vNormal;
    position = gl_Position;
    v_texcoord = vCoordTexture;
}
