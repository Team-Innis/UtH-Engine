uniform sampler2D unifSampler;

varying vec2 texCoord;
varying vec4 color;
varying float enableTexture; // 1 if true, 0 if false

void main() 
{
	gl_FragColor =	enableTexture * (texture2D(unifSampler,texCoord) * color)
	+ ((1.0 - enableTexture) * 	color);
}