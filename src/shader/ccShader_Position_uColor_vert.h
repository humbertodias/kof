/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

"													\n\
attribute vec4 a_position;							\n\
uniform	vec4 u_color;								\n\
uniform float u_pointSize;							\n\
													\n\
#ifdef GL_ES										\n\
varying lowp vec4 v_fragmentColor;					\n\
#else												\n\
varying vec4 v_fragmentColor;						\n\
#endif												\n\
													\n\
void main()											\n\
{													\n\
    gl_Position = CC_MVPMatrix * a_position;		\n\
	gl_PointSize = u_pointSize;						\n\
	v_fragmentColor = u_color;						\n\
}													\n\
";
