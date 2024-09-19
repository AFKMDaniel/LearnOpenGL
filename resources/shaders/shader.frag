#version 330 core

in vec2 texCoord; 

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float alpha;

void main()
{
	FragColor = mix(texture(texture0, texCoord), texture(texture1, vec2(1.0 - texCoord.x, texCoord.y)), alpha);
}
