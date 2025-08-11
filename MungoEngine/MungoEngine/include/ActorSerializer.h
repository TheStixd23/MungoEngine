#pragma once
/**
 * @file ActorSerializer.h
 * @brief Funciones para serializar y deserializar actores a/desde un archivo.
 *
 * Proporciona utilidades para guardar el estado de una colección de actores en un
 * archivo y cargarlo posteriormente, permitiendo persistencia y restauración de escenas.
 *
 * @author Hannin Abarca
 */

#include "./ESC/Actor.h"
#include "Prerequisites.h"

 /**
  * @namespace ActorSerializer
  * @brief Espacio de nombres que contiene funciones de serialización de actores.
  */
namespace ActorSerializer {
	/**
	 * @brief Guarda una lista de actores en un archivo.
	 *
	 * Serializa la información relevante de cada actor y la escribe en el archivo
	 * especificado por nombre.
	 *
	 * @param filename Ruta y nombre del archivo destino.
	 * @param actors Lista de actores a guardar.
	 * @return `true` si la operación fue exitosa, `false` si falló.
	 */
	bool saveActorsToFile(const std::string& filename, const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

	/**
	 * @brief Carga una lista de actores desde un archivo.
	 *
	 * Lee la información previamente serializada y reconstruye la colección de actores
	 * en la referencia proporcionada.
	 *
	 * @param filename Ruta y nombre del archivo de origen.
	 * @param actors Referencia a un vector donde se almacenarán los actores cargados.
	 * @return `true` si la operación fue exitosa, `false` si falló.
	 */
	bool loadActorsFromFile(const std::string& filename, std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);
}
