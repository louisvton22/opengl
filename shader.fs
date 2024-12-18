#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixf;
void main()
{
	// flip only smileyface horizontally
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(-TexCoord.x,TexCoord.y)), 0.2);

	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixf);
}
