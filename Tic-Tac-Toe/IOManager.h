// ##############################
// >>>>>>>| IOManager.h |<<<<<<<<
// ##############################

#pragma once

// Standard Library =============
#include <string>
#include <vector>
// Dependencies =================
#include <GL/glew.h>
// ==============================

// "Input / Output Manager" Class
class IOManager {

public:

	// Functions
	static GLboolean readFileToBuffer(std::string filePath, std::vector<GLubyte>& buffer); ///< Reads file data into a vector of unsigned characters
	static GLboolean readFileToBuffer(std::string filePath, std::string& buffer); ///< Reads file data into a string

	// Class Deafaults
	IOManager(); ///< Class Constructor
	~IOManager(); ///< Class Destructor
};

