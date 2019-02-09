// ##############################
// >>>>>| GLSLProgram.cpp |<<<<<<
// ##############################

// Standard Library =============
#include <fstream>
#include <vector>
// Project Headers ==============
#include "Fritz.h"
#include "GLSLProgram.h"
#include "IOManager.h"
// ==============================

// Class Constructor
GLSLProgram::GLSLProgram() :
	m_programID(0),
	m_vertexShaderID(0),
	m_fragmentShaderID(0),
	m_numAttributes(0)
{ /* Empty */ }

// Class Destructor
GLSLProgram::~GLSLProgram()
{ /* Empty */ }

// Reads in a shader file
GLvoid GLSLProgram::loadShader(std::string shaderSource, GLuint shaderID) {

	// Associate the shader data with the shader ID
	const GLchar* shaderData = shaderSource.c_str();
	glShaderSource(shaderID, 1, &shaderData, nullptr);

	// Compile the shader
	glCompileShader(shaderID);

	// Check integrety of shader
	GLint success = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	// Get error log if compilation failed
	if (success == GL_FALSE) {

		// Get the Length of the error log
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// Get the error log
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &(errorLog[0]));

		// Delete the shader
		glDeleteShader(shaderID);

		// Print out the error log
		printError("Failed to compile shader ", &errorLog[0], 202);
	}
}

// Compiles shaders from strings
GLvoid GLSLProgram::compileSource(std::string& vertexSource, std::string& fragmentSource) {

	// Generate vertex shader id
	if (m_vertexShaderID == 0) m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (m_fragmentShaderID == 0) m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Generate the program
	if (m_programID == 0) m_programID = glCreateProgram();

	// Compile the shaders
	loadShader(vertexSource, m_vertexShaderID);
	loadShader(fragmentSource, m_fragmentShaderID);

}

// Compiles Shaders
GLvoid GLSLProgram::compileFiles(const GLchar* vertexShaderFilePath, const GLchar* fragmentShaderFilePath) {

	// Create buffers containing shader data
	std::string vertexSource;
	std::string fragmentSource;

	// Load file data into shader buffer
	IOManager::readFileToBuffer(vertexShaderFilePath, vertexSource);
	IOManager::readFileToBuffer(fragmentShaderFilePath, fragmentSource);

	// Compile the shaders found in buffers
	compileSource(vertexSource, fragmentSource);

}

// Finds a uniform variable in the shader program
GLint GLSLProgram::getUniformLocation(const GLchar* uniformName) {

	// Give the value of the uniform found in the shader program
	return glGetUniformLocation(m_programID, uniformName);

}

// Grabs attributes from the shader
GLvoid GLSLProgram::addAttributes(const GLchar* attribName) {

	// Look for the attribute in the program and assign an attribute ID to it
	glBindAttribLocation(m_programID, m_numAttributes++, attribName);

}

// Links shaders to the program
GLvoid GLSLProgram::link() {

	// Attach shaders to program
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);
	
	// Link the program
	glLinkProgram(m_programID);

	// Check linking status
	GLint success = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);

	// Grab error log if compilation failed
	if (success == GL_FALSE) {

		// Get the length of the error log
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// Get the error log
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &(errorLog[0]));

		// Detach shaders from program
		glDetachShader(m_programID, m_vertexShaderID);
		glDetachShader(m_programID, m_fragmentShaderID);

		// Delete the shaders
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);

		// Delete the program
		glDeleteProgram(m_programID);

		// Print out the error log
		printError("Shaders failed to link to the program", &errorLog[0], 203);

	}

	// Delete the shaders
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);

}

// Tell openGL to use this shader for rendering graphics
GLvoid GLSLProgram::bind() {

	if (m_programID != 0) glUseProgram(m_programID);

}

// Tell openGL to stop using this shader for the program
GLvoid GLSLProgram::unbind() {


	if (m_programID != 0) glUseProgram(0);

}
