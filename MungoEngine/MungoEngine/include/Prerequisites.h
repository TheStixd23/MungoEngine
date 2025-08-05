#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <map>
#include <fstream>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Memory/TSharedPointer.h"
#include "Memory/TWeakPointer.h"
#include "Memory/TStaticPtr.h"
#include "Memory/TUniquePtr.h"

#include <imgui.h>
#include <imgui-SFML.h>


// ========================
// Macros
// ========================

/**
 * @brief Safely releases a pointer and sets it to nullptr.
 *
 * Example usage:
 * @code
 * SAFE_PTR_RELEASE(myPointer);
 * @endcode
 */
#define SAFE_PTR_RELEASE(x) \
	if (x != nullptr) { delete x; x = nullptr; }

 /**
	* @brief Outputs a formatted message indicating the state of a
	* resource creation.
	*
	* @param classObj The name of the class.
	* @param method The method where the message is generated.
	* @param state The current state or detail of the resource creation.
	*
	* Example usage:
	* @code
	* MESSAGE("MyClass", "initialize", "Success");
	* @endcode
	*/
#define MESSAGE(classObj, method, state)                        \
{                                                               \
	std::ostringstream os_;                                     \
	os_ << classObj << "::" << method << " : "                  \
		<< "[CREATION OF RESOURCE" << ": " << state << "] \n";  \
	std::cerr << os_.str();                                     \
}

	/**
	 * @brief Outputs a formatted error message and exits the application.
	 *
	 * @param classObj The name of the class.
	 * @param method The method where the error occurred.
	 * @param errorMSG A description of the error.
	 *
	 * Example usage:
	 * @code
	 * ERROR("MyClass", "loadFile", "File not found");
	 * @endcode
	 */
#define ERROR(classObj, method, errorMSG)                          \
{                                                                  \
	std::ostringstream os_;                                        \
	os_ << "ERROR : " << classObj << "::" << method << " : "       \
		<< "  Error in data from params [" << errorMSG << "] \n";  \
	std::cerr << os_.str();                                        \
	exit(1);                                                       \
}

	 // ========================
	 // Enums
	 // ========================

	 /**
		* @enum ShapeType
		* @brief Defines the possible shape types that can be
		* rendered or created in the system.
		*/
enum
	ShapeType {
	EMPTY = 0,     ///< No shape defined.
	CIRCLE = 1,    ///< Circle shape.
	RECTANGLE = 2, ///< Rectangle shape.
	TRIANGLE = 3,  ///< Triangle shape.
	POLYGON = 4    ///< Custom polygon shape.
};