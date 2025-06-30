/**
 * @file Prerequisites.h
 * @author Hannin Abarca
 * @brief Archivo de inclusi�n de librer�as est�ndar y macros comunes para el proyecto
 * @version 1.0
 * @date 2025-06-01
 */

#pragma once

 // Librer�as est�ndar
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <map>
#include <fstream>
#include <unordered_map>
#include <cmath>
#include <cassert>

// Librer�as de terceros
#include <SFML/Graphics.hpp>

// Macros

/**
 * @brief Macro para liberar punteros de forma segura
 *
 * Libera el puntero si no es nullptr y luego lo pone en nullptr
 */
#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

 /**
  * @brief Macro para mostrar mensajes informativos en consola
  *
  * @param classObj Nombre de la clase u objeto
  * @param method Nombre del m�todo
  * @param state Estado o mensaje a mostrar
  */
#define MESSAGE(classObj, method, state)                      \
{                                                             \
  std::ostringstream os_;                                     \
  os_ << classObj << "::" << method << " : "                  \
      << "[CREATION OF RESOURCE" << ": " << state "] \n";     \
  std::cerr << os_.str();                                     \
}

  /**
   * @brief Macro para mostrar errores y terminar la ejecuci�n
   *
   * Imprime mensaje de error y llama a exit(1)
   *
   * @param classObj Nombre de la clase u objeto
   * @param method Nombre del m�todo
   * @param errorMSG Mensaje de error detallado
   */
#define ERROR(classObj, method, errorMSG)                      \
{                                                              \
  std::ostringstream os_;                                      \
  os_ << "ERROR : " << classObj << "::" << method << " : "     \
      << "  Error in data from params [" << errorMSG << "] \n";\
  std::cerr << os_.str();                                      \
  exit(1);                                                     \
}

   /**
    * @enum ShapeType
    * @brief Enumeraci�n de tipos de formas geom�tricas soportadas
    */
enum ShapeType {
    EMPTY = 0,
    CIRCLE = 1,
    RECTANGLE = 2,
    TRIANGLE = 3,
    POLYGON = 4
};
