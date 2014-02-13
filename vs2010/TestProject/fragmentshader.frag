uniform sampler2D texSampler;

varying vec2 texCoord;

void main() 
{
	gl_FragColor = texture2D(texSampler,texCoord);
}