attribute vec3 attrPosition;
attribute vec2 attrUV;

uniform mat4 unifModel;
uniform mat4 unifProjection;

uniform vec4 unifColor;

varying vec2 texCoord;
varying vec4 color;

void main() 
{
	texCoord = attrUV;
	color = unifColor;

	//gl_Position = vec4(attrPosition, 1.0);

	//gl_Position *= unifModel;
	//gl_Position *= unifProjection;

	vec4 pos =  vec4(attrPosition, 1.0) * unifModel * unifProjection;
	
	gl_Position = pos;
}