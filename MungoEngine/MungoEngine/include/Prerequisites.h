/**
 * @file Prerequisites.h
 * @brief Archivo de cabecera con utilidades, macros y tipos base comunes para todo el motor.
 * @author Hannin Abarca
 */

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

 /**
  * @def SAFE_PTR_RELEASE(x)
  * @brief Libera un puntero y lo asigna a nullptr de forma segura.
  */
#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

  /**
   * @def MESSAGE(classObj, method, state)
   * @brief Macro para imprimir un mensaje de creación de recurso al flujo de error estándar.
   *
   * @param classObj Nombre de la clase.
   * @param method Nombre del método.
   * @param state Estado del recurso creado.
   */
#define MESSAGE(classObj, method, state)                      \
{                                                             \
    std::ostringstream os_;                                   \
    os_ << classObj << "::" << method << " : "                \
        << "[CREATION OF RESOURCE" << ": " << state << "] \n";\
    std::cerr << os_.str();                                   \
}

   /**
    * @def ERROR(classObj, method, errorMSG)
    * @brief Macro para imprimir un mensaje de error y terminar la ejecución.
    *
    * @param classObj Nombre de la clase donde ocurrió el error.
    * @param method Nombre del método donde ocurrió el error.
    * @param errorMSG Mensaje de error detallado.
    */
#define ERROR(classObj, method, errorMSG)                         \
{                                                                 \
    std::ostringstream os_;                                       \
    os_ << "ERROR : " << classObj << "::" << method << " : "      \
        << "  Error in data from params [" << errorMSG << "] \n"; \
    std::cerr << os_.str();                                       \
    exit(1);                                                      \
}

    /**
     * @enum ShapeType
     * @brief Define los tipos de figuras geométricas soportadas por el sistema.
     */
enum
    ShapeType {
    EMPTY = 0,     /**< Sin tipo asignado. */
    CIRCLE = 1,    /**< Círculo. */
    RECTANGLE = 2, /**< Rectángulo. */
    TRIANGLE = 3,  /**< Triángulo. */
    POLYGON = 4    /**< Polígono de múltiples lados. */
};
