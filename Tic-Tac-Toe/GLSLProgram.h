// ##############################
// >>>>>>| GLSLProgram.h |<<<<<<<
// ##############################

#pragma once

// Dependencies =================
#include <GL/glew.h>
// ==============================

// "GLSL Shader Program" Class
class GLSLProgram {

private:

	// Variables
	GLuint m_programID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;
	GLint m_numAttributes;

	// Functions
	GLvoid loadShader(std::string ShaderSource, GLuint shaderID); ///< Reads in a shader file
	

public:

	// Class Defaults
	GLSLProgram(); ///< Class Constructor
	~GLSLProgram(); ///< Class Destructor

	// Functions
	GLvoid compileSource(std::string& vertexSource, std::string& fragmentSource); ///< Compiles shaders from strings
	GLvoid compileFiles(const GLchar* vertexShaderFilePath, const GLchar* fragmentShaderFilePath); ///< Compiles Shaders from files
	GLint getUniformLocation(const GLchar* uniformName); ///< Finds a uniform variable in the shader program
	GLvoid addAttributes(const GLchar* attribName); ///< Grabs attributes from the shader
	GLvoid link(); ///< Links shaders to the program
	GLvoid bind(); ///< Binds the shader program to renderer
	GLvoid unbind(); ///< Unbinds the shader program from the renderer

};

