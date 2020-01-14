#type vertex
#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoord;
layout (location = 2) in vec3 color;
layout (location = 3) in mat4 transform;

out vec2 pTexCoords;
out vec4 pColor;

uniform mat4 uProjection;

void main(void) {
	pTexCoords = texcoord;
	pColor = vec4(color, 1.0f);
	gl_Position = uProjection * transform * vec4(position, 1.0f);
}

#type fragment
#version 430 core

in vec2 pTexCoords;
in vec4 pColor;

out vec4 outColor;

uniform sampler2D uTexture;

void main() {
	outColor = texture(uTexture, pTexCoords) *pColor;
}
