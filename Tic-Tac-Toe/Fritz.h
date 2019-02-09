// ##############################
// >>>>>>>>>| Fritz.h |<<<<<<<<<<
// ##############################

#pragma once

// Standard Library =============
#include <string>
// Dependencies =================
#include <GL/glew.h>
// ==============================

// Functions
extern GLvoid printError(std::string errorString, std::string details = "", GLint errorCode = -1); ///< Prints an error to the command prompt
