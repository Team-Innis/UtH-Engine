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

	//mat4 model = unifTranslation * unifRotation * unifScale;

	//vec4 pos = unifProjection * model * vec4(attrPosition, 1.0);
	
	gl_Position = unifModel * vec4(attrPosition, 1.0);
}