#version 100
precision mediump float;

uniform sampler2D unifSampler;

varying vec2 texCoord;
varying vec4 color;

void main() 
{
	gl_FragColor = color;
}