#type vertex
#version 430 core
in vec2 position;
in vec2 texcoord;

out vec2 Texcoord;

void main()
{
	Texcoord = texcoord;
	gl_Position = vec4(position, 0.0f, 1.0f);
}

#type fragment
#version 430 core

in vec2 Texcoord;
out vec4 outColor;

uniform sampler2D texFramebuffer;

void main()
{
	outColor = texture(texFramebuffer, Texcoord);
}
