// ##############################
// >>>>| basic_shader.vert |<<<<<
// ##############################

// Shader version
#version 330 core

// Input
in vec3 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

// Output
out vec3 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

// Shader entry point
void main() {

	// Load position data into openGL
	gl_Position = vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0);

	// pass position to fragment shader
	fragmentPosition = vertexPosition;

	// Pass color to fragment shader
	fragmentColor = vertexColor;

	// Pass UV coordinates to fragment shader
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);

}