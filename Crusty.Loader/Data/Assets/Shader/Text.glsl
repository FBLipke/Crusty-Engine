#type vertex
#version 430
layout (location = 0) in vec4 vertex;

out vec2 pTexCoords;
uniform mat4 uProjection;

void main()
{
	gl_Position = uProjection * vec4(vertex.xy, 0.0f, 1.0f);
	pTexCoords = vertex.zw;
}

#type fragment
#version 430

in vec2 pTexCoords;

uniform sampler2D uTexture;
uniform vec3 uTextColor;

out vec4 outColor;

void main()
{
	vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(uTexture, pTexCoords).r);
	outColor = vec4(uTextColor, 1.0f) * sampled;
}
