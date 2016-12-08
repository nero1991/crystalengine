attribute vec4  a_position;
attribute float a_fullR;
attribute float a_discardR;
attribute vec4  a_cirlceOrigin;

varying vec4 v_fragmentColor;
varying float v_discardAlpha;

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    float alpha = abs(distance(a_position,a_cirlceOrigin) / a_fullR);
    if (alpha > 1.0) {
        alpha = 1.0;
    }
    v_discardAlpha = a_discardR;
    v_fragmentColor = vec4(1.0,0.0,0.0, distance(a_position,a_cirlceOrigin) / a_fullR );
}
