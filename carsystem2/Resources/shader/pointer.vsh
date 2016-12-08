attribute vec4  a_position;
varying vec4 v_fragmentColor;

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_fragmentColor = vec4(1.0,1.0,1.0,1.0);
}
