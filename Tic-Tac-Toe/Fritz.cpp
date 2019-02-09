// ##############################
// >>>>>>>>| Fritz.cpp |<<<<<<<<<
// ##############################

// Standard Library =============
#include <iostream>
// Project Headers ==============
#include "Fritz.h"
// ==============================

// Prints an error to the command prompt
GLvoid printError(std::string errorString, std::string details /* "= " */, GLint errorCode /* = -1 */) {

	// Let the user know there is a problem
	std::printf("A FATAL ERROR HAS OCCURED:");

	// Give us the error Code
	if (errorCode > -1) {
		std::printf("Error Code %d\n", errorCode);
	}

	// What happened?
	std::printf("\n%s\n", errorString.c_str());

	// Give us information about the error
	if (details != "") {
		std::printf("%s\n", details.c_str());
	}

	// Prompt the user to quit
	std::string tmp;
	std::printf("HIT ENTER TO QUIT");
	std::getline(std::cin, tmp);

	// Quit the program
	exit(errorCode);

}