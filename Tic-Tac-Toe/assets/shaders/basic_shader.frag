// ##############################
// >>>>| basic_shader.frag |<<<<<
// ##############################

// Shader version
#version 330 core

uniform sampler2D textureSampler;

// Input
in vec3 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

// Output
out vec4 color;

// Shader entry point
void main() {

	vec4 textureColor = texture(textureSampler, fragmentUV);
	
	color = textureColor * fragmentColor;

}