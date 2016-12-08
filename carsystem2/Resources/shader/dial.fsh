varying vec4 v_fragmentColor;
varying float v_discardAlpha;
void main()
{
    if (v_fragmentColor.a < v_discardAlpha) {
        discard;
    } else {
        gl_FragColor = vec4(v_fragmentColor.r,v_fragmentColor.g,v_fragmentColor.b,1.0);
    }
}
