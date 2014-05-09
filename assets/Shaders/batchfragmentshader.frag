uniform sampler2D unifSampler;

varying vec2 texCoord;
varying vec4 color;

void main() 
{
	gl_FragColor = texture2D(unifSampler, texCoord) * color;
}