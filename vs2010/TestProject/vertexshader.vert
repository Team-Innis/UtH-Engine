attribute vec3 vPosition;
attribute vec2 vTexCoord;

uniform mat4 Translation;
uniform mat4 Rotation;
uniform mat4 Scale;
uniform mat4 Projection;

varying vec2 texCoord;

void main() 
{
	texCoord = vTexCoord;

	mat4 model = Translation * Rotation * Scale;

	vec4 pos = Projection * model * vec4(vPosition, 1.0);
	
	gl_Position = pos;
}