#pragma once
/**
 * @file Prerequisites.h
 * @brief Inclusiones y definiciones base para el motor de juego, incluyendo tipos de datos, macros utilitarias y enumeraciones.
 *
 * Este archivo centraliza las dependencias esenciales como punteros inteligentes propios del motor,
 * bibliotecas gráficas (SFML, ImGui) y utilidades para depuración y manejo seguro de punteros.
 * También define enumeraciones comunes como `ShapeType`.
 *
 * @author Hannin Abarca
 */

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

 /**
  * @brief Libera un puntero y lo establece en nullptr si no es nulo.
  * @param x Puntero a liberar.
  */
#define SAFE_PTR_RELEASE(x) \
	if (x != nullptr) { delete x; x = nullptr; }

  /**
   * @brief Macro para mostrar un mensaje de creación de recurso en consola.
   * @param classObj Nombre de la clase.
   * @param method Nombre del método.
   * @param state Estado o descripción de la creación.
   */
#define MESSAGE(classObj, method, state)                        \
{                                                               \
	std::ostringstream os_;                                     \
	os_ << classObj << "::" << method << " : "                  \
		<< "[CREATION OF RESOURCE" << ": " << state << "] \n";  \
	std::cerr << os_.str();                                     \
}

   /**
	* @brief Macro para mostrar un error en consola y finalizar el programa.
	* @param classObj Nombre de la clase.
	* @param method Nombre del método.
	* @param errorMSG Mensaje descriptivo del error.
	*/
#define ERROR(classObj, method, errorMSG)                          \
{                                                                  \
	std::ostringstream os_;                                        \
	os_ << "ERROR : " << classObj << "::" << method << " : "       \
		<< "  Error in data from params [" << errorMSG << "] \n";  \
	std::cerr << os_.str();                                        \
	exit(1);                                                       \
}

	/**
	 * @enum ShapeType
	 * @brief Tipos de formas geométricas manejadas por el motor.
	 */
enum ShapeType {
	EMPTY = 0,    /**< Sin forma asignada. */
	CIRCLE = 1,   /**< Forma circular. */
	RECTANGLE = 2,/**< Forma rectangular. */
	TRIANGLE = 3, /**< Forma triangular. */
	POLYGON = 4   /**< Forma poligonal personalizada. */
};
