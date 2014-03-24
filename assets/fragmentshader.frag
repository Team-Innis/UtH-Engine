#version 100
precision mediump float;

uniform sampler2D unifSampler;

varying vec2 texCoord;
varying vec4 color;

void main() 
{
	float a = texture2D(unifSampler,texCoord).a;
	gl_FragColor.rgb = texture2D(unifSampler,texCoord).rgb * color.rgb;
	gl_FragColor.a = a;

	//gl_FragColor = vec4(texCoord, 0.0, 1.0);
}