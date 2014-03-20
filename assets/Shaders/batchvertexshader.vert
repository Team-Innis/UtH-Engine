#version 100
uniform mat4 unifProjection;
uniform vec4 unifColor;

attribute vec3 attrPosition;
attribute vec2 attrUV;

varying vec2 texCoord;
varying vec4 color;

void main() 
{
	texCoord = attrUV;
	color = unifColor;
	
	gl_Position = vec4(attrPosition, 1.0) * unifProjection;
}