#version 100
precision mediump float;

uniform sampler2D unifSampler;

varying vec2 texCoord;
varying vec4 color;
varying float enableTexture;

void main() 
{
	if(enableTexture > 0.0)
		gl_FragColor = texture2D(unifSampler,texCoord) * color;
	else
		gl_FragColor = color;
}