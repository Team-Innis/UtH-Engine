precision mediump float;

uniform sampler2D unifSampler;

varying vec2 texCoord;

void main() 
{
	gl_FragColor = texture2D(unifSampler,texCoord);

	//gl_FragColor = vec4(texCoord, 0.0, 1.0);
}