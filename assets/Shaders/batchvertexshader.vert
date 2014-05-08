uniform mat4 unifProjection;

attribute vec3 attrPosition;
attribute vec2 attrUV;
attribute vec4 attrColor;

varying vec2 texCoord;
varying vec4 color;

void main() 
{
	texCoord = attrUV;
	color = attrColor;
	
	gl_Position = vec4(attrPosition.xy, 0.0, 1.0) * unifProjection;
}